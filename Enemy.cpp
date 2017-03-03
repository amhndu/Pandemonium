#include "Enemy.h"
#include "ResourceManager.h"
#include "Constants.h"
#include<iostream>

Enemy::Enemy(Player& player):
    GameObject(EnemyObject),
    m_player(player)
{
    m_sprite.setTexture(TextureManager::get(Bot1Sprite), {100, 212});
    m_sprite.setSpriteIndex(0);
    m_sprite.setScale(200.f/ 212.f);
}


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
    m_position = {x, y};
    m_sprite.setPosition(x, y);
}

void Enemy::handleEvent(const sf::Event& event)
{

}

void Enemy::update(float dt)
{
  

    if (m_active)
    {
        bool moving = false;
	/*
	
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_sprite.getPosition().x < WINDOW_WIDTH)
        {
            m_position.x += PLAYER_VELOCITY * dt;
            moving = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_sprite.getPosition().x >= 0)
        {
            m_position.x += -PLAYER_VELOCITY * dt;
            moving = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_z >= 0)
        {
            m_z += -Z_VELOCITY * dt;
            moving = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_z < 10)
        {
            m_z += Z_VELOCITY * dt;
            moving = true;
        }*/
        
        
        if(getPosition().x - m_player.getPosition().x > 0 + 10.f)
	{
	    m_position.x += -ENEMY_VELOCITY * dt;
	    moving = true;
	    m_sprite.setFlip(false);
	}
	else if(getPosition().x - m_player.getPosition().x < 0 + 10.f)
	{
	    m_position.x += +ENEMY_VELOCITY * dt;
	    moving = true;
	    m_sprite.setFlip(true);
	}
        
        if(getPosition().y - m_player.getPosition().y > 0)
	{
	    m_z += -Z_VELOCITY  * dt;
	    moving = true;
	}
	else if(getPosition().y - m_player.getPosition().y < 0)
	{
	    m_z += Z_VELOCITY * dt;
	    moving = true;
	}
        
        

        float d = LAND_APP_HEIGHT * m_z / 10.f;
        m_sprite.setPosition(m_position.x + d * LAND_SLOPE, m_position.y + d);

        if (moving)
        {
            m_frameTimer += dt;
            if (m_frameTimer > 0.3)
            {
                m_frameTimer -= 0.3;

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

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}
