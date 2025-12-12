#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

enum class MenuState {
    MAIN_MENU,
    SETTINGS,
    PLAYING,
    PAUSED
};

class Menu {
private:
    sf::Font font;
    std::vector<sf::Text> menuItems;
    std::vector<sf::Text> settingsItems;
    int selectedIndex;
    MenuState currentState;
    
    float musicVolume;
    float soundVolume;
    
    sf::RectangleShape volumeMusicBar;
    sf::RectangleShape volumeSoundBar;
    sf::RectangleShape volumeMusicFill;
    sf::RectangleShape volumeSoundFill;
    
public:
    Menu();
    
    void handleInput(sf::Event& event);
    void update();
    void render(sf::RenderWindow& window);
    
    MenuState getState() const { return currentState; }
    void setState(MenuState state) { currentState = state; }
    
    float getMusicVolume() const { return musicVolume; }
    float getSoundVolume() const { return soundVolume; }
    
    int getSelectedOption() const { return selectedIndex; }
    
private:
    void setupMainMenu();
    void setupSettings();
    void updateVolumeBar();
};
