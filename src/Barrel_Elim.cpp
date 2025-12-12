#include "../include/Barrel_Elim.h"
#include <iostream>

Barrel_Elim::Barrel_Elim(float x, float y, float scale)
    : x(x)
    , y(y)
    , scale(scale)
    , width(80.0f)
    , height(40.0f)
    , hasTexture(false)
{
    // Try to load texture
    if (texture.loadFromFile("assets/textures/barril_elim.png")) {
        sprite.setTexture(texture);
        // Auto-escalar al tamaño del bloque eliminador (width x height)
        float scaleX = width / texture.getSize().x;
        float scaleY = height / texture.getSize().y;
        sprite.setScale(scaleX, scaleY);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        hasTexture = true;
    }
    
    // Setup SFML shape (fallback)
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Red);  // Rojo para indicar que es un eliminador
    shape.setOrigin(width / 2.0f, height / 2.0f);
    shape.setPosition(x, y);
}

Barrel_Elim::~Barrel_Elim() {
}

void Barrel_Elim::update(float dt) {
    // El barril eliminador no se mueve, es estático
    shape.setPosition(x, y);
    
    if (hasTexture) {
        sprite.setPosition(x, y);
    }
}

void Barrel_Elim::render(sf::RenderWindow& window) {
    if (hasTexture) {
        window.draw(sprite);
    } else {
        window.draw(shape);
    }
}

sf::FloatRect Barrel_Elim::getBounds() const {
    return sf::FloatRect(x - width / 2.0f, y - height / 2.0f, width, height);
}
