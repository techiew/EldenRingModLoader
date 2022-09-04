#pragma once
#include <fstream>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <libloaderapi.h>
#include <string>

#include "Logger.h"
#include "ini.h"

namespace fs = std::filesystem;
using namespace mINI;

class ModLoader
{
public:
	void LoadMods();

private:
	Logger m_logger{ "EldenModLoader" };
	std::string m_modFolder = ".\\mods";
	DWORD m_loadDelay = 5000;
	bool m_showTerminal = false;

	void ReadConfigFile();
	std::vector<std::pair<int64_t, std::string>> FindModsAndReadLoadOrders();
	void LoadDllMods();
	void OpenTerminal();
	void OnLoadingDone();
	INIFile config = INIFile("mod_loader_config.ini");
	INIStructure ini;

};