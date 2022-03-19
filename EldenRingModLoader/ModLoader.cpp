#include "ModLoader.h"

void ModLoader::LoadDllMods()
{
    m_logger.Log("Loading .dll mods...");
    size_t modCount = 0;
    fs::create_directories(m_modFolder);
    for (auto& file : fs::recursive_directory_iterator(m_modFolder))
    {
        // Should be a regular file only
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
                    MessageBox( NULL, std::string("Failed to load " + dllName.string()).c_str(), "Mod Loader", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
                }
                modCount++;
            }
        }
    }
    m_logger.Log("Loaded %i .dll mods", modCount);
}

void ModLoader::OnLoadingDone()
{
    m_logger.Close();
}
