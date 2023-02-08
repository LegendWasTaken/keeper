#ifndef KEEPER_CLI_H
#define KEEPER_CLI_H

#include <CLI/App.hpp>
#include <CLI/Formatter.hpp>
#include <CLI/Config.hpp>

namespace keep::cli {
  struct options {
    bool init = false;
    bool write_service = false;

    std::string path = "";
  };
  [[nodiscard]] options parse(int argc, char** argv) {
    auto app = CLI::App("Keeper");

    auto args = options();
    app.add_flag("--init", args.init, "Should keep initialize base files to the path? (Requires path)");
    app.add_flag("--write_service", args.write_service, "Write a service file for keeper? (Requires path)");

    app.add_option("--path", args.path, "Path for keeper to use");

    try {
      app.parse(argc, argv);
    } catch (CLI::ParseError &e) {
      // Todo: Log error
    }

    return args;
  }
}

#endif //KEEPER_CLI_H
