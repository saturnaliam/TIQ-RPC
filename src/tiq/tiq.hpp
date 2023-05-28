#pragma once
#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif


#include <Windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>

namespace TIQ {
    struct window {
        HWND windowHandle;
        DWORD PID;
        HANDLE processHandle;
        DWORD_PTR baseAddress;
    };
    window findWindow(wchar_t* executableName, wchar_t* windowTitle);

    uintptr_t getModuleBase(DWORD PID, const HWND windowHandle, wchar_t* executableName);

    DWORD_PTR followPointerPath(window processWindow, std::vector<DWORD_PTR> offsets);
    int getScene(DWORD_PTR address, window processWindow);

    /// @note Offsets taken from https://github.com/LukeSaward1/AutoSplitters/blob/main/The%20Impossible%20Quiz/TiQ_Autosplitter.asl)
    namespace offsets {
        /// @brief Offsets for TIQ running on Flash Player 32 SA
        const std::vector<DWORD_PTR> FL32SA_OFFSETS = { 0xC95B64, 0x24, 0xA8C, 0x4, 0x2C, 0x50, 0x264, 0x4C };

        /// @brief Offsets for TIQ running on Flash Player 32
        const std::vector<DWORD_PTR> FL32_OFFSETS = { 0xC951F8, 0xEA8, 0x10, 0x2C, 0xB08, 0x4C };

        /// @brief Offsets for TIQ running on Flash Player 11 SA
        const std::vector<DWORD_PTR> FL11SA_OFFSETS = { 0x7336D0, 0x420, 0xE8 };
    }

}
