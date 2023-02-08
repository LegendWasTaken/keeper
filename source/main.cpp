#include <iostream>

#include "cli.h"

int main(int argc, char** argv) {
  const auto options = [argc, argv](){
    const auto tried_options = keep::cli::try_parse(argc, argv);
    if (tried_options.has_value()) {
      return tried_options.value();
    } else {
      throw std::runtime_error("Failed to parse values");
    }
  }();

  return 0;
}
