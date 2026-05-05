#include <iostream>
#include "AudioSystem.h"

bool AudioSystem::load(const std::string &path)
{
    return music.openFromFile(path);
}

void AudioSystem::play()
{
    music.play();
}

Seconds AudioSystem::getSongTime() const
{
    return Seconds{music.getPlayingOffset().asSeconds()};
}