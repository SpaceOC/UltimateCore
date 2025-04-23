#ifndef CORE_H
#define CORE_H
#include <iostream>
#include <string>
#include <vector>

#if (defined(_WIN32) || defined(_WIN64))
#define OS_NAME "windows"
#elif defined(__APPLE__)
#define OS_NAME "macos"
#else
#define OS_NAME "linux"
#endif

class Module;

class Core
{
public:
  /**
   * Reads the modules.json file.
   * Loads all modules that were specified in that file.
   */
  Core();
  /**
   * Unload all modules
   */
  ~Core();
  Core(const Core &) = delete;
  Core(Core &&) = delete;
  Core &operator=(const Core &) = delete; // NOLINT
  Core &operator=(Core &&) = delete;      // NOLINT

  bool sendRequest(const std::string &request); // NOLINT

  std::string getLanguage();

private:
  friend class Module;
  std::string currentLanguage_;
  std::vector<std::unique_ptr<Module>> loadedModules_;

  void loadAllModules(const std::vector<std::string> &names);
};
#endif // CORE_H