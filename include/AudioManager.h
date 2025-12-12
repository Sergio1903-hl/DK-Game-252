#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <memory>

class AudioManager {
private:
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, std::unique_ptr<sf::Sound>> sounds;
    std::unique_ptr<sf::Music> music;
    
    float musicVolume;
    float soundVolume;
    
    static AudioManager* instance;
    
    AudioManager();
    
public:
    static AudioManager* getInstance();
    
    bool loadSound(const std::string& name, const std::string& filename);
    bool loadMusic(const std::string& filename);
    
    void playSound(const std::string& name);
    void playMusic(bool loop = true);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();
    
    void setMusicVolume(float volume);
    void setSoundVolume(float volume);
    
    float getMusicVolume() const { return musicVolume; }
    float getSoundVolume() const { return soundVolume; }
};
