#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class DonkeyKong {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float x, y;
    float scale;
    
    sf::Clock throwTimer;
    float throwInterval;
    bool isAngry;
    
    // Animation
    int currentFrame;
    sf::Clock animationClock;
    float frameTime;
    
    // IA inteligente
    int barrelsThrown;
    float difficulty;
    
public:
    DonkeyKong(float x, float y, float scale);
    
    void update(float dt);
    void render(sf::RenderWindow& window);
    
    bool shouldThrowBarrel();
    void resetThrowTimer();
    
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const { return {x, y}; }
};
