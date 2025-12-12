#include "../include/DonkeyKong.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>

DonkeyKong::DonkeyKong(float x, float y, float scale)
    : x(x)
    , y(y)
    , scale(scale)
    , throwInterval(3.0f)
    , isAngry(false)
    , currentFrame(0)
    , frameTime(0.2f)
    , barrelsThrown(0)
    , difficulty(1.0f)
{
    // Seed random
    srand(static_cast<unsigned>(time(nullptr)));
    
    // Intervalo inicial aleatorio entre 1 y 7 segundos
    throwInterval = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 6.0f));
    
    // Try to load texture
    if (!texture.loadFromFile("assets/textures/donkey_kong.png")) {
        std::cerr << "Warning: Could not load Donkey Kong texture" << std::endl;
    }
    else {
        sprite.setTexture(texture);
        // Auto-escalar al tamaño deseado (60x80)
        float targetWidth = 60.0f;
        float targetHeight = 80.0f;
        float scaleX = targetWidth / texture.getSize().x;
        float scaleY = targetHeight / texture.getSize().y;
        sprite.setScale(scaleX, scaleY);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        std::cout << "DonkeyKong texture loaded: " << texture.getSize().x << "x" << texture.getSize().y 
                  << " scaled to: " << targetWidth << "x" << targetHeight << std::endl;
    }
    
    sprite.setPosition(x, y);
}

void DonkeyKong::update(float dt) {
    // Animation - más expresiva cuando está enojado
    float animSpeed = isAngry ? 0.1f : 0.2f;
    if (animationClock.getElapsedTime().asSeconds() > animSpeed) {
        currentFrame = (currentFrame + 1) % 4;
        animationClock.restart();
        
        // Animación más agresiva cuando enojado
        if (texture.getSize().x > 0) {
            float targetWidth = 60.0f;
            float targetHeight = 80.0f;
            float scaleVar = isAngry ? (1.0f + 0.1f * sin(currentFrame * 2)) : (1.0f + 0.05f * sin(currentFrame));
            float scaleX = (targetWidth / texture.getSize().x) * scaleVar;
            float scaleY = (targetHeight / texture.getSize().y) * scaleVar;
            sprite.setScale(scaleX, scaleY);
        }
    }
    
    // Sistema de enojo - se enoja si pasa mucho tiempo sin lanzar
    float elapsedTime = throwTimer.getElapsedTime().asSeconds();
    if (elapsedTime > throwInterval * 0.8f) {
        isAngry = true;
    }
}

void DonkeyKong::render(sf::RenderWindow& window) {
    // If no texture, draw a simple brown rectangle
    if (texture.getSize().x == 0) {
        sf::RectangleShape rect(sf::Vector2f(60, 80));
        rect.setPosition(x, y);
        rect.setFillColor(sf::Color(101, 67, 33)); // Brown
        rect.setOrigin(30, 40);
        window.draw(rect);
        
        // Draw simple face
        sf::CircleShape eye(3);
        eye.setFillColor(sf::Color::White);
        eye.setPosition(x - 15, y - 10);
        window.draw(eye);
        
        eye.setPosition(x + 10, y - 10);
        window.draw(eye);
    }
    else {
        window.draw(sprite);
    }
}

bool DonkeyKong::shouldThrowBarrel() {
    // Lógica inteligente: lanzar más barriles cuando está enojado
    float threshold = throwInterval;
    
    // Si está muy enojado, tiene chance de lanzar múltiples barriles
    if (isAngry && barrelsThrown > 5) {
        threshold *= 0.9f;
    }
    
    return throwTimer.getElapsedTime().asSeconds() > threshold;
}

void DonkeyKong::resetThrowTimer() {
    throwTimer.restart();
    barrelsThrown++;
    
    // Nuevo intervalo ALEATORIO entre 1 y 7 segundos
    throwInterval = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 6.0f));
    
    // Calmarse un poco después de lanzar
    if (barrelsThrown % 3 == 0) {
        isAngry = false;
    }
}

sf::FloatRect DonkeyKong::getBounds() const {
    return sf::FloatRect(x - 30, y - 40, 60, 80);
}
