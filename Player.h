#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "SpriteSheet.h"
#include "GameObjectManager.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Enemy;

class Player : public GameObject
{
public:
    Player(GameObjectManager& gom);
    void handleCollision(GameObject& other) override;
    void setActive(bool active) override;
    sf::Vector2f getPosition() override;
    void setPosition(float x, float y) override;  // y is the baseline axis where z = 0, x is the normal co-ordinate
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    float getZ();
    int getHealth();
    void setZ(int z);
    void inflictDamage(int damage);
    template <typename Callable>
    void setDeathCallback(Callable f)
    {
        m_cb = f;
    }
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    void attackEnemy(Enemy& enemy);

    SpriteSheet m_sprite;
    sf::Vector2f m_position;
    float m_z;
    float m_frameTimer;
    bool m_jumping;
    float m_health;
    std::vector<std::vector<int>> m_animationframe;
    std::size_t m_currentAnimation;
    std::size_t m_frame;
    bool m_attacking;
    bool m_colliding;
    GameObjectManager &m_gameObjects;
    bool m_flip;
    float m_timer;
    std::function<void(void)> m_cb;
};

#endif // PLAYER_H
