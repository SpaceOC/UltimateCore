// A virtual file system.

#include "../headers/virtualfs.h"

#include <cereal/archives/portable_binary.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>
#include <fstream>

namespace
{
  const std::string kDefaultFsName = "main.fs"; // NOLINT
} // namespace

template <class Archive>
void VirtualFS::serialize(Archive &archive)
{
  archive(fs_);
};

void VirtualFS::writeFS()
{
  std::ofstream out_file_stream(kDefaultFsName, std::ios::binary);
  if (out_file_stream)
  {
    cereal::PortableBinaryOutputArchive archive(out_file_stream);
    archive(*this);
  }
}

void VirtualFS::loadFS()
{
  std::ifstream in_file_stream(kDefaultFsName, std::ios::binary);
  if (in_file_stream)
  {
    cereal::PortableBinaryInputArchive archive(in_file_stream);
    archive(*this);
  }
}

VirtualFS::VirtualFS()
{
  const bool is_file_exists = std::filesystem::exists(kDefaultFsName);

  if (!is_file_exists)
  {
    writeFS();
  }
  else
  {
    loadFS();
  }
}

VirtualFS::~VirtualFS()
try
{
  writeFS();
}
catch (const std::exception &e)
{
  std::cout << e.what() << '\n';
}

void VirtualFS::addFile(const std::string &path, const std::string &data)
{
  if (readOnly_)
  {
    throw std::logic_error("FS is locked");
  }
  fs_[path] = data;
}

void VirtualFS::lock(const bool isLock) { readOnly_ = isLock; }
