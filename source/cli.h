#ifndef KEEPER_CLI_H
#define KEEPER_CLI_H

#include <string>

namespace keep::cli {
  struct options {
    bool init = false;
    bool write_service = false;

    std::string path = "";
  };

  /**
   * Parses arguments from the command line into options struct
   * @param argc Argument count
   * @param argv Arguments
   * @return Options struct with populated values (or defaults)
   */
  [[nodiscard]] options parse(int argc, const char* const* argv);
}

#endif //KEEPER_CLI_H
