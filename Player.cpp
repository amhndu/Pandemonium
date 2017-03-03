#include "Player.h"
#include "ResourceManager.h"
#include "Constants.h"

Player::Player() :
    GameObject(PlayerObject)
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_position.y += PLAYER_VELOCITY * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_position.y += -PLAYER_VELOCITY * dt;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_z += PLAYER_VELOCITY * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_z += -PLAYER_VELOCITY * dt;
    }

    float d = LAND_APP_HEIGHT * m_z / 10.f;
    m_sprite.setPosition(m_position.x + d,
                            m_position.y + LAND_SLOPE * d);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}
