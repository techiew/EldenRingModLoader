#include "ModLoader.h"

void ModLoader::LoadMods()
{
    m_logger.Log("Loading mods...");
    size_t modCount = 0;
    CreateDirectoryA(m_modFolder.c_str(), NULL);
    for (auto& file : std::filesystem::recursive_directory_iterator(m_modFolder))
    {
        if (file.path().extension() == ".dll")
        {
            std::string modName = file.path().stem().string();
            std::string dllName = file.path().stem().string() + ".dll";
            m_logger.Log("Loading %s...", dllName.c_str());
            if (LoadLibraryA(std::string(m_modFolder + "\\" + dllName).c_str()))
            {
                m_logger.Log("Successfully loaded %s", dllName.c_str());
                std::string directory = m_modFolder + "\\" + modName;
                CreateDirectoryA(directory.c_str(), NULL);
            }
            else
            {
                m_logger.Log("Failed to load %s", dllName.c_str());
                MessageBox(NULL, std::string("Failed to load " + dllName).c_str(), "Mod Loader", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
            }
            modCount++;
        }
    }
    m_logger.Log("Loaded %i mods", modCount);
    m_logger.Close();
}