#include "ModLoader.h"

void ModLoader::LoadDllMods()
{
    m_logger.Log("Loading .dll mods...");
    size_t modCount = 0;
    CreateDirectoryA(m_modFolder.c_str(), NULL);
    for (auto& file : std::filesystem::recursive_directory_iterator(m_modFolder))
    {
        std::string extension = file.path().extension().string();
        std::string path = file.path().parent_path().string();
        if (extension == ".dll" && path == m_modFolder)
        {
            std::string dllName = file.path().stem().string() + ".dll";
            m_logger.Log("Loading %s...", dllName.c_str());
            if (LoadLibraryA(std::string(path + "\\" + dllName).c_str()))
            {
                Sleep(1000);
            }
            else
            {
                m_logger.Log("Failed to load %s", dllName.c_str());
                MessageBox(NULL, std::string("Failed to load " + dllName).c_str(), "Mod Loader", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
            }
            modCount++;
        }
    }
    m_logger.Log("Loaded %i .dll mods", modCount);
}

void ModLoader::OnLoadingDone()
{
    m_logger.Close();
}
