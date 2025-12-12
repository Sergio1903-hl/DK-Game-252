#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Barrel {
private:
    b2BodyId bodyId;
    sf::CircleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    bool hasTexture;
    
    float radius;
    float scale;
    bool active;
    
public:
    Barrel(b2WorldId worldId, float x, float y, float scale);
    ~Barrel();
    
    void update(float dt);
    void render(sf::RenderWindow& window);
    
    b2BodyId getBodyId() const { return bodyId; }
    sf::FloatRect getBounds() const;
    
    bool isActive() const { return active; }
    void setActive(bool value) { active = value; }
    
    // Método para golpear el barril
    void hit() { active = false; }
};
