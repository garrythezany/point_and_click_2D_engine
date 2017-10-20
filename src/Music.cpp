//
// Created by Roman Hock on 20.10.17.
//

#include "Music.h"

BRO::Music::Music(const std::string &filePath) {
    audio.openFromFile(filePath);
}

void BRO::Music::loop() {
    if (audio.getStatus() == 0 || audio.getStatus() == 1){
        audio.play();
    }
    if (audio.getStatus() == 2){
        if (audio.getPlayingOffset().asMilliseconds() >= audio.getDuration().asMilliseconds()){
            audio.stop();
            audio.play();
        }
    }
}