#include <windows.h>
#include <fstream>

#include "ModLoader.h"

#pragma comment(linker, "/export:DirectInput8Create")
#pragma comment(linker, "/export:DllCanUnloadNow,PRIVATE")
#pragma comment(linker, "/export:DllGetClassObject,PRIVATE")
#pragma comment(linker, "/export:DllRegisterServer,PRIVATE")
#pragma comment(linker, "/export:DllUnregisterServer,PRIVATE")
#pragma comment(linker, "/export:GetdfDIJoystick")

// Opaque pointer for dinput8 type
typedef void* LPCDIDATAFORMAT;

// dinput8 function signatures
typedef HRESULT(WINAPI* DirectInput8CreateProc)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);
typedef HRESULT(WINAPI* DllCanUnloadNowProc)();
typedef	HRESULT(WINAPI* DllGetClassObjectProc)(REFCLSID, REFIID, LPVOID*);
typedef HRESULT(WINAPI* DllRegisterServerProc)();
typedef HRESULT(WINAPI* DllUnregisterServerProc)();
typedef	LPCDIDATAFORMAT(WINAPI* GetdfDIJoystickProc)();

// dinput8 procedure pointers
DirectInput8CreateProc pDirectInput8Create;
DllCanUnloadNowProc pDllCanUnloadNow;
DllGetClassObjectProc pDllGetClassObject;
DllRegisterServerProc pDllRegisterServer;
DllUnregisterServerProc pDllUnregisterServer;
GetdfDIJoystickProc pGetdfDIJoystick;

DWORD WINAPI LoaderThread(LPVOID lpParam)
{
	LoadLibraryA("psapi.dll");
	ModLoader loader;
	loader.LoadMods();
	return S_OK;
}

BOOL WINAPI DllMain(HINSTANCE module, DWORD reason, LPVOID)
{
	static HMODULE hmDinput = nullptr;

	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(module);

		// Load original dinput8.dll
		char path[MAX_PATH];
		if (!GetSystemDirectoryA(path, MAX_PATH))
			return false;

		strcat_s(path, "\\dinput8.dll");

		hmDinput = LoadLibraryA(path);
		if (!hmDinput)
			return false;

		// Get original procedures
		pDirectInput8Create = (DirectInput8CreateProc)GetProcAddress(hmDinput, "DirectInput8Create");
		pDllCanUnloadNow = (DllCanUnloadNowProc)GetProcAddress(hmDinput, "DllCanUnloadNow");
		pDllGetClassObject = (DllGetClassObjectProc)GetProcAddress(hmDinput, "DllGetClassObject");
		pDllRegisterServer = (DllRegisterServerProc)GetProcAddress(hmDinput, "DllRegisterServer");
		pDllUnregisterServer = (DllUnregisterServerProc)GetProcAddress(hmDinput, "DllUnregisterServer");
		pGetdfDIJoystick = (GetdfDIJoystickProc)GetProcAddress(hmDinput, "GetdfDIJoystick");

		// Create loader thread
		CreateThread(0, 0, &LoaderThread, 0, 0, NULL);
	}

	if (reason == DLL_PROCESS_DETACH)
		FreeLibrary(hmDinput);

	return true;
}

// dinput8.dll forwarders
extern "C" HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, LPUNKNOWN punkOuter)
{
	if (!pDirectInput8Create)
		return E_FAIL;

	return pDirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}

#pragma warning(suppress: 28251) // Ignore missing SAL annotation warning
extern "C" HRESULT WINAPI DllCanUnloadNow()
{
	if (!pDllCanUnloadNow)
		return E_FAIL;

	return pDllCanUnloadNow();
}

#pragma warning(suppress: 28251) // Ignore missing SAL annotation warning
extern "C" HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID * ppv)
{
	if (!pDllGetClassObject)
		return E_FAIL;

	return pDllGetClassObject(rclsid, riid, ppv);
}

extern "C" HRESULT WINAPI DllRegisterServer()
{
	if (!pDllRegisterServer)
		return E_FAIL;

	return pDllRegisterServer();
}

extern "C" HRESULT WINAPI DllUnregisterServer()
{
	if (!pDllUnregisterServer)
		return E_FAIL;

	return pDllUnregisterServer();
}

extern "C" LPCDIDATAFORMAT WINAPI GetdfDIJoystick()
{
	if (!pGetdfDIJoystick)
		return nullptr;

	return pGetdfDIJoystick();
}
