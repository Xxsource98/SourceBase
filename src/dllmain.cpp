/*
    Last Update Date: 2021-07-28
    Trainer Base Created by: Xxsource98
    Github Link: https://github.com/Xxsource98/SourceBase
    Project License: GNU General Public License v3.0
    Base Version: 1.1
*/

#include <Windows.h>
#include <main.h>
#include <cstdio>
#include <ctime>
#include "script.hpp"
#include "keyboard.hpp"
#include "utils.hpp"

#pragma comment(lib, "ScriptHookV.lib")

void mainScript()
{
    ENABLE_CONSOLE;
    srand((unsigned int)time(0));
    Source::MainLoop();
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved)  // reserved
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        scriptRegister(hinstDLL, mainScript);
        keyboardHandlerRegister(OnKeyboardMessage);
        break;

    case DLL_PROCESS_DETACH:
        FREE_CONSOLE;
        scriptUnregister(mainScript);
        keyboardHandlerUnregister(OnKeyboardMessage);
        break;

    default:
        break;
    }

    return TRUE;
}