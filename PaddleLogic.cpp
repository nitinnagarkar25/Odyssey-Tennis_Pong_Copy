//
// Created by Nitin Nagarkar on 4/17/24.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <random>
#include "Paddle.h"

#include <iostream>
#include <thread>
#include <random>
#include <cmath>

using namespace sf;
using namespace std;

void movePaddle(sf::Event& event, sf::RectangleShape& paddle, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey)
{

    if (event.type == sf::Event::KeyPressed && event.key.code == upKey)
    {
        paddle.move(0,-20);
    }
    if(event.type == sf::Event::KeyPressed && event.key.code == downKey)
    {
        paddle.move(0,20);
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == leftKey)
    {
        paddle.move(-20,0);
    }
    if(event.type == sf::Event::KeyPressed && event.key.code == rightKey)
    {
        paddle.move(20,0);

    }
}

void checkCollision(sf::CircleShape& ball, sf::RectangleShape& paddle1, sf::RectangleShape& paddle2, sf::Sound& hit, sf::Vector2f& ballVelocity, std::mt19937& gen, float& angle)
{
    uniform_real_distribution<float> angleDist(45.0f, 135.0f); // Adjust angle range as needed
    ball.move(ballVelocity);
    if (ball.getPosition().x + ball.getRadius() >= paddle1.getPosition().x+5 &&
        ball.getPosition().x - ball.getRadius() <= paddle1.getPosition().x-5 &&
        ball.getPosition().y + ball.getRadius() >= paddle1.getPosition().y+5 &&
        ball.getPosition().y - ball.getRadius() <= paddle1.getPosition().y-5 + paddle1.getSize().y)
    {
        hit.play();
        // Ball is approaching from the right, reverse x and set a random y velocity
        ballVelocity.x = -ballVelocity.x; // Ensure positive x velocity
        angleDist = std::uniform_real_distribution<float>(-45.0f, 45.0f);
        angle = angleDist(gen);
        ballVelocity.y = 20 * sin(angle * M_PI / 180.0f);
    }
    else if (ball.getPosition().x - ball.getRadius() <= paddle2.getPosition().x-5  &&
             ball.getPosition().x + ball.getRadius() >= paddle2.getPosition().x+5 &&
             ball.getPosition().y + ball.getRadius() >= paddle2.getPosition().y+5 &&
             ball.getPosition().y - ball.getRadius() <= paddle2.getPosition().y-5 + paddle2.getSize().y)
    {
        hit.play();
        // Ball is approaching from the left, reverse x and set a random y velocity
        ballVelocity.x = -ballVelocity.x; // Ensure negative x velocity
        angleDist = std::uniform_real_distribution<float>(-45.0f, 45.0f);
        angle = angleDist(gen);
        ballVelocity.y = 20* sin(angle * M_PI / 180.0f);
    }

    if (ball.getPosition().y < 0 || ball.getPosition().y + ball.getRadius() * 2 > 480)
    {

        ballVelocity.y = -ballVelocity.y;
    }
    if (ball.getPosition().x < 0 || ball.getPosition().x + ball.getRadius() * 2 > 750)
    {

        ballVelocity.x = -ballVelocity.x;

    }

}