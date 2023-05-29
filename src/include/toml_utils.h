#include "../toml/toml.hpp"
#include "error_handle.h"

#include <string>
#include <format>

struct toml_config {
    int flash_version, wait_time;
    bool timeout;
};

toml_config init_config();
