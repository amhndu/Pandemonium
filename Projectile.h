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
    Projectile() ;
    void handleCollision(GameObject& other) override;
    void setActive(bool active) override;
    sf::Vector2f getPosition() override;
    void setPosition(float x, float y) override;
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void setVelocity(float val) ;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
private:
    float velocity ;
    sf::CircleShape m_circle ;   
};

#endif //PROJECTILE_H