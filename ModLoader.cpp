#include "ModLoader.h"

void ModLoader::LoadMods()
{
    m_logger.Log("Loading mods...");
    size_t modCount = 0;
    for (auto& file : std::filesystem::recursive_directory_iterator(m_modFolder))
    {
        if (file.path().extension() == ".dll")
        {
            std::string modName = file.path().stem().string() + ".dll";
            m_logger.Log("Loading %s...", modName);
            if (LoadLibraryA(std::string(m_modFolder + "\\" + modName).c_str()))
            {
                m_logger.Log("Successfully loaded %s", modName);
            }
            else
            {
                m_logger.Log("Failed to load %s", modName);
                MessageBox(NULL, std::string("Failed to load " + modName).c_str(), "Mod Loader", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
            }
            modCount++;
        }
    }
    m_logger.Log("Loaded %i mods", modCount);
}