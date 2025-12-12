#include "../include/Menu.h"
#include <iostream>

Menu::Menu() 
    : selectedIndex(0)
    , currentState(MenuState::MAIN_MENU)
    , musicVolume(50.0f)
    , soundVolume(70.0f)
{
    // Try to load font
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Warning: Could not load font" << std::endl;
    }
    
    setupMainMenu();
    setupSettings();
}

void Menu::setupMainMenu() {
    menuItems.clear();
    
    std::vector<std::string> options = {"JUGAR", "AJUSTES", "SALIR"};
    
    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setCharacterSize(48);
        text.setPosition(300, 200 + i * 80);
        text.setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
        menuItems.push_back(text);
    }
}

void Menu::setupSettings() {
    settingsItems.clear();
    
    // Title
    sf::Text title;
    title.setFont(font);
    title.setString("AJUSTES");
    title.setCharacterSize(56);
    title.setPosition(300, 50);
    title.setFillColor(sf::Color::Yellow);
    settingsItems.push_back(title);
    
    // Music volume label
    sf::Text musicLabel;
    musicLabel.setFont(font);
    musicLabel.setString("Volumen Musica:");
    musicLabel.setCharacterSize(32);
    musicLabel.setPosition(200, 150);
    musicLabel.setFillColor(sf::Color::White);
    settingsItems.push_back(musicLabel);
    
    // Sound volume label
    sf::Text soundLabel;
    soundLabel.setFont(font);
    soundLabel.setString("Volumen Sonido:");
    soundLabel.setCharacterSize(32);
    soundLabel.setPosition(200, 250);
    soundLabel.setFillColor(sf::Color::White);
    settingsItems.push_back(soundLabel);
    
    // Back button
    sf::Text back;
    back.setFont(font);
    back.setString("VOLVER");
    back.setCharacterSize(40);
    back.setPosition(300, 400);
    back.setFillColor(sf::Color::White);
    settingsItems.push_back(back);
    
    // Setup volume bars
    volumeMusicBar.setSize(sf::Vector2f(300, 30));
    volumeMusicBar.setPosition(200, 200);
    volumeMusicBar.setFillColor(sf::Color(100, 100, 100));
    volumeMusicBar.setOutlineThickness(2);
    volumeMusicBar.setOutlineColor(sf::Color::White);
    
    volumeSoundBar.setSize(sf::Vector2f(300, 30));
    volumeSoundBar.setPosition(200, 300);
    volumeSoundBar.setFillColor(sf::Color(100, 100, 100));
    volumeSoundBar.setOutlineThickness(2);
    volumeSoundBar.setOutlineColor(sf::Color::White);
    
    updateVolumeBar();
}

void Menu::updateVolumeBar() {
    volumeMusicFill.setSize(sf::Vector2f(300 * (musicVolume / 100.0f), 30));
    volumeMusicFill.setPosition(200, 200);
    volumeMusicFill.setFillColor(sf::Color::Green);
    
    volumeSoundFill.setSize(sf::Vector2f(300 * (soundVolume / 100.0f), 30));
    volumeSoundFill.setPosition(200, 300);
    volumeSoundFill.setFillColor(sf::Color::Green);
}

void Menu::handleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (currentState == MenuState::MAIN_MENU) {
            if (event.key.code == sf::Keyboard::Up) {
                selectedIndex = (selectedIndex - 1 + menuItems.size()) % menuItems.size();
                for (size_t i = 0; i < menuItems.size(); ++i) {
                    menuItems[i].setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
                }
            }
            else if (event.key.code == sf::Keyboard::Down) {
                selectedIndex = (selectedIndex + 1) % menuItems.size();
                for (size_t i = 0; i < menuItems.size(); ++i) {
                    menuItems[i].setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
                }
            }
            else if (event.key.code == sf::Keyboard::Enter) {
                if (selectedIndex == 0) { // JUGAR
                    currentState = MenuState::PLAYING;
                }
                else if (selectedIndex == 1) { // AJUSTES
                    currentState = MenuState::SETTINGS;
                    selectedIndex = 0;
                }
            }
        }
        else if (currentState == MenuState::SETTINGS) {
            if (event.key.code == sf::Keyboard::Left) {
                if (selectedIndex == 0) { // Music volume
                    musicVolume = std::max(0.0f, musicVolume - 5.0f);
                    updateVolumeBar();
                }
                else if (selectedIndex == 1) { // Sound volume
                    soundVolume = std::max(0.0f, soundVolume - 5.0f);
                    updateVolumeBar();
                }
            }
            else if (event.key.code == sf::Keyboard::Right) {
                if (selectedIndex == 0) { // Music volume
                    musicVolume = std::min(100.0f, musicVolume + 5.0f);
                    updateVolumeBar();
                }
                else if (selectedIndex == 1) { // Sound volume
                    soundVolume = std::min(100.0f, soundVolume + 5.0f);
                    updateVolumeBar();
                }
            }
            else if (event.key.code == sf::Keyboard::Up) {
                selectedIndex = (selectedIndex - 1 + 3) % 3;
            }
            else if (event.key.code == sf::Keyboard::Down) {
                selectedIndex = (selectedIndex + 1) % 3;
            }
            else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape) {
                if (selectedIndex == 2) { // VOLVER
                    currentState = MenuState::MAIN_MENU;
                    selectedIndex = 0;
                    setupMainMenu();
                }
            }
        }
    }
}

void Menu::update() {
    // Update animations or effects here if needed
}

void Menu::render(sf::RenderWindow& window) {
    if (currentState == MenuState::MAIN_MENU) {
        // Draw title
        sf::Text title;
        title.setFont(font);
        title.setString("DONKEY KONG");
        title.setCharacterSize(72);
        title.setPosition(200, 50);
        title.setFillColor(sf::Color::Red);
        window.draw(title);
        
        // Draw menu items
        for (auto& item : menuItems) {
            window.draw(item);
        }
    }
    else if (currentState == MenuState::SETTINGS) {
        // Draw settings items
        for (auto& item : settingsItems) {
            window.draw(item);
        }
        
        // Draw volume bars
        window.draw(volumeMusicBar);
        window.draw(volumeMusicFill);
        window.draw(volumeSoundBar);
        window.draw(volumeSoundFill);
        
        // Highlight selected option
        if (selectedIndex == 0) {
            sf::RectangleShape highlight(sf::Vector2f(320, 50));
            highlight.setPosition(190, 190);
            highlight.setFillColor(sf::Color::Transparent);
            highlight.setOutlineColor(sf::Color::Yellow);
            highlight.setOutlineThickness(3);
            window.draw(highlight);
        }
        else if (selectedIndex == 1) {
            sf::RectangleShape highlight(sf::Vector2f(320, 50));
            highlight.setPosition(190, 290);
            highlight.setFillColor(sf::Color::Transparent);
            highlight.setOutlineColor(sf::Color::Yellow);
            highlight.setOutlineThickness(3);
            window.draw(highlight);
        }
        else if (selectedIndex == 2) {
            settingsItems[3].setFillColor(sf::Color::Yellow);
        }
        else {
            settingsItems[3].setFillColor(sf::Color::White);
        }
    }
}
