#include "Enemy.h"

void Enemy::handleCollision(GameObject& other)
{
    switch (other.getType())
    {
        case Button:
            break;
        case PlayerObject:
            // Do something
            break;
        case EnemyObject:
            // Do nothing ?
            break;
        case Projectile:
            // If colliding, then reduce armor/health
            break;
    }
}

void Enemy::setActive(bool active)
{
    m_active = active;
}

sf::Vector2f Enemy::getPosition()
{
    return m_sprite.getPosition();
}

void Enemy::setPosition(float x, float y)
{
    m_z = 0;
    m_sprite.setPosition(x, y);
}

void Enemy::handleEvent(const sf::Event& event)
{

}

void Enemy::update(float dt)
{

}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}
