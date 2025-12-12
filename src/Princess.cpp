#include "../include/Princess.h"
#include <iostream>

Princess::Princess(float x, float y, float scale)
    : x(x)
    , y(y)
    , scale(scale)
    , currentFrame(0)
    , frameTime(0.3f)
{
    // Try to load texture
    if (!texture.loadFromFile("assets/textures/princess.png")) {
        std::cerr << "Warning: Could not load Princess texture" << std::endl;
    }
    else {
        sprite.setTexture(texture);
        // Auto-escalar al tamaño deseado (45x75) para mayor visibilidad
        float targetWidth = 45.0f;
        float targetHeight = 75.0f;
        float scaleX = targetWidth / texture.getSize().x;
        float scaleY = targetHeight / texture.getSize().y;
        sprite.setScale(scaleX, scaleY);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        std::cout << "Princess texture loaded: " << texture.getSize().x << "x" << texture.getSize().y 
                  << " scaled to: " << targetWidth << "x" << targetHeight << std::endl;
    }
    
    sprite.setPosition(x, y);
}

void Princess::update(float dt) {
    // Simple animation
    if (animationClock.getElapsedTime().asSeconds() > frameTime) {
        currentFrame = (currentFrame + 1) % 2;
        animationClock.restart();
        
        // Animate by moving slightly (mantener escala)
        float offset = currentFrame * 2.0f;
        sprite.setPosition(x, y + offset);
        
        // Asegurar que la escala se mantenga
        if (texture.getSize().x > 0) {
            float targetWidth = 45.0f;
            float targetHeight = 75.0f;
            float scaleX = targetWidth / texture.getSize().x;
            float scaleY = targetHeight / texture.getSize().y;
            sprite.setScale(scaleX, scaleY);
        }
    }
}

void Princess::render(sf::RenderWindow& window) {
    // If no texture, draw a simple pink rectangle
    if (texture.getSize().x == 0) {
        sf::RectangleShape rect(sf::Vector2f(45, 75));
        rect.setPosition(x, y);
        rect.setFillColor(sf::Color(255, 192, 203)); // Pink
        rect.setOrigin(22.5f, 37.5f);
        window.draw(rect);
        
        // Crown
        sf::CircleShape crown(10, 3);
        crown.setFillColor(sf::Color::Yellow);
        crown.setPosition(x - 7, y - 45);
        window.draw(crown);
    }
    else {
        window.draw(sprite);
    }
}

sf::FloatRect Princess::getBounds() const {
    return sf::FloatRect(x - 22.5f, y - 37.5f, 45, 75);
}
