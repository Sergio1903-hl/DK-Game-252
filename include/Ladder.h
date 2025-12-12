#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Ladder {
private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    bool hasTexture;
    
    float x, y, width, height;
    float scale;
    
public:
    Ladder(float x, float y, float width, float height, float scale);
    
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    float getX() const { return x; }
    float getY() const { return y; }
};
