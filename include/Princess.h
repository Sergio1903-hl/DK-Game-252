#pragma once
#include <SFML/Graphics.hpp>

class Princess {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float x, y;
    float scale;
    
    // Animation
    int currentFrame;
    sf::Clock animationClock;
    float frameTime;
    
public:
    Princess(float x, float y, float scale);
    
    void update(float dt);
    void render(sf::RenderWindow& window);
    
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const { return {x, y}; }
};
