#include <iostream>
#include "include/discord_utils.h"
#include "discord/discord.h"

int main() {

    printf("hi");
    DiscordState state{};

    discord::Core* core{};
    auto result = discord::Core::Create(1112083805747023892, DiscordCreateFlags_Default, &core);

    state.core.reset(core);
}
