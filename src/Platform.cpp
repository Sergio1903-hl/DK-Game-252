#include "../include/Platform.h"
#include <iostream>

Platform::Platform(b2WorldId worldId, float x, float y, float width, float height, float scale, bool oneWay, float angleDeg)
    : width(width)
    , height(height)
    , scale(scale)
    , hasTexture(false)
    , isOneWay(oneWay)
    , x(x)
    , y(y)
{
    // Try to load texture
    if (texture.loadFromFile("assets/textures/platform.png")) {
        sprite.setTexture(texture);
        
        // Auto-escalar para que la textura cubra toda la plataforma
        float scaleX = width / texture.getSize().x;
        float scaleY = height / texture.getSize().y;
        sprite.setScale(scaleX, scaleY);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        sprite.setPosition(x, y);
        hasTexture = true;
        
        std::cout << "Platform texture loaded: " << texture.getSize().x << "x" << texture.getSize().y 
                  << " scaled to: " << width << "x" << height << std::endl;
    }
    
    // Create static Box2D body for platform
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.position = {x / scale, y / scale};
    // La rotación se aplica después de crear el cuerpo
    bodyId = b2CreateBody(worldId, &bodyDef);
    float radians = angleDeg * 3.14159f / 180.0f;
    b2Body_SetTransform(bodyId, bodyDef.position, b2MakeRot(radians));
    
    // Create box shape
    b2Polygon boxShape = b2MakeBox((width / 2.0f) / scale, (height / 2.0f) / scale);
    
    // Create shape def
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.material.friction = 0.3f;
    
    // One-way platforms are sensors (no physical collision)
    if (isOneWay) {
        shapeDef.isSensor = true;
    }
    
    b2CreatePolygonShape(bodyId, &shapeDef, &boxShape);
    
    // Setup SFML shape (fallback)
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color(139, 69, 19));
    shape.setOrigin(width / 2.0f, height / 2.0f);
    shape.setPosition(x, y);
    shape.setRotation(angleDeg);
    if (hasTexture) {
        sprite.setRotation(angleDeg);
    }
}

Platform::~Platform() {
    if (B2_IS_NON_NULL(bodyId)) {
        b2DestroyBody(bodyId);
    }
}

void Platform::render(sf::RenderWindow& window) {
    if (hasTexture) {
        window.draw(sprite);
    } else {
        window.draw(shape);
    }
}

sf::FloatRect Platform::getBounds() const {
    return shape.getGlobalBounds();
}
