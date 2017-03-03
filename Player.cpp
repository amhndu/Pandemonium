#include "Player.h"
#include "ResourceManager.h"
#include "Constants.h"

Player::Player() :
    GameObject(PlayerObject),
    m_frameTimer(0)
{
    m_sprite.setTexture(TextureManager::get(PlayerSprite), {374, 810});
    m_sprite.setSpriteIndex(0);
    m_sprite.setScale(200.f/ 810.f);
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            m_position.x += PLAYER_VELOCITY * dt;
            moving = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            m_position.x += -PLAYER_VELOCITY * dt;
            moving = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
             if (m_z > 0)
                m_z += -Z_VELOCITY * dt;
             moving = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
              if (m_z < 10)
                m_z += Z_VELOCITY * dt;
              moving = true;
        }

        float d = LAND_APP_HEIGHT * m_z / 10.f;
        m_sprite.setPosition(m_position.x + d * LAND_SLOPE,
                                m_position.y + d);

        m_frameTimer += dt;
        if (m_frameTimer > 0.01)
        {
            m_frameTimer -= 0.01;

            ++m_frame;
            if (m_frame >= 4)
                m_frame = 0;
            m_sprite.setSpriteIndex(m_frame);
        }
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}
