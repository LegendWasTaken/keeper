#include <catch2/catch_all.hpp>

#include "../source/config/config.h"
#include <string_view>

TEST_CASE("Default server config", "[config.from_string]") {
  const auto val = keep::config::server();
  const auto config = keep::config::detail::parse_from_string<keep::config::server>("a = 5");

  REQUIRE(config.ip == val.ip);
  REQUIRE(config.port == val.port);
  REQUIRE(config.timeout == val.timeout);
  REQUIRE(config.threads.queue == val.threads.queue);
  REQUIRE(config.threads.request == val.threads.request);
  REQUIRE(config.responses.not_found == val.responses.not_found);
  REQUIRE(config.responses.success == val.responses.success);
  REQUIRE(config.responses.timeout == val.responses.timeout);
}

TEST_CASE("Server config from file", "[config.from_file]") {
  const auto config = keep::config::read<keep::config::server>("data/config/server.toml");
  
}
