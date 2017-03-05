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
    enum WeaponType
    {
        CrowBar,
        CrossBow
    };
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

    void changeWeapon();
    WeaponType getWeaponType();

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    void attackEnemy(Enemy& enemy);

    SpriteSheet m_sprite;

    sf::Vector2f m_position;
    float m_z;

    float m_frameTimer;
    float m_health;
    bool m_jumping;
    bool m_attacking;
    bool m_colliding;

    std::vector<std::vector<int>> m_animationframe;
    std::size_t m_currentAnimation;
    std::size_t m_frame;

    GameObjectManager &m_gameObjects;
    bool m_flip;
    float m_redTimer;
    std::function<void(void)> m_cb;

    WeaponType m_currentWeapon;
};

#endif // PLAYER_H
