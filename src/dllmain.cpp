#include <Windows.h>
#include <main.h>
#include <cstdio>
#include <ctime>
#include "script.hpp"
#include "keyboard.hpp"

#pragma comment(lib, "ScriptHookV.lib")

void mainScript()
{
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
        scriptUnregister(mainScript);
        keyboardHandlerUnregister(OnKeyboardMessage);
        break;

    default:
        break;
    }

    return TRUE;
}