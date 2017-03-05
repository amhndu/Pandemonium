#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <functional>

class Button : public GameObject
{
public:
    Button();
    void update(float dt) override;
    void handleEvent(const sf::Event& event) override;
    void setPosition(float x, float y) override;
    sf::Vector2f getPosition() override;
    void setActive(bool active) override;
    void handleCollision(GameObject& other) override {};

    void setText(const std::string& text);
    void setTextColor(const sf::Color& color);
    void setBackgroundColor(const sf::Color& color);
    void setHoverColor(const sf::Color& color);

    
    template <class Function>
    void inline setCallback(Function f) { m_callback = f; };
protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    std::function<void(void)> m_callback;
    sf::Text m_text;
    sf::RectangleShape m_bg;
    bool m_mouseInside;
    sf::Color m_hoverColor;
    sf::Color m_backgroundColor;
};

#endif // BUTTON_H
