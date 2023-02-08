#include "cli.h"

#include <CLI/App.hpp>
#include <CLI/Formatter.hpp>
#include <CLI/Config.hpp>

keep::cli::options keep::cli::parse(int argc, const char *const *argv) {
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
