#ifndef KEEPER_CLI_H
#define KEEPER_CLI_H

#include <string>
#include <optional>

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
   * @return An optional, containing the options struct with populated values (or defaults) if successful
   */
  [[nodiscard]] std::optional<options> try_parse(int argc, const char* const* argv) noexcept;

  /**
   * Parses arguments from the command line into options struct, will throw on error
   * @param argc
   * @param argv
   * @return Options struct with populated values (or defaults)
   */
  [[nodiscard]] std::optional<options> parse(int argc, const char* const* argv);
}

#endif //KEEPER_CLI_H
