#include <iostream>
#include <ctime>
#include <thread>
#include <Windows.h>
#include "include/discord_utils.h"
#include "discord/discord.h"
#include "include/tiq_levels.h"
#include "tiq/tiq.hpp"

int main() {
    init_levels();

    wchar_t* executable = &const_cast<wchar_t&>(*L"flashplayer_32_sa.exe");
    wchar_t* title = &const_cast<wchar_t&>(*L"Adobe Flash Player 32");

    TIQ::window window = TIQ::findWindow(executable, title);

    while (window.windowHandle == NULL) {
        printf("TIQ not found!   \r");
        window = TIQ::findWindow(executable, title);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    DWORD_PTR address = TIQ::followPointerPath(window, TIQ::offsets::FL32SA_OFFSETS);
    int scene = TIQ::getScene(address, window);

    discord::Core* discord_client = init_discord();

    discord::Activity activity{};
    activity.SetDetails("if you see this something went horrible wrong");
    activity.SetType(discord::ActivityType::Playing);
    activity.GetTimestamps().SetStart(std::time(0));
    activity.GetAssets().SetLargeImage("o");
    activity.GetAssets().SetLargeText("The Impossible Quiz");


    while (1) {
        scene = TIQ::getScene(address, window);
        if (scene >= levels.size()) break;

        activity.SetDetails(levels[scene].c_str());
        update_activity(discord_client, activity);
        printf("%s   %d            \r", levels[scene].c_str(), scene);

        discord_client->RunCallbacks();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    discord_client->ActivityManager().ClearActivity([](discord::Result result) {});
    discord_client->RunCallbacks();
}
