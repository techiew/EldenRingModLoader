#include "ModLoader.h"


void ModLoader::LoadMods()
{
    ReadConfigFile();
    LoadDllMods();
    OnLoadingDone();
}

INIFile config("mod_loader_config.ini");;
INIStructure ini;

void ModLoader::ReadConfigFile()
{

    if (config.read(ini))
    {
        m_loadDelay = std::stoi(ini["modloader"].get("load_delay"));
        m_showTerminal = std::stoi(ini["modloader"].get("show_terminal")) != 0;

    }
    else
    {
        ini["modloader"]["load_delay"] = std::to_string(m_loadDelay);
        ini["modloader"]["show_terminal"] = std::to_string(m_showTerminal);
        config.write(ini, true);
    }

    if (m_showTerminal)
    {
        OpenTerminal();
    }


    m_logger.Log("Load delay: %i", m_loadDelay);
    m_logger.Log("Show terminal: %i", m_showTerminal);
}

std::vector<std::pair<int64_t, std::string>> ModLoader::FindModsAndReadLoadOrders()
{
    m_logger.Log("Finding mods...");
    std::vector<std::pair<int64_t, std::string>> dllMods;
    constexpr int automaticLoadOrder = -1;
    fs::create_directories(m_modFolder);

    for (auto file : fs::recursive_directory_iterator(m_modFolder))
    {
        if (file.is_regular_file())
        {

            fs::path extension = file.path().extension();
            fs::path path = file.path().parent_path();
            if (extension == ".dll" && path == m_modFolder)
            {
                std::string modName = file.path().stem().string();
                int64_t loadOrder = automaticLoadOrder;
                std::string load = ini["loadorder"].get(modName);

                if (load == "") {
                    load = ini["loadorder"].get(modName + ".dll");
                }

                if (load != "") {
                    loadOrder = stoi(load);
                }

                printf("%s = %d\n", modName, loadOrder);
				/* std::ifstream loadOrderFile(m_modFolder + "\\" + modName + "\\load.txt", std::ios::binary);
                if (loadOrderFile.is_open())
                {
                    std::string line = "";
                    getline(loadOrderFile, line);
                    std::stringstream stringStream(line);
                    stringStream >> loadOrder;
                }*/

                dllMods.push_back(std::make_pair(loadOrder, modName + ".dll"));
            }
        }
    }


    for (auto& mod : dllMods)
    {
        if (mod.first == automaticLoadOrder)
        {
            mod.first = std::max_element(dllMods.begin(), dllMods.end())->first + 1;
			if (mod.first == 0)
			{
				mod.first = 1;
			}
        }
    }

    std::sort(dllMods.begin(), dllMods.end());
    return dllMods;
}

void ModLoader::LoadDllMods()
{
	m_logger.Log("Loading .dll mods...");

    auto dllMods = FindModsAndReadLoadOrders();
	size_t modCount = 0;
	bool hasSlept = false;
	constexpr int loadInstantly = 0;
    for (size_t i = 0; i < dllMods.size(); i++)
    {
        int64_t loadOrder = dllMods[i].first;
        std::string dllName = dllMods[i].second;

		if (loadOrder != loadInstantly && hasSlept == false)
		{
			Sleep(m_loadDelay);
			hasSlept = true;
		}

        m_logger.Log("Loading %s...", dllName.c_str());
        if (LoadLibraryA(std::string(m_modFolder + "\\" + dllName).c_str()))
        {
			bool nextModHasSameLoadOrder = i != dllMods.size() - 1 && dllMods[i + 1].first == loadOrder;
            if (nextModHasSameLoadOrder == false)
            {
                Sleep(1000);
            }
            modCount++;
        }
        else
        {
            m_logger.Log("Failed to load %s", dllName.c_str());
            MessageBox(NULL, std::string("Failed to load " + dllName).c_str(), "Elden Mod Loader", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
        }
    }
    m_logger.Log("Loaded %i .dll mods", modCount);
}

void ModLoader::OpenTerminal()
{
    if (AllocConsole())
    {
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        SetWindowText(GetConsoleWindow(), "Elden Mod Loader");
    }
}

void ModLoader::OnLoadingDone()
{
    m_logger.Close();
}