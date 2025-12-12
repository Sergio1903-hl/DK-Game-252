#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Platform {
private:
    b2BodyId bodyId;
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    bool hasTexture;
    bool isOneWay;  // Can pass through from below
    
    float width, height;
    float scale;
    float x, y;  // Store position
    
public:
    Platform(b2WorldId worldId, float x, float y, float width, float height, float scale, bool oneWay = false, float angleDeg = 0.0f);
    ~Platform();
    
    void render(sf::RenderWindow& window);
    
    b2BodyId getBodyId() const { return bodyId; }
    sf::FloatRect getBounds() const;
    bool isOneWayPlatform() const { return isOneWay; }
    float getTop() const { return y - height / 2.0f; }
};
