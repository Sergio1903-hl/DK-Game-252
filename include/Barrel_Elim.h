#pragma once
#include <SFML/Graphics.hpp>

class Barrel_Elim {
private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    bool hasTexture;
    
    float x, y;
    float width, height;
    float scale;
    
public:
    Barrel_Elim(float x, float y, float scale);
    ~Barrel_Elim();
    
    void update(float dt);
    void render(sf::RenderWindow& window);
    
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const { return {x, y}; }
};
