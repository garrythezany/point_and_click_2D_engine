//
// Created by Roman Hock on 20.10.17.
//

#include "Music.h"

BRO::Music::Music(std::string filePath) {
    audio.openFromFile(filePath);
}