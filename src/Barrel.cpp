#include "../include/Barrel.h"
#include <iostream>
#include <cmath>

Barrel::Barrel(b2WorldId worldId, float x, float y, float scale)
    : scale(scale)
    , radius(15.0f)
    , active(true)
    , hasTexture(false)
{
    // Try to load texture
    if (texture.loadFromFile("assets/textures/barrel.png")) {
        sprite.setTexture(texture);
        // Auto-escalar al tamaño del barril (diámetro = radius * 2)
        float targetSize = radius * 2.0f;
        float scaleX = targetSize / texture.getSize().x;
        float scaleY = targetSize / texture.getSize().y;
        sprite.setScale(scaleX, scaleY);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        hasTexture = true;
        std::cout << "Barrel texture loaded: " << texture.getSize().x << "x" << texture.getSize().y 
                  << " scaled to: " << targetSize << "x" << targetSize << std::endl;
    }
    
    // Create dynamic Box2D body for barrel
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = {x / scale, y / scale};
    bodyId = b2CreateBody(worldId, &bodyDef);
    
    // Create circle shape
    b2Circle circle = {{0.0f, 0.0f}, radius / scale};
    
    // Create shape def
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.5f;  // Más fricción para que ruede mejor
    shapeDef.material.restitution = 0.2f; // Menos rebote
    b2CreateCircleShape(bodyId, &shapeDef, &circle);
    
    // Iniciar con velocidad hacia la DERECHA (hacia el hueco de Level 4)
    b2Body_SetLinearVelocity(bodyId, {3.0f, 0.5f});
    
    // Setup SFML shape (fallback)
    shape.setRadius(radius);
    shape.setFillColor(sf::Color(205, 133, 63));
    shape.setOrigin(radius, radius);
}

Barrel::~Barrel() {
    if (B2_IS_NON_NULL(bodyId)) {
        b2DestroyBody(bodyId);
    }
}

void Barrel::update(float dt) {
    // Update position from Box2D body
    b2Vec2 position = b2Body_GetPosition(bodyId);
    float posX = position.x * scale;
    float posY = position.y * scale;
    
    shape.setPosition(posX, posY);
    
    if (hasTexture) {
        sprite.setPosition(posX, posY);
    }
    
    // Rotate based on angular velocity
    b2Rot rotation = b2Body_GetRotation(bodyId);
    float angle = b2Rot_GetAngle(rotation);
    float angleDeg = angle * 180.0f / 3.14159f;
    
    shape.setRotation(angleDeg);
    if (hasTexture) {
        sprite.setRotation(angleDeg);
    }
    
    // Los barriles ruedan con fuerza constante hacia el hueco
    b2Vec2 velocity = b2Body_GetLinearVelocity(bodyId);
    
    // Si el barril choca con una pared (está muy cerca del borde), rebotar
    // y cambiar la dirección basada en la posición actual
    
    float dir = 1.0f;
    
    // Rebotar en las paredes
    if (posX <= 30) {
        // Chocó con pared izquierda - ir a la derecha
        dir = 1.0f;
        if (velocity.x < 0) {
            b2Body_SetLinearVelocity(bodyId, {2.0f, velocity.y});
        }
    } else if (posX >= 1170) {
        // Chocó con pared derecha - ir a la izquierda
        dir = -1.0f;
        if (velocity.x > 0) {
            b2Body_SetLinearVelocity(bodyId, {-2.0f, velocity.y});
        }
    } else {
        // Dirección normal basada en el nivel
        // Niveles con hueco DERECHO: Level 4 (Y~220), Level 2 (Y~480) - ir DERECHA
        // Niveles con hueco IZQUIERDO: Level 3 (Y~350), Level 1 (Y~610) - ir IZQUIERDA
        if (posY < 280) {
            dir = 1.0f;  // Level 4 o Top - ir DERECHA
        } else if (posY < 420) {
            dir = -1.0f; // Level 3 - ir IZQUIERDA
        } else if (posY < 550) {
            dir = 1.0f;  // Level 2 - ir DERECHA
        } else if (posY < 680) {
            dir = -1.0f; // Level 1 - ir IZQUIERDA
        } else {
            // Ground - seguir en la dirección actual o ir al centro
            dir = (velocity.x >= 0) ? 1.0f : -1.0f;
        }
    }
    
    // Aplicar fuerza para que ruede (solo cuando no está cayendo)
    if (std::abs(velocity.y) < 3.0f) {
        b2Body_ApplyForceToCenter(bodyId, {dir * 5.0f, 0.0f}, true);
        
        // Si está muy lento, darle impulso extra
        if (std::abs(velocity.x) < 1.5f) {
            b2Body_ApplyLinearImpulseToCenter(bodyId, {dir * 0.8f, 0.0f}, true);
        }
    }
    
    // Limitar velocidad máxima
    if (velocity.x > 5.0f) {
        b2Body_SetLinearVelocity(bodyId, {5.0f, velocity.y});
    } else if (velocity.x < -5.0f) {
        b2Body_SetLinearVelocity(bodyId, {-5.0f, velocity.y});
    }
    
    // Limitar velocidad vertical
    if (velocity.y > 10.0f) {
        b2Body_SetLinearVelocity(bodyId, {velocity.x, 10.0f});
    }
}

void Barrel::render(sf::RenderWindow& window) {
    if (active) {
        if (hasTexture) {
            window.draw(sprite);
        } else {
            window.draw(shape);
        }
    }
}

sf::FloatRect Barrel::getBounds() const {
    return shape.getGlobalBounds();
}
