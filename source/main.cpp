#include "cli.h"

int main(int argc, char** argv) {
  const auto options = keep::cli::parse(argc, argv);

  return 0;
}
