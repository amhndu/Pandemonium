#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SFML/Graphics.hpp>

class SpriteSheet : public sf::Drawable
{
public:
    void setTexture(sf::Texture& texture, sf::Vector2i size);
    void setSpriteIndex(int n);
    void setPosition(float x, float y);
    sf::Vector2f getPosition();
    void setScale(float s);
    void setFlip(bool flag);
    sf::FloatRect getGlobalBounds();
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::Sprite m_sprite;
    sf::Vector2i m_spriteSize;
    int m_index;
    int m_spritesPerRow;
    bool m_flip;
};

#endif // SPRITESHEET_H
