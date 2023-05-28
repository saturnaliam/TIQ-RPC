// Get module base, used when we need to.. get the module's base address. no shit

#include "tiq.hpp"

/// @brief Finds the base address of a given window
/// @param PID The window's proceess ID
/// @param windowHandle The window's handle
/// @param executableName The name of the window's executable
/// @return The window's base address
uintptr_t TIQ::getModuleBase(DWORD PID, const HWND windowHandle, wchar_t* executableName) {
    // Finding the PID of our given window handle
    DWORD processIdFound = 0;
    GetWindowThreadProcessId(windowHandle, &processIdFound);
    if (processIdFound != PID) return 0;

    // Opens the process
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
    if (!processHandle) return 0;

    // black magic
    MODULEENTRY32 moduleEntry = { sizeof(moduleEntry) };
    uintptr_t moduleBaseAddress = 0;
    HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, PID);
    if (Module32First(snapshotHandle, &moduleEntry)) {
        do
        {
            if (_wcsicmp(moduleEntry.szModule, executableName) == 0) moduleBaseAddress = reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
        } while (Module32Next(snapshotHandle, &moduleEntry));
    }

    // memory safety
    CloseHandle(snapshotHandle);
    CloseHandle(processHandle);

    return moduleBaseAddress;
}
