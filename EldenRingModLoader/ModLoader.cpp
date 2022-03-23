#include "ModLoader.h"

void ModLoader::ReadConfigFile()
{
    INIFile config("mod_loader_config.ini");
    INIStructure ini;

    if (config.read(ini))
    {
        loadDelay = std::stoi(ini["modloader"].get("load_delay"));
        showTerminal = std::stoi(ini["modloader"].get("show_terminal")) != 0;
    }
    else
    {
        ini["modloader"]["load_delay"] = std::to_string(loadDelay);
        ini["modloader"]["Show_Terminal"] = std::to_string(showTerminal);
        config.write(ini, true);
    }

    if (showTerminal)
    {
        OpenTerminal();
    }

    m_logger.Log("Load delay: %i", loadDelay);
    m_logger.Log("Show terminal: %i", showTerminal);
}

void ModLoader::LoadDllMods()
{
    m_logger.Log("Loading .dll mods...");
    size_t modCount = 0;
    fs::create_directories(m_modFolder);
    for (auto& file : fs::recursive_directory_iterator(m_modFolder))
    {
        if (fs::is_regular_file(file))
        {
            fs::path extension = file.path().extension();
            fs::path path = file.path().parent_path();
            if (extension == ".dll" && path == m_modFolder)
            {
                fs::path dllName = file.path().stem() += ".dll";
                m_logger.Log("Loading %s...", dllName.string().c_str());
                if (LoadLibraryW(file.path().c_str()))
                {
                    Sleep(1000);
                }
                else
                {
                    m_logger.Log("Failed to load %s", dllName.string().c_str());
                    MessageBox( NULL, std::string("Failed to load " + dllName.string()).c_str(), "Elden Mod Loader", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
                }
                modCount++;
            }
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

void ModLoader::WhenLoadingDone()
{
    m_logger.Close();
}
