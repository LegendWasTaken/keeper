#include <catch2/catch_all.hpp>

#include <cli.h>

#include <initializer_list>

namespace {
[[nodiscard]] std::vector<const char *> create_args(std::initializer_list<std::string_view> views)
{
  auto args = std::vector<const char *>({"fake_pwd"});
  args.reserve(views.size());
  for (auto view : views) {
    args.push_back(view.data());
  }

  return args;
}

TEST_CASE("Default args", "[cli.try_parse]") {
  const auto args = create_args({});
  const auto options = keep::cli::try_parse(static_cast<int>(args.size()), args.data());

  REQUIRE(options.has_value());
  REQUIRE(options->init == false);
  REQUIRE(options->write_service == false);
  REQUIRE(options->path.empty());
}

TEST_CASE("init arg", "[cli.try_parse]") {
  const auto args = create_args({"--init"});
  const auto options = keep::cli::try_parse(static_cast<int>(args.size()), args.data());

  REQUIRE(options.has_value());
  REQUIRE(options->init == true);
  REQUIRE(options->write_service == false);
  REQUIRE(options->path.empty());
}

TEST_CASE("write_service arg", "[cli.try_parse]") {
  const auto args = create_args({"--write_service"});
  const auto options = keep::cli::try_parse(static_cast<int>(args.size()), args.data());

  REQUIRE(options.has_value());
  REQUIRE(options->init == false);
  REQUIRE(options->write_service == true);
  REQUIRE(options->path.empty());
}

TEST_CASE("path arg", "[cli.try_parse]") {
  const auto args = create_args({"--path", "foobar"});
  const auto options = keep::cli::try_parse(static_cast<int>(args.size()), args.data());

  REQUIRE(options.has_value());
  REQUIRE(options->init == false);
  REQUIRE(options->write_service == false);
  REQUIRE(options->path == "foobar");
}

TEST_CASE("nonsense arguments", "[cli.try_parse]") {
  const auto args = create_args({"nonsense"});
  const auto options = keep::cli::try_parse(static_cast<int>(args.size()), args.data());

  REQUIRE(!options.has_value());
}

TEST_CASE("nonsense arguments", "[cli.parse]") {
  const auto args = create_args({"nonsense"});
  REQUIRE_THROWS(keep::cli::parse(static_cast<int>(args.size()), args.data()));
}

}
