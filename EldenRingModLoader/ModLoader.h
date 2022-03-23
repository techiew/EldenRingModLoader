#pragma once
#include <fstream>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <libloaderapi.h>

#include "Logger.h"
#include "ini.h"

namespace fs = std::filesystem;
using namespace mINI;

class ModLoader
{
public:
	void ReadConfigFile();
	void LoadDllMods();
	void OpenTerminal();
	void WhenLoadingDone();

private:
	Logger m_logger{ "EldenModLoader" };
	std::string m_modFolder = ".\\mods";
	DWORD loadDelay = 5000;
	bool showTerminal = false;
};