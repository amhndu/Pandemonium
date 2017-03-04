#include "Enemy.h"
#include "ResourceManager.h"
#include "Constants.h"
#include <iostream>
#include <cmath>

Enemy::Enemy(Type type, Player& player):
    GameObject(EnemyObject),
    m_frame(0),
    m_frameTimer(0),
    m_attackTimer(0),
    m_player(player),
    m_type(type),
    m_health(MAX_HEALTH),
    m_bg(sf::Vector2f(100.f,5)),
    m_fill(sf::Vector2f())
{
    //TODO type
    m_sprite.setTexture(TextureManager::get(Bot1Sprite), {100, 212});
    m_sprite.setSpriteIndex(0);
    m_sprite.setScale(200.f/ 212.f);

    m_bg.setSize(sf::Vector2f(100, 10));
    m_bg.setOutlineColor(sf::Color::Black);
    m_bg.setOutlineThickness(1);
    m_bg.setFillColor(sf::Color::Yellow);

    m_fill.setSize(sf::Vector2f(100, 10));
    m_fill.setFillColor(sf::Color::Red);
}

sf::FloatRect Enemy::getGlobalBounds()
{
    return m_sprite.getGlobalBounds();
}


void Enemy::handleCollision(GameObject& other)
{
    switch (other.getType())
    {
        case Button:
            break;
        case PlayerObject:
            other.handleCollision(*this);
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
    m_position = {x, y};
    m_sprite.setPosition(x, y);

    m_bg.setPosition(x-5, y - 15);
    m_fill.setPosition(m_bg.getPosition());
}

void Enemy::setZ(float z)
{
    m_z = z;
    float d = LAND_APP_HEIGHT * m_z / 10.f;
    m_sprite.setPosition(m_position.x + d * LAND_SLOPE,
                         m_position.y + d);
}

float Enemy::getZ()
{
    return m_z;
}

void Enemy::inflictDamage(int damage)
{
    m_health -= damage;
}

void Enemy::handleEvent(const sf::Event& event)
{

}

void Enemy::update(float dt)
{
    if (m_active)
    {
        bool moving = false;
        bool inbounds = std::abs(m_player.getPosition().x - getPosition().x) <
            std::max(PLAYER_WIDTH, m_sprite.getGlobalBounds().width);
            moving = false;
        if(getPosition().x - m_player.getPosition().x > 0)
        {
            if (!inbounds)
            {
                m_position.x += -ENEMY_VELOCITY * dt;
                moving = true;
            }
            m_sprite.setFlip(false);
        }
        else if(getPosition().x - m_player.getPosition().x < 0)
        {
            if (!inbounds)
            {
                m_position.x += +ENEMY_VELOCITY * dt;
                moving = true;
            }
            m_sprite.setFlip(true);
        }


        if (std::abs(m_player.getZ() - m_z) < 1.5f || std::abs(m_player.getPosition().x - getPosition().x) >= 200.f)
            inbounds = inbounds && true;
        else if(m_player.getZ() - m_z > 0)
        {
            m_z += 2.f * Z_VELOCITY  * dt / 5.f;
            moving = true;
        }
        else if(m_player.getZ() - m_z < 0)
        {
            m_z += -(2.f * Z_VELOCITY * dt / 5.f);
            moving = true;
        }

        float d = LAND_APP_HEIGHT * m_z / 10.f;
        m_sprite.setPosition(m_position.x + d * LAND_SLOPE,
                                m_position.y + d);
        m_bg.setPosition(m_sprite.getPosition() - sf::Vector2f(0, 200) );
        m_fill.setPosition(m_sprite.getPosition() - sf::Vector2f(0, 200));
        m_fill.setSize(sf::Vector2f(m_health , 10));

        m_attackTimer += dt;
        if (inbounds && m_attackTimer > 1.f)
        {
            // Attack player
            m_player.inflictDamage(10);

            m_attackTimer = 0;
        }

        if (moving)
        {
            m_frameTimer += dt;
            if (m_frameTimer > ANIM_FRAME_TIME)
            {
                m_frameTimer -= ANIM_FRAME_TIME;

                ++m_frame;
                if (m_frame >= 8)
                    m_frame = 1;
            }
        }
        else
            m_frame = 0;
        m_sprite.setSpriteIndex(m_frame);
    }
}

bool Enemy::toDestroy()
{
    bool flag = m_health <= 0;
    if (flag)
        m_deathCallback();
    return flag;
}


int Enemy::getHealth()
{
    return m_health;
}



void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_bg, states);
    target.draw(m_fill, states);
    target.draw(m_sprite, states);
}
