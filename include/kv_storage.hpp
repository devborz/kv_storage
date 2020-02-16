// Copyright 2020 Usman Turkaev
#pragma once
#include <boost/program_options.hpp>
#include <boost/thread.hpp>
#include <cassert>
#include <iostream>
#include <string>
#include "rocksdb/db.h"

using namespace boost::program_options;

namespace kv_storage {
void get_options(variables_map& vm, int argc, char* argv[]) {
  options_description desc("Allowed options");
  desc.add_options()("help", "выводим вспомогательное сообщение")(
      "log-level", value<std::string>(),
      "= \"info\"|\"warning\"|\"error\"\n"
      "= default: \"error\"")("thread-count", value<std::string>(),
                              "=\n= default: count of logical core")(
      "output", value<std::string>(),
      "= <path/to/output/storage.db>\n"
      "= default: <path/to/input/dbcs-storage.db>");
  store(parse_command_line(argc, argv, desc), vm);
  notify(vm);
}

void work(int argc, char* argv[]) {
  variables_map vm;
  get_options(vm, argc, argv);
}
}  // namespace kv_storage
