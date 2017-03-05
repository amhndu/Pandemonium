#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"
#include "SpriteSheet.h"
#include <SFML/Graphics.hpp>

class Projectile : public GameObject
{
public:
    enum Type
    {
        Arrow,
        Bullet
    };
    Projectile(Type t, const sf::Vector2f& pos, float vel);
    void handleCollision(GameObject& other) override;
    void setActive(bool active) override;
    sf::Vector2f getPosition() override;
    void setPosition(float x, float y) override;
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    bool toDestroy() { return m_collided; };
    void setCollided();
    void setZ(float z) { m_z = z; };
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    float m_z;
    float m_velocity;
    sf::Sprite m_sprite;
    Type m_type;
    bool m_collided;
};

#endif //PROJECTILE_H