#include "Projectile.h"
#include "ResourceManager.h"
#include "Constants.h"

Projectile::Projectile() :
    GameObject(PlayerObject)
{
    
}

void Projectile::handleCollision(GameObject& other)
{
    switch (other.getType())
    {
        case Button:
            break ;
        case PlayerObject:
            
            break ;
        case EnemyObject:
            //decrease health
            break ;
    }
}

void Projectile::setActive(bool active)
{
    m_active = active ;
}

sf::Vector2f Projectile::getPosition()
{
    return m_circle.getPosition() ;
}

void Projectile::setPosition(float x , float y)
{
    m_circle.setPosition(x,y) ;
}

void Projectile::handleEvent(const sf::Event& event)
{

}

void Projectile::setVelocity(float val)
{
    velocity = val ;
}


void Projectile::update(float dt)
{
    if(m_active)
    {
        
    }
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_active)
        target.draw(m_circle) ;
}


