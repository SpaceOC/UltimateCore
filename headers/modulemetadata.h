#ifndef MODULEMETADATA_H
#define MODULEMETADATA_H

#include <string>
#include <vector>
#include <map>

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>

struct TranslateMap
{
  std::map<std::string, std::string> translate;

  template <class Archive>
  void serialize(Archive &archive)
  {
    archive(translate);
  }
};

struct ModuleMetadataTranslate // NOLINT
{
  std::vector<std::string> translations;
  std::vector<std::string> require;

  template <class Archive>
  void serialize(Archive &archive)
  {
    archive(translations, require);
  }
};

struct ModuleMetadata // NOLINT
{
  std::string name;
  std::string description;
  std::vector<std::string> targets;
  std::string uses;
  std::map<std::string, std::string> layout;
  ModuleMetadataTranslate *translate = nullptr; // Для класса Module

  template <class Archive>
  void serialize(Archive &archive)
  {
    archive(name, description, targets, uses, layout);
  }
};

#endif // MODULEMETADATA_H