// Read memory

#include "tiq.hpp"

/// @brief Follows the pointer path given to find the end address to read
/// @param processWindow The process to read from
/// @param offsets All pointer offsets
/// @return The address given at the end of the path
DWORD_PTR TIQ::followPointerPath(TIQ::window processWindow, std::vector<DWORD_PTR> offsets) {
    SIZE_T bytesRead;
    DWORD_PTR address;

    int pointerValue = processWindow.baseAddress;

    for (int i = 0; i < offsets.size(); i++) {
        address = pointerValue;
        address += offsets[i];
        ReadProcessMemory(processWindow.processHandle, (LPVOID)address, &pointerValue, sizeof(pointerValue), &bytesRead);
    }

    return address;
}

/// @brief Gets the current scene TIQ is on
/// @param address Address to read from
/// @param processWindow The process to read from
/// @return The scene
int TIQ::getScene(DWORD_PTR address, TIQ::window processWindow) {
    SIZE_T bytesRead;
    int scene;

    ReadProcessMemory(processWindow.processHandle, (LPVOID)address, &scene, sizeof(scene), &bytesRead);

    return scene;
}
