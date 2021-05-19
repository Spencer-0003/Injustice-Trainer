/*
    Injustice Gods Among Us Trainer
    Made for personal usage by Spencer-0003

    Might make one for Injustice 2 next :shrug:
*/

#include <Windows.h>
#include "mem.h"
#include <cstdio>
#include <iostream>
#include <string> 

DWORD WINAPI MainThread(HMODULE hMod)
{
    // Info text for console
    const char* info =
        "WARNING: Enabling features while not in a match will crash you!!!\n\n"
        "Hotkeys:\n"
        "Refill shield - Insert\n"
        "Refill health - Home";

    // Create console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONIN$", "r", stdin);
    freopen_s(&f, "CONOUT$", "w", stdout);

    SetConsoleTitle(L"Injustice Trainer by Spencer-0003");

    std::cout << info;

    // Get base
    uintptr_t base = (uintptr_t)GetModuleHandle(L"Injustice.exe");

    // Main loop
    while (true)
    {
        if (1) {
            if (GetAsyncKeyState(VK_INSERT))
            {
                uintptr_t shield = mem::FindDMAAddy(base + 0x030CFE1C, { 0x384 });
                int* _shield = (int*)shield;
                *_shield = 10e16; // Just a really big number to make sure it's full.
            }
            else if (GetAsyncKeyState(VK_HOME))
            {
                uintptr_t health = mem::FindDMAAddy(base + 0x030CFE1C, { 0x388 });
                int* _health = (int*)health;
                *_health = 10e16; // Just a really big number to make sure it's full. x2
            };
        };
    };

    return 1;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

