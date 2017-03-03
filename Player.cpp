#include "Player.h"
#include "ResourceManager.h"
#include "Constants.h"

Player::Player() :
    GameObject(PlayerObject),
    m_frameTimer(0),
    
    m_armour(0),
    m_health(MAX_HEALTH),
    m_attack1(false),
    m_animationframe({{0,1,0,2},{0,3,3},{0,5,6},{0,7,8}}),
    m_currentAnimation(0)
{
    m_sprite.setTexture(TextureManager::get(PlayerSprite), {/**374, 810**/540,540});
    m_sprite.setSpriteIndex(0);
    m_sprite.setScale(200.f/ /**810.f**/540.f);
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
            // See if we're trying to hit something. Or possibly, let the enemy object handle this
            // as it'd have to inflict damage upon it
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
    m_z = 0.f;
    m_position = {x, y};
    m_sprite.setPosition(x, y);
}

void Player::handleEvent(const sf::Event& event)
{

}

void Player::update(float dt)
{
    if (m_active)
    {
        bool moving = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            moving = false;
            if (!m_attack1)
            {
                if (m_currentAnimation >= 3)
                    m_currentAnimation = 1;
                else
                    ++m_currentAnimation;
                m_attack1 = true;
            }

        }
        else 
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_sprite.getPosition().x < WINDOW_WIDTH)
            {
                m_position.x += PLAYER_VELOCITY * dt;
                moving = true;
                m_sprite.setFlip(false);
                if (m_currentAnimation != 0)
                {
                    m_currentAnimation = 0;
                    m_frame = 0;
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_sprite.getPosition().x >= 0)
            {
                m_position.x += -PLAYER_VELOCITY * dt;
                moving = true;
                m_sprite.setFlip(true);
                if (m_currentAnimation != 0)
                {
                    m_currentAnimation = 0;
                    m_frame = 0;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_z >= 0 && m_sprite.getPosition().x < WINDOW_WIDTH)
            {
                m_z += -Z_VELOCITY * dt;
                moving = true;
                if (m_currentAnimation != 0)
                {
                    m_currentAnimation = 0;
                    m_frame = 0;
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_z < 10 && m_sprite.getPosition().x >= 0)
            {
                m_z += Z_VELOCITY * dt;
                moving = true;
                if (m_currentAnimation != 0)
                {
                    m_currentAnimation = 0;
                    m_frame = 0;
                }
            }    
        }
        
        float d = LAND_APP_HEIGHT * m_z / 10.f;
        m_sprite.setPosition(m_position.x + d * LAND_SLOPE,
                             m_position.y + d);

        if (moving || m_attack1)
        {
            m_frameTimer += dt;
            if (m_frameTimer > ANIM_FRAME_TIME)
            {
                m_frameTimer -= ANIM_FRAME_TIME;

                ++m_frame;
                if (m_frame >= m_animationframe[m_currentAnimation].size())
                {
                    m_frame = 0;
                    if (m_attack1)
                        m_attack1 = false;
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
    target.draw(m_sprite);
}
