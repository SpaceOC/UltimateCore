#ifndef CORE_H
#define CORE_H
#include <iostream>
#include <string>
#include <vector>

class Module;

class Core
{
public:
  Core();
  /**
   * Unload all modules
   */
  ~Core();
  Core(const Core &) = delete;
  Core(Core &&) = delete;
  Core &operator=(const Core &) = delete; // NOLINT
  Core &operator=(Core &&) = delete;      // NOLINT

  int sendRequest(std::string what); // NOLINT

private:
  friend class Module;
  std::vector<std::unique_ptr<Module>> loadedModules_;
};
#endif // CORE_H