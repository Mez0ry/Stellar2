#ifndef __ASSET_MANAGER_HPP__
#define __ASSET_MANAGER_HPP__

#include <filesystem>
#include <unordered_map>
#include <memory>
#include <string>
#include <cstdint>

namespace Core {
    template <typename T>
    using Ref = std::shared_ptr<T>;
}//!Core

class Texture;
class Renderer;

class AssetManager{
public:
    AssetManager();
    AssetManager(const std::string& assets_folder);

    ~AssetManager();
    
    AssetManager(const AssetManager &) = delete;
    AssetManager(AssetManager &&) = delete;
    AssetManager &operator=(const AssetManager &) = delete;
    AssetManager &operator=(AssetManager &&) = delete;

    void SetAssetsFolder(const std::string& assets_folder);

    uint32_t GetAssetsSize() const;
    
    /**
     * @brief Loads assets from assets folder
     * @tparam renderer required in texture loading
     * @return true if assets were loaded, false otherwise
     */
    bool LoadAssets(const Core::Ref<Renderer> renderer);
private:
    std::unordered_map<std::string,Core::Ref<Texture>> m_AssetsMap;
    std::string m_AssetsFolder;
    uint32_t m_Size;
};

#endif //!__ASSET_MANAGER_HPP__