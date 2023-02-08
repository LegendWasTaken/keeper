#include "cli.h"

#include <CLI/App.hpp>
#include <CLI/Formatter.hpp>
#include <CLI/Config.hpp>

std::optional<keep::cli::options> keep::cli::try_parse(int argc, const char *const *argv) noexcept {
  auto app = CLI::App("Keeper");

  auto args = options();
  app.add_flag("--init", args.init, "Should keep initialize base files to the path? (Requires path)");
  app.add_flag("--write_service", args.write_service, "Write a service file for keeper? (Requires path)");

  app.add_option("--path", args.path, "Path for keeper to use");

  try {
    app.parse(argc, argv);
  } catch (CLI::ParseError &e) {
    return std::nullopt;
  }

  return args;
}

keep::cli::options keep::cli::parse(int argc, const char *const *argv) {
  const auto optional_options = try_parse(argc, argv);
  if (optional_options.has_value()) {
    return optional_options.value();
  } else {
    throw std::runtime_error("failed to parse values from cli");
  }
}
