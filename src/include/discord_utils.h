#include "../discord/discord.h"
#include <ctime>
#include <iostream>
#include <format>

discord::Core* init_discord();
void update_activity(discord::Core* client, discord::Activity activity);
