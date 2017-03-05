#include "HUD.h"
#include "Constants.h"
#include "ResourceManager.h"


HUD::HUD(Player& player) :
    GameObject(GameObject::HUD),
    m_bg(sf::Vector2f(100.f,5)),
    m_fill(sf::Vector2f()),
    m_player(player),
    m_isCrossBow(player.getWeaponType() == Player::CrossBow)
{
    m_healthText.setString("Health :");
    m_healthText.setFont(FontManager::get(DefaultFont));
    m_healthText.setColor(sf::Color::White);
    m_healthText.setCharacterSize(20);

    if(m_isCrossBow)
        m_weaponText.setString("Current Weapon : Cross Bow");

    m_weaponText.setString("Current Weapon : Crow Bar");
    m_weaponText.setFont(FontManager::get(DefaultFont));
    m_weaponText.setColor(sf::Color::White);
    m_weaponText.setCharacterSize(20);

    m_crossBow.setString("No of Cross Bow :");
    m_crossBow.setFont(FontManager::get(DefaultFont));
    m_crossBow.setColor(sf::Color::White);
    m_crossBow.setCharacterSize(20);

    m_bg.setSize(sf::Vector2f(100, 10));
    m_bg.setOutlineColor(sf::Color::Black);
    m_bg.setOutlineThickness(1);
    m_bg.setFillColor(sf::Color::Yellow);

    m_fill.setSize(sf::Vector2f(100, 10));
    m_fill.setFillColor(sf::Color::Red);

    m_crossBow.setPosition(sf::Vector2f(50, 130));
    m_weaponText.setPosition(sf::Vector2f(50, 100));
    m_healthText.setPosition(sf::Vector2f(50,70));
    m_bg.setPosition(sf::Vector2f(115 ,80));
    m_fill.setPosition(sf::Vector2f(115, 80));
}


void HUD::update(float dt)
{
    m_fill.setSize(sf::Vector2f(m_player.getHealth(),10));
}

void HUD::setPosition(float x, float y)
{
}

sf::Vector2f HUD::getPosition()
{
    return m_healthText.getPosition();
}

void HUD::setActive(bool active)
{
    m_active = active;
}

void HUD::handleEvent(const sf::Event& event)
{

}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_active)
    {
        target.draw(m_bg, states);
        target.draw(m_fill, states);
        target.draw(m_healthText, states);
        target.draw(m_weaponText, states);
        if (m_isCrossBow)
            target.draw(m_crossBow, states);
    }
}