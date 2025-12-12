#include "../include/Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Player::Player(b2WorldId worldId, float x, float y, float scale) 
    : scale(scale)
    , width(36.0f)
    , height(56.0f)
    , onGround(false)
    , onLadder(false)
    , climbing(false)
    , facingRight(true)
    , moveSpeed(2.5f)
    , jumpForce(7.0f)
    , climbSpeed(3.0f)
    , hasTexture(false)
{
    // Try to load texture
    if (texture.loadFromFile("assets/textures/player.png")) {
        sprite.setTexture(texture);
        // Auto-escalar al tamaño deseado sin importar tamaño original
        float scaleX = width / texture.getSize().x;
        float scaleY = height / texture.getSize().y;
        sprite.setScale(scaleX, scaleY);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        hasTexture = true;
        std::cout << "Player texture loaded: " << texture.getSize().x << "x" << texture.getSize().y 
                  << " scaled to: " << width << "x" << height << std::endl;
    }
    else {
        std::cerr << "Warning: Could not load player texture, using shape" << std::endl;
    }
    
    // Create Box2D body
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = {x / scale, y / scale};
    bodyDef.fixedRotation = true;
    bodyId = b2CreateBody(worldId, &bodyDef);
    
    // Create shape
    b2Polygon dynamicBox = b2MakeBox((width / 2.0f) / scale, (height / 2.0f) / scale);
    
    // Create shape def
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
    
    // Setup SFML shape (fallback)
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(width / 2.0f, height / 2.0f);
}

Player::~Player() {
    if (B2_IS_NON_NULL(bodyId)) {
        b2DestroyBody(bodyId);
    }
}

void Player::handleInput(float dt) {
    b2Vec2 velocity = b2Body_GetLinearVelocity(bodyId);
    
    if (climbing && onLadder) {
        // Climbing mode - disable gravity effect
        velocity.y = 0;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            velocity.y = -climbSpeed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || 
                 sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            velocity.y = climbSpeed;
        }
        
        // Can move left/right while climbing
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocity.x = -moveSpeed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || 
                 sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocity.x = moveSpeed;
        }
        else {
            velocity.x = 0;
        }
    }
    else {
        // Normal movement mode
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocity.x = -moveSpeed;
            facingRight = false;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || 
                 sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocity.x = moveSpeed;
            facingRight = true;
        }
        else {
            velocity.x = 0;
        }
        
        // Jump - solo si está en el suelo y NO en escalera
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround && !onLadder) {
            velocity.y = -jumpForce;
            onGround = false;
        }
        
        // Empezar a escalar si está en escalera y presiona arriba/abajo
        if (onLadder && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || 
                         sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
                         sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || 
                         sf::Keyboard::isKeyPressed(sf::Keyboard::S))) {
            climbing = true;
            b2Body_SetGravityScale(bodyId, 0.0f);
        }
    }
    
    // Salir del modo escalera si no está en escalera
    if (!onLadder && climbing) {
        climbing = false;
        b2Body_SetGravityScale(bodyId, 1.0f);
    }
    
    b2Body_SetLinearVelocity(bodyId, velocity);
}

void Player::update(float dt) {
    // Update position from Box2D body
    b2Vec2 position = b2Body_GetPosition(bodyId);
    float posX = position.x * scale;
    float posY = position.y * scale;
    
    shape.setPosition(posX, posY);
    
    if (hasTexture) {
        sprite.setPosition(posX, posY);
        
        // Flip sprite based on direction (auto-escalado)
        float scaleX = width / texture.getSize().x;
        float scaleY = height / texture.getSize().y;
        
        if (facingRight) {
            sprite.setScale(scaleX, scaleY);
        } else {
            sprite.setScale(-scaleX, scaleY);
        }
    }
    
    // Check if on ground
    if (b2Body_GetLinearVelocity(bodyId).y == 0 && !climbing) {
        onGround = true;
    }
}

void Player::render(sf::RenderWindow& window) {
    if (hasTexture) {
        window.draw(sprite);
    } else {
        window.draw(shape);
    }
}

sf::FloatRect Player::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const {
    b2Vec2 pos = b2Body_GetPosition(bodyId);
    return sf::Vector2f(pos.x * scale, pos.y * scale);
}

sf::FloatRect Player::getHitBoxBounds() const {
    // Crear un área de golpe ligeramente más grande que el jugador
    sf::FloatRect bounds = shape.getGlobalBounds();
    // Expandir el área de golpe un 50% en cada dirección
    float expandX = bounds.width * 0.25f;
    float expandY = bounds.height * 0.25f;
    bounds.left -= expandX;
    bounds.top -= expandY;
    bounds.width += expandX * 2.0f;
    bounds.height += expandY * 2.0f;
    return bounds;
}

bool Player::canHit() const {
    // El jugador puede golpear si está en el suelo o en el aire (siempre que presione Q)
    return true;
}