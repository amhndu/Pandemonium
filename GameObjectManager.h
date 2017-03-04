#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H
#include "GameObject.h"
#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics/RenderTarget.hpp>

class GameObjectManager
{
public:
    // Ownership of obj is transferred to the manager
    GameObject* insert(const std::string& key, GameObject* obj);
    GameObject* get(const std::string& key);

    void update(float dt);
    void handleEvent(const sf::Event& event);
    void render(sf::RenderTarget& target);
    void setActive(bool active);
    void clear();

    template <typename Callable>
    void foreach(Callable c)
    {
        for (auto &p : m_objects)
            c(*p.second);
    }
private:
    std::map<std::string, std::unique_ptr<GameObject>> m_objects;
};

#endif // GAMEOBJECTMANAGER_H
