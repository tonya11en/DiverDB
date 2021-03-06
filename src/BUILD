cc_binary(
  name = "diodb",
  srcs = ["main.cc"],
  deps = [
    "@glog//:glog",
    "@com_github_gflags_gflags//:gflags",
    ":diodb_server_lib",
  ],
  copts = ["-std=c++17"],
)

cc_library(
  name = "diodb_server_lib",
  srcs = ["server.cc"],
  hdrs = ["server.h"],
  deps = [
    "@glog//:glog",
    "@com_github_gflags_gflags//:gflags",
  ],
  copts = ["-std=c++17"],
)

cc_library(
  name = "buffer_lib",
  hdrs = ["buffer.h"],
  deps = [],
  copts = ["-std=c++17"],
)

cc_library(
  name = "memtable_lib",
  srcs = ["memtable.cc"],
  hdrs = ["memtable.h"],
  deps = [
    "@glog//:glog",
    ":buffer_lib",
    ":generic_table_lib",
  ],
  visibility = ["//test:__pkg__"],
)

cc_library(
  name = "iohandle_lib",
  srcs = ["iohandle.cc"],
  hdrs = ["iohandle.h"],
  deps = [
    "@glog//:glog",
    "@boost//:filesystem",
    ":buffer_lib",
  ],
  copts = ["-std=c++17"],
  visibility = ["//test:__pkg__", "//test/mocks:__pkg__"],
)

cc_library(
  name = "db_ctl_lib",
  srcs = ["db_controller.cc"],
  hdrs = ["db_controller.h"],
  deps = [
    "@glog//:glog",
    ":memtable_lib",
    ":sstable_lib",
    "@boost//:filesystem",
    "//src/util:util_lib",
  ],
  copts = ["-std=c++17"],
  visibility = ["//test:__pkg__", "//test/mocks:__pkg__"],
)

cc_library(
  name = "sstable_lib",
  srcs = ["sstable.cc"],
  hdrs = ["sstable.h"],
  deps = [
    "@glog//:glog",
    ":memtable_lib",
    "@boost//:filesystem",
    ":iohandle_lib",
    ":generic_table_lib",
  ],
  copts = ["-std=c++17"],
  visibility = ["//test:__pkg__", "//test/mocks:__pkg__"],
)

cc_library(
  name = "generic_table_lib",
  hdrs = ["table_stats.h", "readable_table_base.h"],
  copts = ["-std=c++17"],
)
