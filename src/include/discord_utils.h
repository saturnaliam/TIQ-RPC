#include "../discord/discord.h"
#include <memory>

struct DiscordState {
    discord::User current_user;

    std::unique_ptr<discord::Core> core;
};

DiscordState initialize_discord();
