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
	originalDll = LoadLibraryA(".mods\\d3d12.dll");
	if (!originalDll)
	{
		originalDll = LoadLibraryA(std::string(systemPath + "\\D3D12.dll").c_str());
	}

	if (originalDll)
	{
		// Set function addresses we need for forward exporting
		originalFunctions[0] = GetProcAddress(originalDll, "D3D12CoreCreateLayeredDevice");
		originalFunctions[1] = GetProcAddress(originalDll, "D3D12CoreGetLayeredDeviceSize");
		originalFunctions[2] = GetProcAddress(originalDll, "D3D12CoreRegisterLayers");
		originalFunctions[3] = GetProcAddress(originalDll, "D3D12CreateDevice");
		originalFunctions[4] = GetProcAddress(originalDll, "D3D12CreateRootSignatureDeserializer");
		originalFunctions[5] = GetProcAddress(originalDll, "D3D12CreateVersionedRootSignatureDeserializer");
		originalFunctions[6] = GetProcAddress(originalDll, "D3D12DeviceRemovedExtendedData");
		originalFunctions[7] = GetProcAddress(originalDll, "D3D12EnableExperimentalFeatures");
		originalFunctions[8] = GetProcAddress(originalDll, "D3D12GetDebugInterface");
		originalFunctions[9] = GetProcAddress(originalDll, "D3D12GetInterface");
		originalFunctions[10] = GetProcAddress(originalDll, "D3D12PIXEventsReplaceBlock");
		originalFunctions[11] = GetProcAddress(originalDll, "D3D12PIXGetThreadInfo");
		originalFunctions[12] = GetProcAddress(originalDll, "D3D12PIXNotifyWakeFromFenceSignal");
		originalFunctions[13] = GetProcAddress(originalDll, "D3D12PIXReportCounter");
		originalFunctions[14] = GetProcAddress(originalDll, "D3D12SerializeRootSignature");
		originalFunctions[15] = GetProcAddress(originalDll, "D3D12SerializeVersionedRootSignature");
		originalFunctions[16] = GetProcAddress(originalDll, "GetBehaviorValue");
		originalFunctions[17] = GetProcAddress(originalDll, "SetAppCompatStringPointer");
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

	void PROXY_Ordinal99()
	{
		address = originalFunctions[0];
		AsmJump();
	}
	void PROXY_D3D12CoreCreateLayeredDevice() {
		address = originalFunctions[0];
		AsmJump();
	}
	void PROXY_D3D12CoreGetLayeredDeviceSize() {
		address = originalFunctions[1];
		AsmJump();
	}
	void PROXY_D3D12CoreRegisterLayers() {
		address = originalFunctions[2];
		AsmJump();
	}
	void PROXY_D3D12CreateDevice() {
		address = originalFunctions[3];
		AsmJump();
	}
	void PROXY_D3D12CreateRootSignatureDeserializer() {
		address = originalFunctions[4];
		AsmJump();
	}
	void PROXY_D3D12CreateVersionedRootSignatureDeserializer() {
		address = originalFunctions[5];
		AsmJump();
	}
	void PROXY_D3D12DeviceRemovedExtendedData() {
		address = originalFunctions[6];
		AsmJump();
	}
	void PROXY_D3D12EnableExperimentalFeatures() {
		address = originalFunctions[7];
		AsmJump();
	}
	void PROXY_D3D12GetDebugInterface() {
		address = originalFunctions[8];
		AsmJump();
	}
	void PROXY_D3D12GetInterface() {
		address = originalFunctions[9];
		AsmJump();
	}
	void PROXY_D3D12PIXEventsReplaceBlock() {
		address = originalFunctions[10];
		AsmJump();
	}
	void PROXY_D3D12PIXGetThreadInfo() {
		address = originalFunctions[11];
		AsmJump();
	}
	void PROXY_D3D12PIXNotifyWakeFromFenceSignal() {
		address = originalFunctions[12];
		AsmJump();
	}
	void PROXY_D3D12PIXReportCounter() {
		address = originalFunctions[13];
		AsmJump();
	}
	void PROXY_D3D12SerializeRootSignature() {
		address = originalFunctions[14];
		AsmJump();
	}
	void PROXY_D3D12SerializeVersionedRootSignature() {
		address = originalFunctions[15];
		AsmJump();
	}
	void PROXY_GetBehaviorValue() {
		address = originalFunctions[16];
		AsmJump();
	}
	void PROXY_SetAppCompatStringPointer() {
		address = originalFunctions[17];
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

	return 1;
}