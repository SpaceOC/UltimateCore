#include "core.h"
#include "module.h"

#include <cereal/archives/json.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>
#include <fstream>

Module::Module(Core *core, ModuleMetadata *meta) : corePtr_(core), metadata_(meta) // NOLINT
{
    path_ = "modules/" + meta->name;

    std::fstream translate_data(path_ + "/langs/" + corePtr_->getLanguage() + ".json");
    cereal::JSONInputArchive archive(translate_data);

    TranslateMap cur_language; // NOLINT
    archive(cur_language);

    currentLanguage_ = cur_language.translate;
};