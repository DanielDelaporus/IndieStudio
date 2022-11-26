# CMAKE DONE BY VINCENT DOUROUX

cmake_minimum_required(VERSION 3.10)

project(bomberman)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(Irrlicht_DIR "lib/Irrlicht_windows")

include(${Irrlicht_DIR}/FindIrrlicht.cmake)

add_executable(bomberman 
    src/main.cpp
    src/Map.cpp
    src/EventReceiver.cpp
    src/GameState.cpp
    src/Blocks/Bomb.cpp
    src/Blocks/Box.cpp
    src/Blocks/Wall.cpp
    src/Blocks/Powerup.cpp
    src/Entities/Player.cpp
    src/Entities/Bot.cpp
    src/AI/AI.cpp
)

IF (MSVC)     # Windows
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR "./lib/SFML/lib/cmake/SFML")
    file(COPY ./lib/SFML/bin/openal32.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
    file(COPY ./lib/SFML/bin/sfml-audio-2.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
    file(COPY ./lib/SFML/bin/sfml-audio-d-2.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)

    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/debug)
    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/Release)

    file(COPY lib/Irrlicht_windows/Irrlicht.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
    file(COPY lib/Irrlicht_windows/Irrlicht.dll DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY lib/Irrlicht_windows/Irrlicht.dll DESTINATION ${CMAKE_BINARY_DIR}/Release)
ENDIF(MSVC)

find_package(SFML 2.5 COMPONENTS audio REQUIRED)


FIND_PACKAGE( Boost 1.69)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


target_link_libraries (bomberman ${Irrlicht_LIBRARIES} sfml-audio ${Boost_LIBRARIES})

include_directories(${Irrlicht_INCLUDE_DIRS})