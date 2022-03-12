#include <windows.h>
#include <fstream>

#include "ModLoader.h"

FARPROC originalFunctions[18];
HINSTANCE originalDll = 0;

DWORD WINAPI LoaderThread(LPVOID lpParam)
{
	std::string systemPath = "";
	char dummy[1];
	UINT pathLength = GetSystemDirectoryA(dummy, 1);
	systemPath.resize(pathLength);
	LPSTR lpSystemPath = const_cast<char*>(systemPath.c_str());
	GetSystemDirectoryA(lpSystemPath, systemPath.size());
	systemPath = lpSystemPath;
	originalDll = LoadLibraryA("mods\\dinput8.dll");
	if (!originalDll)
	{
		originalDll = LoadLibraryA(std::string(systemPath + "\\dinput8.dll").c_str());
	}

	if (originalDll)
	{
		// Set function addresses we need for forward exporting
		originalFunctions[0] = GetProcAddress(originalDll, "DirectInput8Create");
		originalFunctions[1] = GetProcAddress(originalDll, "DllCanUnloadNow");
		originalFunctions[2] = GetProcAddress(originalDll, "DllGetClassObject");
		originalFunctions[3] = GetProcAddress(originalDll, "DllRegisterServer");
		originalFunctions[4] = GetProcAddress(originalDll, "DllUnregisterServer");
		originalFunctions[5] = GetProcAddress(originalDll, "GetdfDIJoystick");
	}
	else
	{
		return false;
	}

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

	static ModLoader loader;
	loader.LoadMods();
	return S_OK;
}

extern "C"
{
	FARPROC address = NULL;
	int AsmJump();

	void PROXY_DirectInput8Create()
	{
		address = originalFunctions[0];
		AsmJump();
	}
	void PROXY_DllCanUnloadNow()
	{
		address = originalFunctions[1];
		AsmJump();
	}
	void PROXY_DllGetClassObject()
	{
		address = originalFunctions[2];
		AsmJump();
	}
	void PROXY_DllRegisterServer()
	{
		address = originalFunctions[3];
		AsmJump();
	}
	void PROXY_DllUnregisterServer()
	{
		address = originalFunctions[4];
		AsmJump();
	}
	void PROXY_GetdfDIJoystick()
	{
		address = originalFunctions[5];
		AsmJump();
	}
}

BOOL WINAPI DllMain(HINSTANCE module, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(module);
		CreateThread(0, 0, &LoaderThread, 0, 0, NULL);
	}

	if (reason == DLL_PROCESS_DETACH)
	{
		FreeLibrary(module);
		return 1;
	}

	return 1;
}