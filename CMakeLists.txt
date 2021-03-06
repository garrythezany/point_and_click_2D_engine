cmake_minimum_required(VERSION 3.8)
project(PNC_Engine)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        rooms/studio.h
        src/main.cpp
        src/Game.cpp
        src/Game.h
        src/Cursor.cpp
        src/Cursor.h
        src/Player.cpp
        src/Player.h
        src/Room.cpp
        src/Room.h
        src/Item.cpp
        src/Item.h
        src/World.cpp
        src/World.h
        src/Pathfinder.cpp
        src/Pathfinder.h
        src/Music.cpp
        src/Music.h)

configure_file(images/sprite_full.png sprite_full.png COPYONLY)
configure_file(images/cursor.png cursor.png COPYONLY)
configure_file(images/shop.png shop.png COPYONLY)
configure_file(images/bedroom.png bedroom.png COPYONLY)
configure_file(images/arcade.png arcade.png COPYONLY)
configure_file(images/studio.png studio.png COPYONLY)
configure_file(music/track1.ogg track1.ogg COPYONLY)

add_executable(SFML ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(SFML ${SFML_LIBRARIES})
endif()