#include "Projectile.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "Enemy.h"

Projectile::Projectile(Type t, const sf::Vector2f& pos, float vel) :
    GameObject(GameObject::ProjectileObject),
    m_type(t),
    m_velocity(vel),
    m_collided(false)
{
    switch (m_type)
    {
        case Arrow:
            m_sprite.setTexture(TextureManager::get(ArrowTexture));
            break;
        case Bullet:
            m_sprite.setTexture(TextureManager::get(BulletTexture));
            break;
    }
    m_sprite.setPosition(pos);
}

void Projectile::handleCollision(GameObject& other)
{
    switch (other.getType())
    {
        case Button:
            break;
        case PlayerObject:
            break;
        case EnemyObject:
            auto& enemy = static_cast<Enemy&>(other);
            auto box1 = m_sprite.getGlobalBounds();
            box1.top = m_z - 1;
            box1.height = 3;
            auto box2 = enemy.getGlobalBounds();
            box2.top = enemy.getZ() - 1;
            box2.height = 3;
            if (box1.intersects(box2))
            {
                enemy.inflictDamage(20);
                setCollided();
            }
            break;
    }
}

void Projectile::setActive(bool active)
{
    m_active = active;
}

sf::Vector2f Projectile::getPosition()
{
    return m_sprite.getPosition();
}

void Projectile::setPosition(float x , float y)
{
    m_sprite.setPosition(x,y);
}

void Projectile::handleEvent(const sf::Event& event)
{

}

void Projectile::setCollided()
{
    m_collided = true;
}

void Projectile::update(float dt)
{
    if(m_active)
    {
        m_sprite.move(m_velocity * dt, 0);
        if (m_sprite.getPosition().x > WINDOW_WIDTH - m_sprite.getGlobalBounds().width ||
            m_sprite.getPosition().x < 0)
            setCollided();
    }
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_active)
        target.draw(m_sprite);
}


