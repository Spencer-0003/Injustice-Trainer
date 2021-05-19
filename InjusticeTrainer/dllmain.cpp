/*
    Injustice Gods Among Us Trainer
    Made for personal usage by Spencer-0003

    Might make one for Injustice 2 next :shrug:
*/

#include <Windows.h>
#include "mem.h"
#include "offsets.h"

#include <cstdio>
#include <iostream>

DWORD WINAPI MainThread(HMODULE hMod)
{
    // Info text for console
    const char* info =
        "Hotkeys:\n"
        "Refill shield - Numpad 1\n"
        "Refill health - Numpad 2\n"
        "Refill ability bar - Numpad 3\n"
        "Kill player two - Numpad 4\n"
        "Exit cheat - End";

    // Create console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    SetConsoleTitle(L"Injustice Trainer by Spencer-0003");

    std::cout << info;

    // Get base
    //uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandle(L"Injustice.exe"));
    uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));

    // Main loop
    while (true)
    {
        if (GetAsyncKeyState(VK_END) && 0x1) // Exit cheat
        {
            break;
        }
        else if (GetAsyncKeyState(VK_NUMPAD1) && 0x1) // Refill shield
        {
            uintptr_t shield = mem::FindDMAAddy(base + playerOneHealthBar, { playerOneShield });
            if (shield == 900) continue;

            *(float*)(shield) = 1;
        }
        else if (GetAsyncKeyState(VK_NUMPAD2) && 0x1) // Refill health
        {
            uintptr_t health = mem::FindDMAAddy(base + playerOneHealthBar, { playerOneHealth });
            if (health == 904) continue;

            *(float*)(health) = 1;
        }
        else if (GetAsyncKeyState(VK_NUMPAD3) && 0x1) // Refill ability bar
        {
            uintptr_t ability = mem::FindDMAAddy(base + playerOneAbilityBar, { playerOneAbility });
            if (ability == 752) continue;

            *(float*)(ability) = 1;
        }
        else if (GetAsyncKeyState(VK_NUMPAD4) && 0x1) // Kill player two
        {
            uintptr_t shield = mem::FindDMAAddy(base + playerTwoHealthBar, { playerTwoShield });
            uintptr_t health = mem::FindDMAAddy(base + playerTwoHealthBar, { playerTwoHealth });
            if (shield == 900) continue;

            *(float*)(shield) = 0;
            *(float*)(health) = 0;
        };
    };

    /*if (f != 0) fclose(f); // Looks bad but it fixes a warning in VS
    FreeConsole();
    FreeLibraryAndExitThread(hMod, 0);*/

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
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

