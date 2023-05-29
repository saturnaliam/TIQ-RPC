#include "tiq_levels.h"

/**
 * \brief Initializes a vector of the levels in TIQ
 *
 * \return A vector of levels alongside their scene
 */
std::vector<std::string> init_levels() {
    std::vector<std::string> levels;

    levels.push_back("Main Menu");

    for (int i = 1; i <= 110; i++) {
        levels.push_back(std::format("Q{}", i));
    }

    // adds some values bc the like skip cutscenes have their own scenes for some reason
    levels.insert(levels.begin() + 11, 18, "Q11"); // awesome hardcoded values :3
    levels.insert(levels.begin() + 39, 19, "Q21");
    levels.insert(levels.begin() + 73, 18, "Q36");
    levels.insert(levels.begin() + 111, 18, "Q56");
    levels.insert(levels.begin() + 149, 19, "Q76");
    levels.insert(levels.begin() + 193, "Q101");
    levels.insert(levels.begin() + 195, "Q102");
    levels.insert(levels.begin() + 197, "Q103");
    levels.insert(levels.begin() + 199, "Q104");
    levels.insert(levels.begin() + 201, 2, "Q105");
    levels.insert(levels.begin() + 205, 3, "Q107");
    levels.insert(levels.begin() + 209, "Q108");
    levels.insert(levels.begin() + 211, "Q109");
    levels.insert(levels.begin() + 213, 8, "Q110");

    for (int i = 222; i <= 341; i++) {
        levels.push_back("Beat the game!");
    }

    for (int i = 342; i < 404; i++) {
        levels.push_back("ngl no clue whats going on");
    }

    levels.push_back("game over :(");

    return levels;
}
