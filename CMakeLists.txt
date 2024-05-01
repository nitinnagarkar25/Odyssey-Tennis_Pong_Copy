cmake_minimum_required(VERSION 3.27)
project(Odyssey-Tennis-Pong)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        Paddle.h
        Ball.h
        PaddleLogic.cpp
)
add_executable(Odyssey-Tennis-Pong ${SOURCE_FILES})
include_directories(/usr/local/include)

configure_file(images/Hello.png images/Hello.png COPYONLY)
configure_file(images/ping_pong.jpeg images/ping_pong.jpeg COPYONLY)
configure_file(images/Clay.png images/Clay.png COPYONLY)
configure_file(images/Grass.png images/Grass.png COPYONLY)
configure_file(images/IntroPhoto.jpg images/IntroPhoto.jpg COPYONLY)
configure_file(font/font.ttf font/font.ttf COPYONLY)
configure_file(font/square-deal.ttf font/square-deal.ttf COPYONLY)
configure_file(sound/tennis-hit.wav sound/tennis-hit.wav COPYONLY)
configure_file(sound/tennis-hit2.wav sound/tennis-hit2.wav COPYONLY)
configure_file(sound/button.wav sound/button.wav COPYONLY)


find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Odyssey-Tennis-Pong sfml-system sfml-window sfml-graphics sfml-audio sfml-network)