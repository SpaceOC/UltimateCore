#ifndef MODULEMETADATA_H
#define MODULEMETADATA_H

#include <string>
#include <vector>
#include <map>

struct ModuleMetadataTranslate // NOLINT
{
  std::vector<std::string> translations;
  std::vector<std::string> require;
};

struct ModuleMetadata // NOLINT
{
  std::string name;
  std::string description;
  std::vector<std::string> targets;
  std::string uses;
  std::map<std::string, std::string> layout;
  ModuleMetadataTranslate *translate = nullptr; // Для класса Module
};

#endif // MODULEMETADATA_H