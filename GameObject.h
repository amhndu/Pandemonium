#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>


class GameObject : public sf::Drawable
{
public:
    enum Type
    {
        Button,
        HUD,
        PlayerObject,
        EnemyObject,
        Projectile
    };

    GameObject(Type type) : m_type(type), m_active(true) {};
    virtual ~GameObject() {};

    virtual void update(float dt) = 0;
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual sf::Vector2f getPosition() = 0;
    virtual void setActive(bool active) = 0;
    virtual void handleCollision(GameObject& other) = 0;
    Type inline getType() { return m_type; };
    virtual bool toDestroy() { return false; };

protected:
    Type m_type;
    bool m_active;
};

#endif //GAMEOBJECT_H