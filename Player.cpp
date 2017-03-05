#include "Player.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "Enemy.h"
#include "Projectile.h"
#include <iostream>

Player::Player(GameObjectManager& gom) :
    GameObject(PlayerObject),
    m_frameTimer(0),
    m_health(MAX_HEALTH),
    m_animationframe({{0,1,0,2}, {0,5,4}, {0,6,4}, {0,7,4}, {8,9,8,10}, {8,11,12}}),
    m_currentAnimation(0),
    m_attacking(false),
    m_gameObjects(gom),
    m_frame(0),
    m_flip(false),
    m_redTimer(0),
    m_colliding(false),
    m_currentWeapon(CrowBar),
    m_arrowLeft(10)
{
    m_sprite.setTexture(TextureManager::get(PlayerSprite), {120, 200});
    m_sprite.setSpriteIndex(0);
}


void Player::handleCollision(GameObject& other)
{
    switch (other.getType())
    {
        case Button:
            break;
        case PlayerObject:
            // This really should just never happen
            break;
        case EnemyObject:
            break;
        case ProjectileObject:
            // If colliding, then reduce armor/health
            break;
    }
}

void Player::setActive(bool active)
{
    m_active = active;
}

int Player::getArrowLeft()
{
    return m_arrowLeft;
}


sf::Vector2f Player::getPosition()
{
    return m_sprite.getPosition();
}

float Player::getZ()
{
    return m_z;
}

void Player::setPosition(float x, float y)
{
    m_position = {x, y};
    m_sprite.setPosition(x, y);
}

void Player::setZ(int z)
{
    m_z = z;
    float d = LAND_APP_HEIGHT * m_z / 10.f;
    m_sprite.setPosition(m_position.x + d * LAND_SLOPE,
                         m_position.y + d);
}

void Player::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K)
    {
        changeWeapon();
    }
}

void Player::attackEnemy(Enemy& enemy)
{
    // FIXME proper collision detection
    sf::FloatRect weaponextension = m_sprite.getGlobalBounds();
    if(!m_flip)
    {
        weaponextension.left += weaponextension.width * 3.f / 4.f;

    }
    weaponextension.width *= 1.f / 4.f;
    weaponextension.top = m_z - 1;
    weaponextension.height = 3;

    sf::FloatRect enemybody = enemy.getGlobalBounds();
    enemybody.top = enemy.getZ() - 1;
    enemybody.height = 3;

    if (weaponextension.intersects(enemybody))
    {
        if (enemy.inflictDamage(20)) // If it dies: health bonus
        {
            m_health += 20;
            m_health = std::min(MAX_HEALTH, m_health);
        }
    }
}

int Player::getHealth()
{
    return m_health;
}

void Player::changeWeapon()
{
    m_currentWeapon = static_cast<WeaponType>(1 - m_currentWeapon);
    m_currentAnimation = m_currentWeapon == CrowBar ? 0 : 4;
    m_sprite.setSpriteIndex(m_animationframe[m_currentAnimation][m_frame]);
}

Player::WeaponType Player::getWeaponType()
{
    return m_currentWeapon;
}



void Player::inflictDamage(int damage)
{
    m_health -= damage;
    if (m_health <= 0)
        m_cb();
    m_redTimer = 0.3f;
    m_sprite.setColor(sf::Color::Red);
}

void Player::update(float dt)
{
    if (m_active)
    {
        if (m_health < MAX_HEALTH)
        {
            m_health += 5 * dt;
            m_health = std::min(MAX_HEALTH, m_health);
        }

        if (m_redTimer > 0)
        {
            m_redTimer -= dt;
            if (m_redTimer <= 0)
                m_sprite.setColor(sf::Color::White);
        }

        bool moving = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        {
            moving = false;
            if (!m_attacking)
            {
                switch (m_currentWeapon)
                {
                case CrowBar:
                    if (m_currentAnimation >= 3)
                        m_currentAnimation = 1;
                    else
                        ++m_currentAnimation;
                    break;
                case CrossBow:
                    m_currentAnimation = 5;
                    break;
                }
                m_attacking = true;
            }

        }
        else if (!m_colliding)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_sprite.getPosition().x < WINDOW_WIDTH)
            {
                m_position.x += PLAYER_VELOCITY * dt;
                moving = true;
                m_flip = false;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_sprite.getPosition().x >= 0)
            {
                m_position.x += -PLAYER_VELOCITY * dt;
                moving = true;
                m_flip = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_z >= 0 && m_sprite.getPosition().x < WINDOW_WIDTH)
            {
                m_z += -Z_VELOCITY * dt;
                moving = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_z < 10 && m_sprite.getPosition().x >= 0)
            {
                m_z += Z_VELOCITY * dt;
                moving = true;
            }
            m_sprite.setFlip(m_flip);
        }

        float d = LAND_APP_HEIGHT * m_z / 10.f;
        m_sprite.setPosition(m_position.x + d * LAND_SLOPE,
                             m_position.y + d);

        if (moving || m_attacking)
        {
            if (!m_attacking) // i.e. only moving
            {
                if (m_currentAnimation != 0 && m_currentAnimation != 4)
                {
                    m_currentAnimation = m_currentWeapon == CrowBar ? 0 : 4;
                    m_frame = 0;
                }
            }
            m_frameTimer += dt;
            if (m_frameTimer > ANIM_FRAME_TIME)
            {
                m_frameTimer -= ANIM_FRAME_TIME;

                ++m_frame;
                if (m_frame >= m_animationframe[m_currentAnimation].size())
                {
                    m_frame = 0;
                    if (m_attacking)
                    {
                        if (m_currentWeapon == CrowBar)
                        {
                            m_gameObjects.foreach([&](GameObject& g){
                                if (g.getType() == EnemyObject) attackEnemy(static_cast<Enemy&>(g));});
                        }
                        else if (m_arrowLeft > 0)
                        {
                            if(m_gameObjects.insert("arrow", new Projectile(Projectile::Arrow,
                                                                         getPosition() + sf::Vector2f{100.f - 80.f * m_flip, -100.f},
                                                                         350.f - 700.f * m_flip, m_z)))
                                --m_arrowLeft;

                        }
                        m_attacking = false;
                    }
                }
            }
            m_sprite.setSpriteIndex(m_animationframe[m_currentAnimation][m_frame]);
        }
        else
        {
            m_frame = 0;
            m_sprite.setSpriteIndex(m_animationframe[m_currentWeapon == CrowBar ? 0 : 4][m_frame]);
        }
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
