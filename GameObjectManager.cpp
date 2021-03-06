#include "GameObjectManager.h"
#include <iostream>

void GameObjectManager::render(sf::RenderTarget& target)
{
    for (auto& go : m_objects)
        target.draw(*(go.second.get()));
}

GameObject* GameObjectManager::get(const std::string& key)
{
    auto found = m_objects.find(key);
    if (found != m_objects.end())
        return found->second.get();

    return nullptr;
}

void GameObjectManager::handleEvent(const sf::Event& event)
{
    for (auto& go : m_objects)
        go.second->handleEvent(event);
}

void GameObjectManager::update(float dt)
{
    for (auto go = m_objects.begin(); go != m_objects.end(); )
    {
        go->second->update(dt);
        for (auto other = std::next(go); other != m_objects.end(); ++other)
            go->second->handleCollision(*other->second);

        if (go->second->toDestroy())
            go = m_objects.erase(go);
        else
            ++go;
    }
}

void GameObjectManager::setActive(bool active)
{
    for (auto& go : m_objects)
        go.second->setActive(active);
}

GameObject* GameObjectManager::insert(const std::string& key, GameObject* obj)
{
    auto res = m_objects.emplace(key, std::unique_ptr<GameObject>(obj));

    if (res.second)
        return obj;
    return nullptr;
}

void GameObjectManager::clear()
{
    m_objects.clear();
}
