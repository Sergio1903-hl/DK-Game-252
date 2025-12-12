#include "../include/AudioManager.h"
#include <iostream>

AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager() 
    : musicVolume(50.0f)
    , soundVolume(70.0f)
{
    music = std::make_unique<sf::Music>();
}

AudioManager* AudioManager::getInstance() {
    if (!instance) {
        instance = new AudioManager();
    }
    return instance;
}

bool AudioManager::loadSound(const std::string& name, const std::string& filename) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        std::cerr << "Failed to load sound: " << filename << std::endl;
        return false;
    }
    
    soundBuffers[name] = buffer;
    sounds[name] = std::make_unique<sf::Sound>();
    sounds[name]->setBuffer(soundBuffers[name]);
    sounds[name]->setVolume(soundVolume);
    
    return true;
}

bool AudioManager::loadMusic(const std::string& filename) {
    if (!music->openFromFile(filename)) {
        std::cerr << "Failed to load music: " << filename << std::endl;
        return false;
    }
    music->setVolume(musicVolume);
    return true;
}

void AudioManager::playSound(const std::string& name) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second->play();
    }
}

void AudioManager::playMusic(bool loop) {
    music->setLoop(loop);
    music->play();
}

void AudioManager::stopMusic() {
    music->stop();
}

void AudioManager::pauseMusic() {
    music->pause();
}

void AudioManager::resumeMusic() {
    music->play();
}

void AudioManager::setMusicVolume(float volume) {
    musicVolume = volume;
    music->setVolume(volume);
}

void AudioManager::setSoundVolume(float volume) {
    soundVolume = volume;
    for (auto& sound : sounds) {
        sound.second->setVolume(volume);
    }
}
