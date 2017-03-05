#include "Enemy.h"
#include "ResourceManager.h"
#include "Constants.h"
#include <iostream>
#include <cmath>

Enemy::Enemy(Type type, Player& player, SmokeEmitter &smoke):
    GameObject(EnemyObject),
    m_frame(0),
    m_frameTimer(0),
    m_attackTimer(0),
    m_stunTimer(0),
    m_player(player),
    m_type(type),
    m_health(0),
    m_bg(sf::Vector2f(100.f,5)),
    m_fill(sf::Vector2f()),
    m_smoke(smoke)
{
    switch (m_type)
    {
        case DamagedEasy:
        case Easy:
            m_sprite.setTexture(TextureManager::get(Bot1Sprite), {60, 200});
            m_health = 40;
            m_attackDamage = 10;
            m_enemyVelocity = 120.f;
            m_enemyZVelocity = 15.f;
            m_emmiterPosition = {45.f, -65.f};
            break;
        case Medium:
            m_sprite.setTexture(TextureManager::get(Bot2Sprite), {120, 100});
            m_health = 60;
            m_attackDamage = 20;
            m_enemyVelocity = 50.f;
            m_enemyZVelocity = 8.f;
            m_emmiterPosition = {68.f, -42.f};
            break;
        case Hard:
            m_sprite.setTexture(TextureManager::get(Bot3Sprite), {135, 210});
            m_health = 100;
            m_attackDamage = 30;

            m_emmiterPosition = {104.f, -106.f};

            m_enemyZVelocity = 8.f;
            m_enemyVelocity = 50.f;
            break;
    }

    m_maxHealth = m_health;
    if (m_type == DamagedEasy)
        m_health = m_health / 2;

    m_sprite.setSpriteIndex(0);

    m_bg.setSize(sf::Vector2f(100, 10));
    m_bg.setOutlineColor(sf::Color::Black);
    m_bg.setOutlineThickness(1);
    m_bg.setFillColor(sf::Color::Yellow);

    m_fill.setSize(sf::Vector2f(100, 10));
    m_fill.setFillColor(sf::Color::Red);

    m_smoke.setLooping(true);
    m_smoke.setSpeed(8, 4);
    m_smoke.setLifetime(5);
    m_smoke.setScale(0.75, 2.5);
    //smoke.setAngle(math::PI / 4, 0.4);
    //m_smoke.createParticles(200);
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
        case ProjectileObject:
            other.handleCollision(*this);
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

    m_bg.setPosition(x - 200, y - 200);
    m_fill.setPosition(m_bg.getPosition());

    m_smoke.setPosition(m_sprite.getPosition() + m_emmiterPosition);
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

bool Enemy::inflictDamage(int damage)
{
    m_health -= damage;
    m_stunTimer = 0.3f;
    m_sprite.setColor(sf::Color::Red);
    m_smoke.createParticles(200.f * damage / m_maxHealth);
    return m_health <= 0;
}

void Enemy::handleEvent(const sf::Event& event)
{

}

void Enemy::update(float dt)
{
    if (m_active)
    {
        if (m_stunTimer > 0)
        {
            m_stunTimer -= dt;
            if (m_stunTimer <= 0)
                m_sprite.setColor(sf::Color::White);
        }

        bool moving = false;
        bool inbounds = std::abs(m_player.getPosition().x - getPosition().x) <
            std::max(PLAYER_WIDTH, m_sprite.getGlobalBounds().width);
            moving = false;
        if(getPosition().x - m_player.getPosition().x > 0)
        {
            if (!inbounds)
            {
                m_position.x += -m_enemyVelocity * dt;
                moving = true;
            }
            m_sprite.setFlip(false);
        }
        else if(getPosition().x - m_player.getPosition().x < 0)
        {
            if (!inbounds)
            {
                m_position.x += +m_enemyVelocity * dt;
                moving = true;
            }
            m_sprite.setFlip(true);
        }


        if (std::abs(m_player.getZ() - m_z) < 2.f || std::abs(m_player.getPosition().x - getPosition().x) >= 200.f)
        {
            if (std::abs(m_player.getZ() - m_z) <= 1.f)
                inbounds = inbounds && true;
        }
        else if(m_player.getZ() - m_z > 0)
        {
            m_z += 2.f * m_enemyZVelocity  * dt / 5.f;
            moving = true;
        }
        else if(m_player.getZ() - m_z < 0)
        {
            m_z += -(2.f * m_enemyZVelocity * dt / 5.f);
            moving = true;
        }

        float d = LAND_APP_HEIGHT * m_z / 10.f;
        m_sprite.setPosition(m_position.x + d * LAND_SLOPE,
                                m_position.y + d);
        m_bg.setPosition(m_sprite.getPosition() - sf::Vector2f(0, 200) );
        m_fill.setPosition(m_sprite.getPosition() - sf::Vector2f(0, 200));
        m_fill.setSize(sf::Vector2f(getHealth() * 100, 10));
        m_smoke.setPosition(m_sprite.getPosition() + m_emmiterPosition);

        if (m_attackTimer > 0)
        {
            m_attackTimer -= dt;
            if (m_attackTimer <= 0)
                m_player.inflictDamage(m_attackDamage);
        }

        if (m_stunTimer <= 0 && inbounds && m_attackTimer <= 0)
        {
            m_attackTimer = 1.5f;
        }

        if (moving)
        {
            m_frameTimer += dt;
            if (m_frameTimer > ANIM_FRAME_TIME)
            {
                m_frameTimer -= ANIM_FRAME_TIME;

                ++m_frame;
                if (m_frame >= 3)
                    m_frame = 0;
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
    {
        m_deathCallback();
        m_smoke.setDie(true);
    }
    return flag;
}


float Enemy::getHealth()
{
    return static_cast<float>(m_health) / m_maxHealth;
}


void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_bg, states);
    target.draw(m_fill, states);
    target.draw(m_sprite, states);
}
