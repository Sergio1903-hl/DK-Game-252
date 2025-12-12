#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Player {
private:
    b2BodyId bodyId;
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    bool hasTexture;
    
    float width, height;
    float scale;
    
    bool onGround;
    bool onLadder;
    bool climbing;
    bool facingRight;
    
    float moveSpeed;
    float jumpForce;
    float climbSpeed;
    
public:
    Player(b2WorldId worldId, float x, float y, float scale);
    ~Player();
    
    void handleInput(float dt);
    void update(float dt);
    void render(sf::RenderWindow& window);
    
    b2BodyId getBodyId() const { return bodyId; }
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    
    void setOnGround(bool value) { onGround = value; }
    void setOnLadder(bool value) { onLadder = value; }
    void setClimbing(bool value) { climbing = value; }
    
    bool isOnGround() const { return onGround; }
    bool isOnLadder() const { return onLadder; }
    bool isClimbing() const { return climbing; }
    
    // Método para golpear barriles (tecla Q)
    sf::FloatRect getHitBoxBounds() const;
    bool canHit() const;
};
