#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ResourceManager.h"
#include "Constants.h"
#include <iostream>

Button::Button() :
    GameObject(GameObject::Button),
    m_mouseInside(false)
{
}

void Button::setText(const std::string& text)
{
    m_text.setString(text);
    m_text.setFont(FontManager::get(DefaultFont));
    m_text.setColor(BUTTON_TEXT_COLOR);
    m_text.setCharacterSize(50);
    m_bg.setSize(sf::Vector2f(m_text.getGlobalBounds().width + 20, m_text.getGlobalBounds().height + 20));
    auto p = m_bg.getSize();
    m_bg.setOrigin(0, -m_bg.getLocalBounds().height / 2 + 22);
    m_bg.setFillColor(BUTTON_BG_COLOR);
}

void Button::setPosition(float x, float y)
{
    m_text.setPosition(x, y);
    m_bg.setPosition(x, y);
}

sf::Vector2f Button::getPosition()
{
    return m_text.getPosition();
}

void Button::setActive(bool active)
{
    m_active = active;
}

void Button::handleEvent(const sf::Event& event)
{
    if (m_active)
    {
        if (event.type == sf::Event::MouseButtonReleased)
        {
            sf::Vector2f mouse(static_cast<float>(event.mouseButton.x),
                               static_cast<float>(event.mouseButton.y));
            if (m_bg.getGlobalBounds().contains(mouse))
                m_callback();
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f mouse(static_cast<float>(event.mouseMove.x),
                               static_cast<float>(event.mouseMove.y));
            bool inside = m_bg.getGlobalBounds().contains(mouse);
            if (!m_mouseInside && inside)
            {
                m_mouseInside = true;
                m_bg.setFillColor(BUTTON_HOVER_COLOR);
            }
            else if (m_mouseInside && !inside)
            {
                m_mouseInside = false;
                m_bg.setFillColor(BUTTON_BG_COLOR);
            }
        }
    }
}

void Button::update(float dt)
{
    // Do nothing
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_active)
    {
        auto p = m_bg.getSize();
        target.draw(m_bg, states);
        target.draw(m_text, states);
    }
}
