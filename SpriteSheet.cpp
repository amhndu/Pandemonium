#include "SpriteSheet.h"

void SpriteSheet::setTexture(sf::Texture& texture, sf::Vector2i size)
{
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect({0, 0, size.x, size.y});
    m_spritesPerRow = texture.getSize().x / size.x;
    m_spriteSize = size;
}

void SpriteSheet::setPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

sf::Vector2f SpriteSheet::getPosition()
{
    return m_sprite.getPosition();
}

void SpriteSheet::setScale(float s)
{
    m_sprite.setScale(s, s);
}

void SpriteSheet::setSpriteIndex(int n)
{
    int x = n % m_spritesPerRow,
        y = n / m_spritesPerRow;
    m_sprite.setTextureRect({x * m_spriteSize.x, y * m_spriteSize.y, m_spriteSize.x, m_spriteSize.y});
}

void SpriteSheet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}
