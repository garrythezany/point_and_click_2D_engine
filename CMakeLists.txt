cmake_minimum_required(VERSION 3.8)
project(SFML)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        OpenSans-Regular.ttf
        src/Node.cpp
        src/Node.h
        src/Polygon.cpp
        src/Polygon.h
        src/NavMesh.cpp
        src/NavMesh.h
        src/Game.cpp
        src/Game.h
        src/Cursor.cpp
        src/Cursor.h
        src/Player.cpp
        src/Player.h)

configure_file(images/sprite_full.png sprite_full.png COPYONLY)
configure_file(images/cursor.png cursor.png COPYONLY)
configure_file(images/shop.png shop.png COPYONLY)
configure_file(images/bedroom.png bedroom.png COPYONLY)
configure_file(images/arcade.png arcade.png COPYONLY)

add_executable(SFML ${SOURCE_FILES} src/Node.cpp src/Node.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(SFML ${SFML_LIBRARIES})
endif()