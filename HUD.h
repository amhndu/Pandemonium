#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Player.h"

class HUD : public GameObject
{
public:
    HUD(Player& player);
    void update(float dt) override;
    void handleEvent(const sf::Event& event) override;
    void setPosition(float x, float y) override;
    sf::Vector2f getPosition() override;
    void setActive(bool active) override;
    void handleCollision(GameObject& other) override {};
    void setText(const std::string& text);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Text m_healthText;
    sf::Text m_weaponText;
    sf::Text m_crossBow;
    sf::RectangleShape m_bg;
    sf::RectangleShape m_fill;
    Player& m_player;
    
    bool m_isCrossBow;
};

#endif
 