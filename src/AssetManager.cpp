#include "AssetManager.hpp"

#include "Logger.hpp"
#include "Texture.hpp"
#include "Renderer.hpp"
#include "Core.hpp"

AssetManager::AssetManager() : m_Size(0)
{
    
}

AssetManager::AssetManager(const std::string& assets_folder) : m_Size(0)
{
    this->SetAssetsFolder(assets_folder);
}

AssetManager::~AssetManager()
{
    
}

void AssetManager::SetAssetsFolder(const std::string& assets_folder)
{
    m_AssetsFolder = assets_folder;
}

uint32_t AssetManager::GetAssetsSize() const
{
    return m_Size;
}

bool AssetManager::LoadAssets(const Core::Ref<Renderer> renderer)
{
    if(m_AssetsFolder.empty()){
        STELLAR_CORE_ERROR("Assets folder doesn't specified. Filename: {0}, line: {1}", STELLAR_FILENAME, STELLAR_LINE);
    }
    
    std::filesystem::path root_assets_path = m_AssetsFolder;

    if(!std::filesystem::exists(root_assets_path)){
        STELLAR_CORE_ERROR("Folder doesn't exist. Filename: {0}, line: {1}", STELLAR_FILENAME, STELLAR_LINE);
        return false;
    }

    if(std::filesystem::is_empty(root_assets_path)){
        STELLAR_CORE_ERROR("Folder is empty. Filename: {0}, line: {1}", STELLAR_FILENAME, STELLAR_LINE);
        return false;
    }

    for (const auto& dir_entry : std::filesystem::recursive_directory_iterator(root_assets_path)){
        const auto& entry_path = dir_entry.path();

        if(entry_path.has_extension() && entry_path.has_filename()){
         
         m_AssetsMap.insert(std::make_pair(entry_path.filename().generic_string(),Core::CreateRef<Texture>(renderer,entry_path.string())));
         ++m_Size;
         
         STELLAR_CORE_INFO("Asset has been successfully loaded. Asset name: {0}, extension: {1}",entry_path.filename().string(),entry_path.extension().string());
       }
    }

    return true;
}
