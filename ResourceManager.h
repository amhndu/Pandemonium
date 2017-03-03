#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <memory>
#include <map>

// Singleton generic resource manager
template <typename Resource, typename Identifier>
class ResourceManager
{
    public:
        static bool load(Identifier id, const std::string& file)
        {
            if (!m_instance)
                m_instance.reset(new ResourceManager);

            return m_instance->m_resources[id].loadFromFile(file);
        }

        static Resource& get(Identifier id)
        {
            if (!m_instance)
                m_instance.reset(new ResourceManager);
            auto found = m_instance->m_resources.find(id);
            if (found == m_instance->m_resources.end())
                throw std::runtime_error("Resource not found");

            return found->second;
        }
    private:
        std::map<Identifier, Resource> m_resources;
        static std::unique_ptr<ResourceManager> m_instance;
};

#include "ResourceIdentifiers.h"

using TextureManager = ResourceManager<sf::Texture, TextureIdentifier>;
using FontManager = ResourceManager<sf::Font, FontIdentifier>;


#endif // RESOURCEMANAGER_H
