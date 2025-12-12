#include "../include/Ladder.h"
#include <iostream>

Ladder::Ladder(float x, float y, float width, float height, float scale)
    : x(x)
    , y(y)
    , width(width)
    , height(height)
    , scale(scale)
    , hasTexture(false)
{
    // Try to load texture
    if (texture.loadFromFile("assets/textures/ladder.png")) {
        sprite.setTexture(texture);
        texture.setRepeated(true); // Permitir repetición vertical para escaleras
        
        // Auto-escalar como las plataformas: la textura se estira para cubrir el área completa
        sf::Vector2u textureSize = texture.getSize();
        float scaleX = width / textureSize.x;
        float scaleY = height / textureSize.y;
        
        sprite.setScale(scaleX, scaleY);
        sprite.setPosition(x, y);
        hasTexture = true;
        std::cout << "Ladder texture loaded: " << textureSize.x << "x" << textureSize.y 
                  << " scaled to: " << width << "x" << height << " at position: " << x << "," << y << std::endl;
    }
    
    // Setup SFML shape (fallback)
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(x, y);
}

void Ladder::render(sf::RenderWindow& window) {
    if (hasTexture) {
        window.draw(sprite);
    } else {
        window.draw(shape);
    }
}

sf::FloatRect Ladder::getBounds() const {
    return shape.getGlobalBounds();
}
