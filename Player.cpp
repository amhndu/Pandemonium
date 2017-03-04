#include "Player.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "Enemy.h"
#include <iostream>

Player::Player(GameObjectManager& gom) :
    GameObject(PlayerObject),
    m_frameTimer(0),
    m_health(MAX_HEALTH),
    m_animationframe({{0,1,0,2}, {0,5,4}, {0,6,4}, {0,7,4}}),
    m_currentAnimation(0),
    m_attacking(false),
    m_gameObjects(gom),
    m_frame(0),
    m_flip(false),
    m_colliding(false)
{
    m_sprite.setTexture(TextureManager::get(PlayerSprite), {120, 200});
    m_sprite.setSpriteIndex(0);
    //m_sprite.setScale(200.f/ /**810.f**/540.f);
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
        case Projectile:
            // If colliding, then reduce armor/health
            break;
    }
}

void Player::setActive(bool active)
{
    m_active = active;
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
    weaponextension.top = m_z;

    sf::FloatRect enemybody = enemy.getGlobalBounds();
    enemybody.top = enemy.getZ();

    if (std::abs(m_z - enemy.getZ()) < 1.5f && weaponextension.intersects(enemybody))
    {
        if (enemy.inflictDamage(20))
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

void Player::inflictDamage(int damage)
{
    m_health -= damage;
    if (m_health <= 0)
        m_cb();
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

        bool moving = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        {
            moving = false;
            if (!m_attacking)
            {
                if (m_currentAnimation >= 3)
                    m_currentAnimation = 1;
                else
                    ++m_currentAnimation;
                m_attacking = true;
                m_gameObjects.foreach([&](GameObject& g){
                            if (g.getType() == EnemyObject) attackEnemy(static_cast<Enemy&>(g));});
            }

        }
        else if (!m_colliding)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_sprite.getPosition().x < WINDOW_WIDTH)
            {
                m_position.x += PLAYER_VELOCITY * dt;
                moving = true;
                m_flip = false;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_sprite.getPosition().x >= 0)
            {
                m_position.x += -PLAYER_VELOCITY * dt;
                moving = true;
                m_flip = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_z >= 0 && m_sprite.getPosition().x < WINDOW_WIDTH)
            {
                m_z += -Z_VELOCITY * dt;
                moving = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_z < 10 && m_sprite.getPosition().x >= 0)
            {
                m_z += Z_VELOCITY * dt;
                moving = true;
            }
            m_sprite.setFlip(m_flip);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            
        }
        float d = LAND_APP_HEIGHT * m_z / 10.f;
        m_sprite.setPosition(m_position.x + d * LAND_SLOPE,
                             m_position.y + d);

        if (moving || m_attacking)
        {
            if (!m_attacking) // i.e. only moving
            {
                if (m_currentAnimation != 0)
                {
                    m_currentAnimation = 0;
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
                        m_attacking = false;
                }
            }
            m_sprite.setSpriteIndex(m_animationframe[m_currentAnimation][m_frame]);
        }
        else
        {
            m_frame = 0;
            m_sprite.setSpriteIndex(0);
        }
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
