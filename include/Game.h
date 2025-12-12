#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include <vector>
#include <memory>
#include <string>
#include "Player.h"
#include "Platform.h"
#include "Ladder.h"
#include "Barrel.h"
#include "DonkeyKong.h"
#include "Princess.h"
#include "Menu.h"
#include "AudioManager.h"
#include "Barrel_Elim.h"

enum class GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    WIN
};

class Game {
private:
    sf::RenderWindow window;
    b2WorldId worldId;
    
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Platform>> platforms;
    std::vector<std::unique_ptr<Ladder>> ladders;
    std::vector<std::unique_ptr<Barrel>> barrels;
    std::unique_ptr<DonkeyKong> donkeyKong;
    std::unique_ptr<Princess> princess;
    std::unique_ptr<Barrel_Elim> barrelElim;
    std::unique_ptr<Menu> menu;
    
    AudioManager* audioManager;
    
    sf::Clock clock;
    sf::Clock barrelSpawnClock;
    float barrelSpawnTime;
    
    sf::Font font;
    sf::Text scoreText;
    sf::Text livesText;
    sf::Text levelText;
    
    // Background
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    
    int score;
    int lives;
    int level;
    bool gameOver;
    GameState gameState;
    std::string playerName;
    
    const float SCALE = 30.0f; // pixels per meter
    
public:
    Game();
    ~Game();
    
    void run();
    b2WorldId getWorldId() const { return worldId; }
    
private:
    void processEvents();
    void update(float dt);
    void render();
    
    void setupWorld();
    void resetLevel();
    void spawnBarrel();
    void checkCollisions();
    void updateScore(int points);
    
    void handleMenuInput(sf::Event& event);
    void startGame();
    void pauseGame();
    void resumeGame();
    void gameOverScreen();
    void winLevel();
    
    void loadAssets();

    void promptPlayerName();
    void saveScoreEntry(const std::string& reason);
};
