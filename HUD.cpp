#include "HUD.h"
#include "Constants.h"
#include "ResourceManager.h"
#include "iostream"

HUD::HUD(Player& player) :
    GameObject(GameObject::HUD),
    m_bg(sf::Vector2f(100.f,5)),
    m_fill(sf::Vector2f()),
    m_player(player)
{
    m_healthText.setString("Health :");
    m_healthText.setFont(FontManager::get(DefaultFont));
    m_healthText.setColor(sf::Color::White);
    m_healthText.setCharacterSize(20);

    m_weaponText.setString("Current Weapon: " + std::string(player.getWeaponType() == Player::CrossBow ? "Cross Bow" : "Crowbar"));
    m_weaponText.setFont(FontManager::get(DefaultFont));
    m_weaponText.setColor(sf::Color::White);
    m_weaponText.setCharacterSize(20);

    m_crossBow.setString("No of Arrows : " + std::to_string(m_player.getArrowLeft()));
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


void HUD::setSceneNumber(int number)
{
    m_sceneNumber.setString("Scene : " + std::to_string(number));
    m_sceneNumber.setPosition(sf::Vector2f(400, 70));
    m_sceneNumber.setFont(FontManager::get(DefaultFont));
    m_sceneNumber.setColor(sf::Color::White);
    m_sceneNumber.setCharacterSize(20);
}

void HUD::setWaveNumber(int number)
{
    m_waveNumber.setString("Wave : " + std::to_string(number));
    m_waveNumber.setPosition(sf::Vector2f(400, 100));
    m_waveNumber.setFont(FontManager::get(DefaultFont));
    m_waveNumber.setColor(sf::Color::White);
    m_waveNumber.setCharacterSize(20);
}


void HUD::update(float dt)
{
    m_fill.setSize(sf::Vector2f(m_player.getHealth(),10));
    m_weaponText.setString("Current Weapon: " +
                            std::string(m_player.getWeaponType() == Player::CrossBow ? "Hawkeye's Cross Bow" : "Gordon's Crowbar"));
    m_crossBow.setString("No of Arrows : " + std::to_string(m_player.getArrowLeft()));
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
        if (m_player.getWeaponType() == Player::CrossBow)
            target.draw(m_crossBow, states);
        target.draw(m_sceneNumber, states);
        target.draw(m_waveNumber, states);
    }
}