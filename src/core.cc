#include "core.h"
#include "module.h"

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <dylib.hpp>
#include <fstream>
#include <filesystem>

struct ModulesConfig
{
  std::vector<std::string> modules;

  template <class Archive>
  void serialize(Archive &archive)
  {
    archive(modules);
  }
};

Core::Core() // NOLINT
{
  std::fstream config("modules.json");
  cereal::JSONInputArchive archive(config);

  ModulesConfig modules; // NOLINT
  archive(modules);

  if (!modules.modules.empty())
  {
    loadAllModules(modules.modules);
  }
}

Core::~Core() // NO;INT
{
}

bool Core::sendRequest(const std::string &request) // NOLINT
{
  if (loadedModules_.empty())
  {
    return false;
  }

  for (size_t i = 0; i < loadedModules_.size(); i++)
  {
    if (!loadedModules_[i])
    {
      continue;
    }

    bool result = loadedModules_[i]->runRequest(request);

    if (result)
    {
      return result;
    }
  }
  return false;
}

std::string Core::getLanguage() // NOLINT
{
  return currentLanguage_;
}

void Core::loadAllModules(const std::vector<std::string> &names)
{
  for (size_t i = 0; i < names.size(); i++)
  {
    std::string name = names[i];
    std::string start_path = "modules/" + name;

    if (!std::filesystem::exists(start_path) && !std::filesystem::exists(start_path + "/lib.json") && !std::filesystem::exists(start_path + "/translations.json"))
    {
      continue;
    }

    std::fstream metadata_file("modules/" + name + "/lib.json");
    cereal::JSONInputArchive archive_metadata(metadata_file);

    auto module_metadata = new ModuleMetadata();
    archive_metadata(*module_metadata);

    if (module_metadata->name != name)
    {
      delete module_metadata;
      continue;
    }

    std::fstream translate_metadata_file("modules/" + name + "/translations.json");
    cereal::JSONInputArchive archive_translate_metadata(translate_metadata_file);

    auto module_translate_metadata = new ModuleMetadataTranslate();
    archive_translate_metadata(*module_translate_metadata);

    module_metadata->translate = module_translate_metadata;

    try
    {
      std::string bin_name = module_metadata->layout[OS_NAME];

      dylib lib(start_path + "/bin/" + (bin_name.empty() ? OS_NAME : bin_name));
      auto create_module_func = lib.get_function<Module *(Core *, ModuleMetadata *)>("createModule");

      auto module = create_module_func(this, module_metadata);
      if (module)
      {
        std::unique_ptr<Module> module_with_unique_ptr(std::move(module));

        loadedModules_.push_back(std::move(module_with_unique_ptr));
      }
    }
    catch (std::exception &e)
    {
      std::cout << e.what() << '\n';
    }
  }
}