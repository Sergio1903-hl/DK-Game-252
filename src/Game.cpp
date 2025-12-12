#include "../include/Game.h"
#include <iostream>

Game::Game() 
    : window(sf::VideoMode(1200, 800), "Donkey Kong")
    , score(0)
    , lives(3)
    , level(1)
    , gameOver(false)
    , gameState(GameState::MENU)
    , barrelSpawnTime(3.0f)
    , SCALE(30.0f)
{
    window.setFramerateLimit(60);
    
    // Create Box2D world with gravity
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 9.8f};
    worldId = b2CreateWorld(&worldDef);
    
    // Initialize audio manager
    audioManager = AudioManager::getInstance();
    
    // Create menu
    menu = std::make_unique<Menu>();
    
    // Load assets
    loadAssets();
    
    setupWorld();
}

Game::~Game() {
    b2DestroyWorld(worldId);
}

void Game::run() {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        
        processEvents();
        
        if (!gameOver) {
            update(dt);
        }
        
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        if (gameState == GameState::MENU) {
            handleMenuInput(event);
        }
        else if (gameState == GameState::PLAYING) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    pauseGame();
                }
            }
        }
        else if (gameState == GameState::PAUSED) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    resumeGame();
                }
                if (event.key.code == sf::Keyboard::M) {
                    gameState = GameState::MENU;
                    audioManager->stopMusic();
                }
            }
        }
        else if (gameState == GameState::GAME_OVER) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    startGame();
                }
                if (event.key.code == sf::Keyboard::M) {
                    gameState = GameState::MENU;
                }
            }
        }
    }
}

void Game::update(float dt) {
    if (gameState == GameState::MENU) {
        menu->update();
        return;
    }
    
    if (gameState != GameState::PLAYING) {
        return;
    }
    
    // Update physics
    b2World_Step(worldId, dt, 4);
    
    // Handle player input
    player->handleInput(dt);
    player->update(dt);
    
    // Update Donkey Kong
    if (donkeyKong) {
        donkeyKong->update(dt);
        
        // Spawn barrels from DK
        if (donkeyKong->shouldThrowBarrel()) {
            spawnBarrel();
            donkeyKong->resetThrowTimer();
            audioManager->playSound("barrel_roll");
        }
    }
    
    // Update Princess
    if (princess) {
        princess->update(dt);
        
        // Check if player reached princess (win condition)
        sf::FloatRect playerBounds = player->getBounds();
        if (playerBounds.intersects(princess->getBounds())) {
            winLevel();
        }
    }
    
    // Update barrels
    for (auto it = barrels.begin(); it != barrels.end();) {
        (*it)->update(dt);
        b2Vec2 pos = b2Body_GetPosition((*it)->getBodyId());
        float barrelY = pos.y * SCALE;
        
        // Remover barriles que caen muy fuera de pantalla (ajustado para ventana 1200x800)
        if (barrelY > 850) {
            it = barrels.erase(it);
        } else {
            ++it;
        }
    }
    
    checkCollisions();
    
    // Update UI
    scoreText.setString("Score: " + std::to_string(score));
    livesText.setString("Lives: " + std::to_string(lives));
    levelText.setString("Level: " + std::to_string(level));
}

void Game::render() {
    window.clear(sf::Color::Black);
    
    if (gameState == GameState::MENU) {
        menu->render(window);
        window.display();
        return;
    }
    
    // Draw background
    if (backgroundTexture.getSize().x > 0) {
        window.draw(backgroundSprite);
    }
    
    // Render platforms
    for (auto& platform : platforms) {
        platform->render(window);
    }
    
    // Render ladders
    for (auto& ladder : ladders) {
        ladder->render(window);
    }
    
    // Render Donkey Kong
    if (donkeyKong) {
        donkeyKong->render(window);
    }
    
    // Render Princess
    if (princess) {
        princess->render(window);
    }
    
    // Render barrels
    for (auto& barrel : barrels) {
        barrel->render(window);
    }
    
    // Render player
    if (player) {
        player->render(window);
    }
    
    // Render UI
    if (font.getInfo().family != "") {
        window.draw(scoreText);
        window.draw(livesText);
        window.draw(levelText);
    }
    
    // Render game state overlays
    if (gameState == GameState::PAUSED) {
        sf::RectangleShape overlay(sf::Vector2f(800, 600));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(overlay);
        
        if (font.getInfo().family != "") {
            sf::Text pauseText;
            pauseText.setFont(font);
            pauseText.setString("PAUSADO\n\nESC - Continuar\nM - Menu");
            pauseText.setCharacterSize(48);
            pauseText.setFillColor(sf::Color::White);
            pauseText.setPosition(250, 200);
            window.draw(pauseText);
        }
    }
    else if (gameState == GameState::GAME_OVER) {
        sf::RectangleShape overlay(sf::Vector2f(800, 600));
        overlay.setFillColor(sf::Color(0, 0, 0, 200));
        window.draw(overlay);
        
        if (font.getInfo().family != "") {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setString("GAME OVER!\n\nR - Reintentar\nM - Menu");
            gameOverText.setCharacterSize(48);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(200, 200);
            window.draw(gameOverText);
        }
    }
    
    window.display();
}

void Game::setupWorld() {
    // Create player - empieza abajo a la derecha
    player = std::make_unique<Player>(worldId, 1000.0f, 700.0f, SCALE);
    
    // Clear existing platforms and ladders
    platforms.clear();
    ladders.clear();
    
    // PAREDES INVISIBLES en los bordes de la ventana
    // Los barriles rebotan en estas paredes
    // Pared IZQUIERDA (X=0)
    platforms.push_back(std::make_unique<Platform>(worldId, -10, 400, 20, 800, SCALE, false, 0.0f));
    // Pared DERECHA (X=1200)
    platforms.push_back(std::make_unique<Platform>(worldId, 1210, 400, 20, 800, SCALE, false, 0.0f));
    
    // DISEÑO DONKEY KONG CLÁSICO
    // Plataformas completas - los barriles rebotan en las paredes y bajan por gravedad
    // Ventana: 1200x800
    
    // Ground (Y=740) - COMPLETO
    platforms.push_back(std::make_unique<Platform>(worldId, 600, 740, 1200, 20, SCALE, false, 0.0f));
    
    // Level 1 (Y=610) - Hueco IZQUIERDA
    platforms.push_back(std::make_unique<Platform>(worldId, 700, 610, 1000, 20, SCALE, false, 0.0f));
    
    // Level 2 (Y=480) - Hueco DERECHA
    platforms.push_back(std::make_unique<Platform>(worldId, 500, 480, 1000, 20, SCALE, false, 0.0f));
    
    // Level 3 (Y=350) - Hueco IZQUIERDA
    platforms.push_back(std::make_unique<Platform>(worldId, 700, 350, 1000, 20, SCALE, false, 0.0f));
    
    // Level 4 (Y=220) - Hueco DERECHA
    platforms.push_back(std::make_unique<Platform>(worldId, 500, 220, 1000, 20, SCALE, false, 0.0f));
    
    // Top (Y=90) - Plataforma donde está DK
    platforms.push_back(std::make_unique<Platform>(worldId, 300, 90, 500, 20, SCALE, false, 0.0f));
    
    // Escaleras - posicionadas al lado de las plataformas para fácil acceso
    // Escalera izquierda inferior
    ladders.push_back(std::make_unique<Ladder>(180, 600, 60, 135, SCALE));     // Ground↔Level1 (izq)
    // Escalera derecha media
    ladders.push_back(std::make_unique<Ladder>(970, 470, 60, 135, SCALE));   // Level1↔Level2 (der)
    // Escalera izquierda
    ladders.push_back(std::make_unique<Ladder>(180, 340, 60, 135, SCALE));     // Level2↔Level3 (izq)
    // Escalera derecha
    ladders.push_back(std::make_unique<Ladder>(970, 210, 60, 135, SCALE));   // Level3↔Level4 (der)
    // Escalera central superior
    ladders.push_back(std::make_unique<Ladder>(220, 80, 60, 135, SCALE));    // Level4↔Top (centro)
    
    // DK está en la plataforma Top
    donkeyKong = std::make_unique<DonkeyKong>(450.0f, 45.0f, SCALE);
    
    // Princess está a la izquierda
    princess = std::make_unique<Princess>(150.0f, 45.0f, SCALE);
}

void Game::spawnBarrel() {
    // Spawn barrel from Donkey Kong's position
    if (donkeyKong) {
        sf::Vector2f dkPos = donkeyKong->getPosition();
        barrels.push_back(std::make_unique<Barrel>(worldId, dkPos.x + 30, dkPos.y, SCALE));
    }
}

void Game::checkCollisions() {
    // Check player-ladder collision
    player->setOnLadder(false);
    sf::FloatRect playerBounds = player->getBounds();
    
    for (auto& ladder : ladders) {
        if (playerBounds.intersects(ladder->getBounds())) {
            player->setOnLadder(true);
            break;
        }
    }
    
    // Obtener estado del jugador
    b2Vec2 playerPos = b2Body_GetPosition(player->getBodyId());
    b2Vec2 playerVel = b2Body_GetLinearVelocity(player->getBodyId());
    float playerBottom = (playerPos.y * SCALE) + 14.0f;
    
    // Si está escalando hacia arriba en una escalera, FORZAR el movimiento hacia arriba
    // ignorando las colisiones de Box2D
    if (player->isClimbing() && player->isOnLadder() && playerVel.y < 0) {
        // El jugador está subiendo por escalera
        // Teletransportar hacia arriba para ignorar colisiones con plataformas
        b2Vec2 newPos = playerPos;
        newPos.y -= 0.1f; // Mover hacia arriba
        b2Body_SetTransform(player->getBodyId(), newPos, b2Body_GetRotation(player->getBodyId()));
    }
    
    // Verificar si el jugador está sobre alguna plataforma
    player->setOnGround(false);
    
    // Solo verificar colisión con plataformas si NO está escalando hacia arriba
    bool isClimbingUp = player->isClimbing() && player->isOnLadder() && playerVel.y < 0;
    
    if (!isClimbingUp) {
        for (auto& platform : platforms) {
            sf::FloatRect platBounds = platform->getBounds();
            float platformTop = platform->getTop();
            
            // El jugador está sobre la plataforma si sus pies están cerca del tope
            if (playerBottom >= platformTop - 5 && playerBottom <= platformTop + 20 &&
                playerBounds.left + playerBounds.width > platBounds.left &&
                playerBounds.left < platBounds.left + platBounds.width) {
                player->setOnGround(true);
                break;
            }
        }
    }
    
    // Detectar si el jugador presiona Q para golpear barriles
    bool isHitting = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    sf::FloatRect hitBoxBounds = player->getHitBoxBounds();
    
    // Check player-barrel collision
    if (!barrels.empty()) {
        for (auto it = barrels.begin(); it != barrels.end();) {
            sf::FloatRect barrelBounds = (*it)->getBounds();
            
            // Detectar golpe con Q
            if (isHitting && hitBoxBounds.intersects(barrelBounds) && (*it)->isActive()) {
                (*it)->hit();  // Marcar barril como inactivo
                updateScore(100);  // Dar 100 puntos por golpear
                audioManager->playSound("barrel_roll");  // Sonido de impacto
                it = barrels.erase(it);  // Eliminar barril
                continue;
            }
            
            // Detectar colisión normal con barril (jugador saltando sobre él)
            if (playerBounds.intersects(barrelBounds) && (*it)->isActive()) {
                // Verificar si el jugador está saltando SOBRE el barril
                // El jugador está sobre el barril si su parte inferior está por encima del centro del barril
                float playerBottom = playerBounds.top + playerBounds.height;
                float barrelCenterY = barrelBounds.top + barrelBounds.height / 2.0f;
                
                // Si el jugador está arriba del barril (no intersección profunda)
                if (playerBottom < barrelCenterY) {
                    // El jugador está saltando sobre el barril
                    updateScore(100);  // Dar 100 puntos
                    audioManager->playSound("barrel_roll");
                    it = barrels.erase(it);  // Eliminar barril
                    continue;
                } else {
                    // Colisión normal - el jugador muere
                    gameOverScreen();
                    return;
                }
            }
            ++it;
        }
    }
    
    // Check player win condition - llegar a la princesa
    if (princess) {
        sf::FloatRect princessBounds = princess->getBounds();
        if (playerBounds.intersects(princessBounds)) {
            // ¡Ganó el nivel!
            level++;
            setupWorld();
            return;
        }
    }
    
    // Check if player falls off
    if (playerPos.y * SCALE > 850) {
        gameOverScreen();
    }
}

void Game::updateScore(int points) {
    score += points;
}

void Game::loadAssets() {
    // Try to load background
    if (backgroundTexture.loadFromFile("assets/textures/background.png")) {
        backgroundSprite.setTexture(backgroundTexture);
        // Auto-escalar al tamaño de la ventana (1200x800)
        float scaleX = 1200.0f / backgroundTexture.getSize().x;
        float scaleY = 800.0f / backgroundTexture.getSize().y;
        backgroundSprite.setScale(scaleX, scaleY);
        std::cout << "Background texture loaded: " << backgroundTexture.getSize().x << "x" << backgroundTexture.getSize().y 
                  << " scaled to: 1200x800" << std::endl;
    }
    
    // Load sounds
    audioManager->loadSound("jump", "assets/sounds/jump.wav");
    audioManager->loadSound("barrel_roll", "assets/sounds/barrel_roll.wav");
    audioManager->loadSound("game_over", "assets/sounds/game_over.wav");
    audioManager->loadSound("win", "assets/sounds/win.wav");
    audioManager->loadSound("menu_select", "assets/sounds/menu_select.wav");
    
    // Load music - nueva música de fondo
    if (!audioManager->loadMusic("assets/music/sndbck.mp3")) {
        std::cerr << "Warning: Could not load background music sndbck.mp3" << std::endl;
        // Intentar cargar música alternativa
        audioManager->loadMusic("assets/music/game_music.ogg");
    }
    
    // Load font
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Warning: Could not load font" << std::endl;
    }
    
    // Setup UI text
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    
    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::Red);
    livesText.setPosition(10, 40);
    
    levelText.setFont(font);
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::Yellow);
    levelText.setPosition(10, 70);
}

void Game::startGame() {
    gameState = GameState::PLAYING;
    score = 0;
    lives = 3;
    level = 1;
    gameOver = false;
    barrels.clear();
    resetLevel();
    audioManager->playMusic(true);
}

void Game::pauseGame() {
    gameState = GameState::PAUSED;
    audioManager->pauseMusic();
}

void Game::resumeGame() {
    gameState = GameState::PLAYING;
    audioManager->resumeMusic();
}

void Game::resetLevel() {
    barrels.clear();
    setupWorld();
}

void Game::gameOverScreen() {
    lives--;
    
    if (lives > 0) {
        // Todavía tiene vidas - reiniciar nivel
        resetLevel();
        // La música sigue sonando, no la detenemos
    } else {
        // Game over definitivo
        gameState = GameState::GAME_OVER;
        audioManager->stopMusic();
        audioManager->playSound("game_over");
    }
}

void Game::winLevel() {
    gameState = GameState::WIN;
    audioManager->playSound("win");
    level++;
    score += 1000;
    
    // After celebration, start next level
    resetLevel();
    gameState = GameState::PLAYING;
}

void Game::handleMenuInput(sf::Event& event) {
    menu->handleInput(event);
    
    if (menu->getState() == MenuState::PLAYING) {
        startGame();
    }
    
    // Update audio volumes from menu
    audioManager->setMusicVolume(menu->getMusicVolume());
    audioManager->setSoundVolume(menu->getSoundVolume());
}
