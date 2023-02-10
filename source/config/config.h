#ifndef KEEPER_CONFIG_H
#define KEEPER_CONFIG_H

#include <toml/toml.hpp>

#include <string>
#include <filesystem>

namespace keep::config {
struct server {
  static constexpr std::string_view name = "server.config";

  const std::string ip = "127.0.0.1";
  const std::string port = "25565";
  const std::uint64_t timeout = 10'000;

  struct {
    const std::uint32_t queue = 4;
    const std::uint32_t request = 8;
  } threads;

  struct {
    const std::string not_found = "./respond/404.json";
    const std::string success = "./respond/found.json";
    const std::string timeout = "./respond/timeout.json";
  } responses;
};

namespace detail {
template <typename T>
[[nodiscard]] T read_value(const auto &node, T def) = delete;

template <>
[[nodiscard]] std::string read_value(const auto &node, std::string def) {
  return std::string(node.value_or(def));
}

template <>
[[nodiscard]] std::uint64_t read_value(const auto &node, std::uint64_t def) {
  return node.value_or(def);
}

template <>
[[nodiscard]] std::uint32_t read_value(const auto &node, std::uint32_t def) {
  return node.value_or(def);
}

template <typename T>
[[nodiscard]] T parse_toml(toml::table table) = delete;

template <>
[[nodiscard]] server parse_toml(toml::table table) {
  const auto def = server();

  return {
    .ip = read_value(table["ip"], def.ip),
    .port = read_value(table["port"], def.port),
    .timeout = read_value(table["timeout"], def.timeout),
    .threads = {
      .queue = read_value(table["threads"]["queue"], def.threads.queue),
      .request = read_value(table["threads"]["queue"], def.threads.request),
    },
    .responses = {
      .not_found = read_value(table["responses"]["not_found"], def.responses.not_found),
      .success = read_value(table["responses"]["success"], def.responses.success),
      .timeout = read_value(table["responses"]["timeout"], def.responses.timeout),
    }
  };
}

template<typename T>
concept Configurable = requires(T t, toml::table read_table) {
//  std::is_same<typename T::name, std::string_view>::value;
  parse_toml<T>(read_table);
};

/**
 * Will attempt to read config of the specified type from the passed config string
 * @tparam Config a valid configurable type to read
 * @param contents the config string
 * @return The parsed config
 * @throw toml::parse_error On failure to parse the string
 */
template<Configurable Config>
[[nodiscard]] Config parse_from_string(std::string_view contents) {
  const auto table = toml::parse(contents);
  return parse_toml<Config>(table);
}
}

/**
 * Will attempt to read config of the specified type
 * @tparam Config a valid configurable type to read
 * @param folder the folder that the file is located in
 * @return The read config
 * @throw toml::parse_error On failure to parse the file
 */
template<detail::Configurable Config>
[[nodiscard]] std::optional<Config> read(const std::filesystem::path &folder) {
  const auto file = folder / Config::name;
  auto stream = std::ifstream(file);
  const auto contents = std::string(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
  return detail::parse_from_string<Config>(contents);
}
}

#endif //KEEPER_CONFIG_H
