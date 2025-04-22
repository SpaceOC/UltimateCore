#pragma once
#include <filesystem>
#include <map>
#include <string>

class VirtualFS {
 public:
  /**
   * Loads a filesystem from default file ('main.fs') in this directory.
   * Creates this file if it doesn't exist.
   */
  VirtualFS();
  /**
   * Saves the FS file.
   */
  ~VirtualFS();

  template <class Archive>
  void serialize(Archive& archive);

  void writeFS();
  void loadFS();

  /**
   * Adds or overwrites the file with data.
   * @param path A path to the file.
   * @param data Data to write.
   */
  void addFile(const std::string& path, const std::string& data);

  /**
   * Locks (allows only read) or unlocks (allows both read and write) the FS.
   * @param isLock true - lock, false - unlock.
   */
  void lock(bool isLock);

 private:
  std::map<std::string, std::string> fs_;
  // This should not be serialized.
  bool readOnly_ = false;
};