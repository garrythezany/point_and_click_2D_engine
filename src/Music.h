//
// Created by Roman Hock on 20.10.17.
//

#ifndef PNC_ENGINE_MUSIC_H
#define PNC_ENGINE_MUSIC_H

#include <SFML/Audio.hpp>

namespace BRO{
    class Music {
    public:
        sf::Music audio;
        explicit Music(std::string filePath);
    };

}


#endif //PNC_ENGINE_MUSIC_H
