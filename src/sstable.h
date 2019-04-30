#pragma once

#include <string>
#include <unordered_map>

#include <boost/filesystem.hpp>

#include "buffer.h"
#include "memtable.h"

namespace fs = boost::filesystem;
namespace diodb {

class SSTable {
 public:
  // Constructing an SSTable object with just a filename implies that we are
  // simply representing an SSTable file that already exists. If the file
  // indicated by 'sstable_path' DOES NOT exist, DioDB will abort.
  SSTable(const fs::path sstable_path);

  // Constructing an SSTable using a filename and a memtable implies we are
  // flushing the memtable to disk. The file indicated by 'new_sstable_path'
  // MUST NOT exist, or DioDB will abort.
  SSTable(const fs::path new_sstable_path, const Memtable memtable);

  // Constructing an SSTable from other SSTable objects will merge the provided
  // SSTables into a new object at the provided filename. The file indicated by
  // 'new_sstable_path' MUST NOT exist, or DioDB will abort.
  SSTable(const fs::path new_sstable_path, const std::vector<SSTable> sstables);

  ~SSTable() {}

  // TODO: stats such as num_bytes..

 private:
  // The minimum number of bytes between each segment referenced in the
  // sparse index.
  size_t index_offset_bytes_;

  // A sparse index of the keys and offsets of the associated SSTable entries
  // in the file.
  std::unordered_map<Buffer, uint64_t> sparse_index_;
};

}  // namespace diodb
