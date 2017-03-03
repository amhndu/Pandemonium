#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "SpriteSheet.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

class Enemy : public GameObject
{
public:
    Enemy(Player &player);
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
    int m_z;
    float m_frameTimer;
    int m_frame;
    Player& m_player;
    
};
#endif // ENEMY_H
