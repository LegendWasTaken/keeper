#include "cli.h"

#include <iostream>

int main(int argc, char** argv) {
  const auto options = keep::cli::parse(argc, argv);

  std::cout << options.path << std::endl;

  return 0;
}
