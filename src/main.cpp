#include <iostream>
#include <ctime>
#include <thread>
#include "include/discord_utils.h"
#include "discord/discord.h"

int main() {
    discord::Core* discord_client = init_discord();

    discord::Activity activity{};
    activity.SetDetails("ballin out");
    activity.SetState("not done yet idk");
    activity.SetType(discord::ActivityType::Playing);
    activity.GetTimestamps().SetStart(std::time(0));

    update_activity(discord_client, activity);

    while (1) {
        discord_client->RunCallbacks();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}
