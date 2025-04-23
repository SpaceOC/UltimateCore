#include "core.h"
#include "module.h"

Module::Module(Core *core, ModuleMetadata *meta) : corePtr_(core), metadata_(meta) // NOLINT
{
    path_ = "modules/" + meta->name;

    // std::string coreLanguage = corePtr_->getLanguage();
    // currentLanguage_ = ...
};