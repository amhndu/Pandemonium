#include "HUD.h"
#include "Constants.h"
#include "ResourceManager.h"


HUD::HUD(Player& player) :
    GameObject(GameObject::HUD),
    m_bg(sf::Vector2f(100.f,5)),
    m_fill(sf::Vector2f()),
    m_player(player)
{
    m_text.setString("Health :");
    m_text.setFont(FontManager::get(DefaultFont));
    m_text.setColor(sf::Color::Black);
    m_text.setCharacterSize(20);

    m_bg.setSize(sf::Vector2f(100, 10));
    m_bg.setOutlineColor(sf::Color::Black);
    m_bg.setOutlineThickness(1);
    m_bg.setFillColor(sf::Color::Yellow);

    m_fill.setSize(sf::Vector2f(100, 10));
    m_fill.setFillColor(sf::Color::Red);

    m_text.setPosition(sf::Vector2f(50,70));
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
    return m_text.getPosition();
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
        target.draw(m_text, states);
    }
}