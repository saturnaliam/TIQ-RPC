#include <iostream>
#include <ctime>
#include <thread>
#include <string>
#include <vector>
#include <Windows.h>
#include "include/discord_utils.h"
#include "discord/discord.h"
#include "include/tiq_levels.h"
#include "tiq/tiq.hpp"
#include "toml/toml.hpp"

/**
 * TODO support for *.toml config
 * ? allow disabling of timeout
*/

struct toml_config {
    int flash_version, wait_time;
    bool timeout;
} program_config;

void exit_program() {
    printf("\n");
    system("pause");
    exit(-1);
}

void initialize() {
    // initializing the config
    toml::table table;

    try {
        table = toml::parse_file("config.toml");
    } catch (const toml::parse_error& err) {
        printf("Failed during parsing: %s. Check your config.toml file!", err.description().data());
        exit_program();
    }


    // ! oops! terrible code!
   if (!table["flash_version"].is_integer()) {
        invalid_version:
            printf("Invalid flash version! Check your config.toml file!");
            exit_program();
    } else if (!table["timeout"].is_boolean()) {
        printf("Error reading key 'timeout'! Check your config.toml file!");
        exit_program();
    } else if (!table["wait_time"].is_integer()) {
        invalid_wait:
            printf("Invalid wait time! Check your config.toml file!");
            exit_program();
    }

    int flash_version = *table["flash_version"].value<int>();
    int wait_time = *table["wait_time"].value<int>();
    bool timeout = *table["timeout"].value<bool>();

    if (flash_version > 2 || flash_version < 0) goto invalid_version;
    if (wait_time > 1000 || wait_time < 10) goto invalid_wait;

    program_config.flash_version = flash_version;
    program_config.timeout = timeout;
    program_config.wait_time = wait_time;
}

int main() {
    initialize();

    wchar_t* executable;
    wchar_t* window_name;
    std::vector<DWORD_PTR> ptr_path;

    switch (program_config.flash_version) {
        case 0:
            executable = (wchar_t*)L"flashplayer_11_sa_32bit.exe";
            window_name = (wchar_t*)L"Adobe Flash Player 11";
            ptr_path = TIQ::offsets::FL11SA_OFFSETS;
            break;

        case 1:
            executable = (wchar_t*)L"Flash_Player.exe";
            window_name = (wchar_t*)L"Abode Flash Player 32";
            ptr_path = TIQ::offsets::FL32_OFFSETS;

        case 2:
            executable = (wchar_t*)L"flashplayer_32_sa.exe";
            window_name = (wchar_t*)L"Adobe Flash Player 32";
            ptr_path = TIQ::offsets::FL32SA_OFFSETS;
            break;
    }

    // generic variable init stuff
    std::vector<std::string> levels = init_levels();

    discord::Core* discord_client = init_discord();

    discord::Activity activity{};
    activity.SetType(discord::ActivityType::Playing);
    activity.GetTimestamps().SetStart(std::time(0));
    activity.GetAssets().SetLargeImage("o"); // ? i should change the image tag to something better but idgaf
    activity.GetAssets().SetLargeText("The Impossible Quiz");


    find_window:
        TIQ::window window = TIQ::findWindow(executable, window_name);

        clock_t current_time = clock();

        while (window.windowHandle == NULL) {
            if (program_config.timeout && clock() - current_time > 30000) {
                printf("\r                                              \rTimed out!");
                exit_program();
            }

            printf("\r                     \rSearching for TIQ...");
            window = TIQ::findWindow(executable, window_name);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }


    printf("\r                             \rFound window!");

    DWORD_PTR address = TIQ::followPointerPath(window, TIQ::offsets::FL32SA_OFFSETS);

    int scene = TIQ::getScene(address, window);
    int prev_scene = scene;

    if (scene >= levels.size()) goto find_window; // TODO refactor this
    activity.SetDetails(levels[scene].c_str());

    while (1) {
        window = TIQ::findWindow(executable, window_name);
        scene = TIQ::getScene(address, window);

        if (window.windowHandle == NULL) {
            discord_client->ActivityManager().ClearActivity([](discord::Result result) {});
            goto find_window;
        }

        // making sure we dont call update activity toooo often
        if (scene != prev_scene) {
            if (scene < levels.size() && window.windowHandle != NULL) {
                activity.SetDetails(levels[scene].c_str());
            } else {
                activity.SetDetails("");
            }

            prev_scene = scene;
            update_activity(discord_client, activity);
        }


        discord_client->RunCallbacks();

        std::this_thread::sleep_for(std::chrono::milliseconds(program_config.wait_time));
    }

    discord_client->ActivityManager().ClearActivity([](discord::Result result) {});
    discord_client->RunCallbacks();
}
