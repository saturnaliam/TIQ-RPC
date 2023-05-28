// Window information

#include "tiq.hpp"

/// @brief Finds a window given some information
/// @param executableName The name of the executable
/// @param windowTitle The window's title
/// @return All the given information of the window
TIQ::window TIQ::findWindow(wchar_t* executableName, wchar_t* windowTitle) {
    DWORD PID;
    TIQ::window window;

    window.windowHandle = FindWindowW(nullptr, windowTitle);

    GetWindowThreadProcessId(window.windowHandle, &PID);
    window.PID = PID;

    window.processHandle = OpenProcess(PROCESS_VM_READ, FALSE, window.PID);

    window.baseAddress = TIQ::getModuleBase(window.PID, window.windowHandle, executableName);

    return window;
}
