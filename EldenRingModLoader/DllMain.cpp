#include <windows.h>
#include <fstream>

#include "ModLoader.h"

#pragma comment(linker, "/export:DirectInput8Create=C:\\\\Windows\\\\System32\\\\dinput8.dll.DirectInput8Create")
#pragma comment(linker, "/export:DllCanUnloadNow=C:\\\\Windows\\\\System32\\\\dinput8.dll.DllCanUnloadNow,PRIVATE")
#pragma comment(linker, "/export:DllGetClassObject=C:\\\\Windows\\\\System32\\\\dinput8.dll.DllGetClassObject,PRIVATE")
#pragma comment(linker, "/export:DllRegisterServer=C:\\\\Windows\\\\System32\\\\dinput8.dll.DllRegisterServer,PRIVATE")
#pragma comment(linker, "/export:DllUnregisterServer=C:\\\\Windows\\\\System32\\\\dinput8.dll.DllUnregisterServer,PRIVATE")
#pragma comment(linker, "/export:GetdfDIJoystick=C:\\\\Windows\\\\System32\\\\dinput8.dll.GetdfDIJoystick")

DWORD WINAPI LoaderThread(LPVOID lpParam)
{
	// The mods use psapi functions and the psapi might not be loaded when we need it (game loads it at some point)?
	// Loading it in the loader is probably cleaner than making it an explicit dependency for all mods...
	LoadLibraryA("psapi.dll"); 

	std::fstream terminalEnableFile;
	terminalEnableFile.open("loader_enable_terminal.txt", std::fstream::in);
	if (terminalEnableFile.is_open())
	{
		if (AllocConsole())
		{
			freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
			SetWindowText(GetConsoleWindow(), "Elden Mod Loader");
		}
		terminalEnableFile.close();
	}

	ModLoader loader;
	loader.LoadDllMods();
	loader.OnLoadingDone();
	return S_OK;
}

BOOL WINAPI DllMain(HINSTANCE module, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(module);
		CreateThread(0, 0, &LoaderThread, 0, 0, NULL);
	}
	return 1;
}