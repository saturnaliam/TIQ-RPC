#include "../discord/discord.h"
#include <iostream>

discord::Core* init_discord();
void update_activity(discord::Core* client, discord::Activity activity);
