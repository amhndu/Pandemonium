#include "SpriteSheet.h"

void SpriteSheet::setTexture(sf::Texture& texture, sf::Vector2i size)
{
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect({0, 0, size.x, size.y});
    m_spritesPerRow = texture.getSize().x / size.x;
    m_spriteSize = size;
    m_sprite.setOrigin({0, m_sprite.getLocalBounds().height});
    m_flip = false;
    m_index = 0;
}

void SpriteSheet::setPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

sf::FloatRect SpriteSheet::getGlobalBounds()
{
    return m_sprite.getGlobalBounds();
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
    m_index = n;
    int x = n % m_spritesPerRow,
        y = n / m_spritesPerRow;
    m_sprite.setTextureRect({x * m_spriteSize.x, y * m_spriteSize.y, m_spriteSize.x, m_spriteSize.y});
}

void SpriteSheet::setFlip(bool flip)
{
    if (flip)
        m_sprite.setOrigin({ m_sprite.getLocalBounds().width, m_sprite.getOrigin().y });
    else
        m_sprite.setOrigin({0, m_sprite.getOrigin().y});

    if (m_flip != flip)
        m_sprite.setScale(-m_sprite.getScale().x, m_sprite.getScale().y);
    m_flip = flip;
}

void SpriteSheet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}
