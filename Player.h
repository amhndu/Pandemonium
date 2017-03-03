#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "SpriteSheet.h"
#include <SFML/Graphics.hpp>

class Player : public GameObject
{
public:
    Player();
    void handleCollision(GameObject& other) override;
    void setActive(bool active) override;
    sf::Vector2f getPosition() override;
    void setPosition(float x, float y) override;
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    SpriteSheet m_sprite;
    sf::Vector2f m_position;
    float m_z;
};

#endif // PLAYER_H
