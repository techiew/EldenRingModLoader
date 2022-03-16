#pragma once
#include <fstream>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <libloaderapi.h>

#include "Logger.h"

class ModLoader
{
public:
	void LoadDllMods();
	void OnLoadingDone();

private:
	Logger m_logger{ "EldenModLoader" };
	std::string m_modFolder = ".\\mods";
};