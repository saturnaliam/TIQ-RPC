#include <string>
#include <format>
#include <vector>
#include <Windows.h>

struct flash_player {
    wchar_t* executable;
    wchar_t* window_name;
    std::vector<DWORD_PTR> ptr_path;
};

std::vector<std::string> init_levels();
