#include "discord_utils.h"

#define CLIENT_ID 1112083805747023892

/**
 * \brief Instantiates the Discord core
 *
 * \return Discord's core
 */
discord::Core* init_discord() {
    discord::Core* client{};

    auto result = discord::Core::Create(CLIENT_ID, DiscordCreateFlags_Default, &client);

    if (!client) {
        printf("Failed while initiating the Discord core. Error: %d.\n", static_cast<int>(result));
        exit(-1);
    }

    return client;
}

/**
 * \brief Updates user's activity
 *
 * \param client The Discord core
 * \param activity The activity to be put into the status
 */
void update_activity(discord::Core* client, discord::Activity activity) {
    client->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
        printf("%s", (result == discord::Result::Ok ? "" : std::format("Failed while updating activity. Error: {}\r", static_cast<int>((result))).c_str()));
    });
}
