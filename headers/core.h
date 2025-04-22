#pragma once
#include <iostream>
#include <string>
#include <vector>

class Module;

class Core {
public:
  Core();
  /**
   * Unload all modules
   */
  ~Core();
  int sendRequest(std::string what);

protected:
  friend class Module;
  std::vector<std::unique_ptr<Module>> loadedModules;
};