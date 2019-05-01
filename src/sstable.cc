#include <fstream>
#include <memory>

#include <glog/logging.h>
#include <google/protobuf/util/delimited_message_util.h>
#include <boost/filesystem.hpp>

#include "sstable.h"
#include "proto/segment.pb.h"

DEFINE_uint64(index_offset_bytes, 4096,
              "The minimum number of bytes between each segment that is "
              "referenced in the sparse index. Increasing this will decrease "
              "memory usage, but at the cost of higher read overhead");

using google::protobuf::util::SerializeDelimitedToOstream;

namespace diverdb {

SSTable::SSTable(const fs::path sstable_path)
    : index_offset_bytes_(FLAGS_index_offset_bytes) {
  CHECK(fs::exists(sstable_path))
      << "SSTable file " << sstable_path << " does not exist";
}

SSTable::SSTable(const fs::path new_sstable_path, const Memtable& memtable)
    : index_offset_bytes_(FLAGS_index_offset_bytes) {
  CHECK(!fs::exists(new_sstable_path))
      << "SSTable file " << new_sstable_path << " exists";
}

SSTable::SSTable(const fs::path new_sstable_path,
                 const std::vector<SSTablePtr>& sstables)
    : index_offset_bytes_(FLAGS_index_offset_bytes) {
  CHECK(!fs::exists(new_sstable_path))
      << "SSTable file " << new_sstable_path << " exists";
}

bool SSTable::FlushMemtable(const fs::path new_sstable_path,
                            const Memtable& memtable) {
  // Relying on the ofstream destructor to close the fd.
  fs::ofstream ofs(new_sstable_path);

  for (const auto& entry : memtable) {
    // TODO: Investigate using protobuf zero-copy streams.
    // TODO: Investigate protobuf arena.
    Segment segment = entry.second;
    if (!SerializeDelimitedToOstream(segment, &ofs)) {
      return false;
    }
  }

  return true;
}

}  // namespace diverdb
