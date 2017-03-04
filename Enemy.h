#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "SpriteSheet.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <functional>

class Enemy : public GameObject
{
public:
    enum Type
    {
        Easy,
        Medium,
        Boss
    };
    Enemy(Type type, Player &player);
    void handleCollision(GameObject& other) override;
    void setActive(bool active) override;
    sf::Vector2f getPosition() override;
    void setPosition(float x, float y) override;
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    bool toDestroy() override;
    void setZ(int z);

    template <typename Callable>
    void setDeathCallback(Callable f){ m_deathCallback = f; };
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    std::function<void(void)> m_deathCallback;
    Type m_type;
    SpriteSheet m_sprite;
    sf::Vector2f m_position;
    float m_z;
    float m_frameTimer;
    int m_frame;
    Player& m_player;
    int m_health;

};
#endif // ENEMY_H
