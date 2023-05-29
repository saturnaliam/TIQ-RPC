#include "toml_utils.h"

/**
 * \brief Initializes the configuration for the program
 *
 * \return toml_config Configurations
 */
toml_config init_config() {
    toml_config config;

    toml::table table;

    try {
        table = toml::parse_file("config.toml");
    } catch (const toml::parse_error& err) {
        die(std::format("{} Check your config.toml file!", err.description().data()));
    }

    std::optional<int> flash_version = table["flash_version"].value<int>();
    std::optional<int> wait_time = table["wait_time"].value<int>();
    std::optional<bool> timeout = table["timeout"].value<bool>();

    // Ensuring that the necessary keys are there
    if (!flash_version) die("Error finding key 'flash_version'! Check your config.toml file!");
    if (!wait_time) die("Error finding key 'wait_time'! Check your config.toml file!");
    if (!timeout) die("Error finding key 'timeout'! Check your config.toml file!");

    // Handling invalid Flash Versions
    if (*flash_version < 0 || *flash_version > 2) die("Invalid Flash version! Check your config.toml file!");
    if (*wait_time < 10 || *wait_time > 1000) die("Invalid wait time! Check your config.toml file!");

    config.flash_version = *flash_version;
    config.wait_time = *wait_time;
    config.timeout = *timeout;

    return config;
}
