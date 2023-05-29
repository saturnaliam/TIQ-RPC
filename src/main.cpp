#include <ctime>
#include <thread>
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>

#include "tiq/tiq.hpp"
#include "toml/toml.hpp"
#include "discord/discord.h"
#include "include/toml_utils.h"
#include "include/tiq_utils.h"
#include "include/error_handle.h"
#include "include/discord_utils.h"

#define TIMEOUT_TIME 3000

/**
 * * To ensure lines are properly cleared, printf() statements should be 20 characters long.
 */

/**
 * \brief Initializes the program
 *
 * \param config The toml_config struct
 * \param flash The Flash player to configure
 * \param levels The vector of levels
 * \param client The Discord client
 */
void initialize(toml_config &config, flash_player &flash, std::vector<std::string> &levels, discord::Core* &client) {
    config = init_config();

    // initializing the player
    switch (config.flash_version) {
        case 0:
            flash.executable = (wchar_t*)L"flashplayer_11_sa_32bit.exe";
            flash.window_name = (wchar_t*)L"Adobe Flash Player 11";
            flash.ptr_path = TIQ::offsets::FL11SA_OFFSETS;
            break;

        case 1:
            flash.executable = (wchar_t*)L"Flash_Player.exe";
            flash.window_name = (wchar_t*)L"Adobe Flash Player 32";
            flash.ptr_path = TIQ::offsets::FL32_OFFSETS;
            break;

        case 2:
            flash.executable = (wchar_t*)L"flashplayer_32_sa.exe";
            flash.window_name = (wchar_t*)L"Adobe Flash Player 32";
            flash.ptr_path = TIQ::offsets::FL32SA_OFFSETS;
            break;
    }

    // initializing levels stuff
    levels = init_levels();

    // initializing discord client
    client = init_discord();
}

/**
 * \brief Attempts to find the window, times out otherwise
 *
 * \param timeout Whether or not to timeout
 * \param flash The flash player
 * \param window The window to find
 */
void find_window(bool timeout, flash_player flash, TIQ::window &window) {
    window = TIQ::findWindow(flash.executable, flash.window_name);

    clock_t initial_time = clock();
    clock_t dot_time = clock();

    int dot_anim = 0;

    while (window.windowHandle == NULL) {
        if (timeout && clock() - initial_time > TIMEOUT_TIME) die("Timed out!          \r");

        std::string print_string = "Searching for TIQ";

        // adding the little animated silly dots
        switch (dot_anim % 3) {
            case 0:
                print_string += ".  ";
                break;

            case 1:
                print_string += ".. ";
                break;

            case 2:
                print_string += "...";
                break;
        }

        printf("%s\r", print_string.c_str());

        // incrementing dot timer
        if (clock() - dot_time > 750) {
            dot_time = clock();
            dot_anim++;
        }

        // actually finding the window
        window = TIQ::findWindow(flash.executable, flash.window_name);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::vector<std::string> levels;
    toml_config program_config{ };
    flash_player flash{ };
    discord::Core* discord_client{ };
    initialize(program_config, flash, levels, discord_client);


    TIQ::window window{ };
    find_window(program_config.timeout, flash, window);
    printf("Found window!       \r");


    DWORD_PTR address = TIQ::followPointerPath(window, flash.ptr_path);
    int scene = TIQ::getScene(address, window);
    int prev_scene = scene;
    if (scene >= levels.size()) die("Issue with detecting the current level! Check your Flash version!");


    discord::Activity activity{ };
    activity.SetType(discord::ActivityType::Playing);
    activity.GetTimestamps().SetStart(std::time(0));
    activity.GetAssets().SetLargeImage("icon");
    activity.GetAssets().SetLargeText("The Impossible Quiz");
    activity.SetDetails(levels[scene].c_str());
    update_activity(discord_client, activity);


    while (1) {
        window = TIQ::findWindow(flash.executable, flash.window_name);
        scene = TIQ::getScene(address, window);

        if (window.windowHandle == NULL) {
            discord_client->ActivityManager().ClearActivity([](discord::Result result) {});

            find_window(program_config.timeout, flash, window);
            prev_scene = 999; // making sure the rpc updates
            address = TIQ::followPointerPath(window, flash.ptr_path);
            printf("Found window!       \r");
            continue;
        }

        // making sure we dont call update activity toooo often
        if (scene != prev_scene) {
            if (scene < levels.size()) {
                activity.SetDetails(levels[scene].c_str());
            } else {
                die("Issue with current level! Check your Flash version!");
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
