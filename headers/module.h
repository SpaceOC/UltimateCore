#ifndef MODULE_H
#define MODULE_H

#include "modulemetadata.h"

#include <memory>
#include <string>
#include <map>

#define DLLExport __declspec(dllexport)

class Core;

class Module
{
public:
  explicit Module(Core *core, ModuleMetadata *meta);
  virtual ~Module() = 0;
  Module(const Module &) = delete;
  Module(Module &&) = delete;
  Module &operator=(const Module &) = delete; // NOLINT
  Module &operator=(Module &&) = delete;      // NOLINT

  virtual bool runRequest(const std::string &request) = 0; // NOLINT
private:
  std::unique_ptr<Core> corePtr_;
  std::string path_;
  std::map<std::string, std::string> currentLanguage_;
  std::unique_ptr<ModuleMetadata> metadata_;
};

#endif // MODULE_H