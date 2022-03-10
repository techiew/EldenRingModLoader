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
	void LoadMods();
private:
	Logger m_logger{ "EldenRingModLoader" };
	std::string m_modFolder = ".\\mods";
};