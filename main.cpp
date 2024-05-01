// All the libraries used
/* Name: Nitin Nagarkar - Odyssey
 * Project: Pong Game (2D)
 * Start page, then game begins with a toss
 */
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

using namespace sf;
using namespace std;

// Main block

int main()
{


    enum GameState{Instructions,Court,toss,ready,play,winner,end};
    GameState state = Instructions;


    int dir = 0; // to decide the direction of the ball
    sf::RenderWindow window(sf::VideoMode(1000, 480), "SFML Tennis Game"); // creating a window of certain size
    sf::Texture t1;

    sf::Texture t2;
    sf::Texture t3;
    sf::Texture t4;
//    sf::View view(sf::FloatRect(0, 0, 750, 480)); // Initial viewport setup
//    window.setView(view);
//     setting a variable for the background
    t1.loadFromFile("images/ping_pong.jpeg");
    t2.loadFromFile("images/Clay.png");
    t3.loadFromFile("images/Grass.png");
    t4.loadFromFile("images/IntroPhoto.jpg");
    sf::Sprite background2(t2);
    sf::Sprite background3(t3);
    sf::Sprite background(t1); // loading the background
    sf::Sprite background4(t4);
    //backgroundSprite.setTextureRect(sf::IntRect(0, 0, window.getSize().x * 2, window.getSize().y))
    window.setFramerateLimit(30); // sprite frame rate

    sf::SoundBuffer tHit;
    if (!tHit.loadFromFile("sound/tennis-hit2.wav"))
    {
        return -1;
    }

    sf::SoundBuffer clickSound;
    if (!clickSound.loadFromFile("sound/button.wav"))
    {
        return -1;
    }

    sf::Sound hit;

    sf::Sound click;

    hit.setBuffer(tHit);
    click.setBuffer(clickSound);

    sf::Text text1;
    sf::Text text2;
    sf::Text text3;
    sf::Text text4;
    sf::Text text5;
    sf::Text text6;
    sf::Text text7;
    sf::Text text8;
    sf::Text text9;
    sf::Text text10;

    int court;



    background.setScale(1.80,1.90); // changing the scale of the background
    background2.setScale(0.477,0.610687);
    background3.setScale(0.477,0.621762);
    background4.setScale(0.65104167,0.3125);


    // Set up the paddles
    sf::RectangleShape paddle1(sf::Vector2f(20, 100));


    paddle1.setFillColor(Color::Black);
    paddle1.setOutlineColor(Color(0,58,0));
    paddle1.setOutlineThickness(3);

    sf::RectangleShape paddle2(sf::Vector2f(20, 100));


    paddle2.setFillColor(Color::Black);
    paddle2.setOutlineColor(Color(0,58,0));
    paddle2.setOutlineThickness(3);

    // Set up the ball
    sf::CircleShape ball(15);
    //ball.setPosition(375, 240);

    ball.setFillColor(Color::Green);
    ball.setOutlineColor(Color::Black);
    ball.setOutlineThickness(3);


    // Set up ball movement
    Vector2f ballVelocity(5, 5);

    sf::RectangleShape button(sf::Vector2f(200, 30));
    button.setFillColor(Color::Black);
    button.setOutlineColor(Color(0,128,0));
    button.setOutlineThickness(5);

    sf::RectangleShape score(sf::Vector2f(200,70));

    score.setFillColor(Color(0,128,0));

    score.setOutlineColor(Color::White);
    score.setOutlineThickness(5);
    score.setPosition(780,400);
    sf::RectangleShape border1(sf::Vector2f(10,50));
    sf::RectangleShape border2(sf::Vector2f(10,50));
    sf::RectangleShape border3(sf::Vector2f (150,10));



    sf::RectangleShape button2(sf::Vector2f(200, 30));
    button2.setFillColor(Color::Black);
    button2.setOutlineColor(Color(0,128,0));
    button2.setOutlineThickness(5);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> angleDist(45.0f, 135.0f); // Adjust angle range as needed
    float angle = angleDist(gen);

    ballVelocity.x = 10;
    ballVelocity.y = 20 * sin(angle * M_PI / 180.0f);


    // Load font for text display
    sf::Font font;
    sf::Font font2;

    const float movementSpeed = 200.0f;

    //window.draw(background);
    if (!font.loadFromFile("font/font.ttf"))
    {
        // Handle font loading error
        return -1;
    }
    if (!font2.loadFromFile("font/square-deal.ttf"))
    {
        // Handle font loading error
        return -1;
    }
    text9.setFont(font);
    text9.setCharacterSize(20);
    text9.setFillColor(sf::Color::White);
    text9.setStyle(sf::Text::Bold);
    text9.setPosition(300,400);

    text10.setFont(font);
    text10.setCharacterSize(20);
    text10.setFillColor(sf::Color::White);
    text10.setStyle(sf::Text::Bold);
    text10.setPosition(300,400);

    int score1 = 0;
    int score2 = 0;

    string YourScore1;
    string YourScore2;

    while (window.isOpen())
    {

//        sf::Event event5;
//        while (window.pollEvent(event5)) {
//            if (event5.type == sf::Event::Closed)
//                window.close();
//            else if (event5.type == sf::Event::Resized) {
//                // Adjust the viewport to keep the game world visible
//                sf::FloatRect visibleArea(0, 0, event5.size.width, event5.size.height);
//                window.setView(sf::View(visibleArea));
//            }
//        }

        if (state == Instructions) // when state is Instructions
        {
            window.draw(background4);


            text1.setFont(font2);
            text1.setCharacterSize(35); // setting the character size in pixels
            text1.setFillColor(sf::Color::Yellow); // setting the color of the font
            text1.setStyle(sf::Text::Bold); // text style
            text1.setPosition(280,130); // position of the text
            text1.setString("      WELCOME!!\n"
                            "This is Tennis Pong!\n"
                            "Face off with your Opponent!\n "
                            "First person to reach 10 points\n "
                            " WINS !! "
                            "Good luck!!"); // the contents of the string that needs to be displayed

            text9.setPosition(360,400);
            text9.setString(" Choose Court ");
            button.setPosition(350, 400);

            window.draw(text1);
            window.draw(button);
            window.draw(text9);



            Event p; // a new event type variable
            while (window.pollEvent(p)) // window event
            {
                if (p.type == sf::Event::Closed)
                {
                    window.close();
                }
                if (p.type == sf::Event::MouseMoved)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (text9.getGlobalBounds().contains(mousePos)) {
                        // Mouse is hovering over the text
                        text9.setFillColor(sf::Color::Red);
                        window.draw(text9);
                    }

                }

                if (p.type == sf::Event::MouseButtonPressed)
                {
                    if (p.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        if (text9.getGlobalBounds().contains(mousePos))
                        {
                            click.play();
                            // Mouse left button is pressed while hovering over the text
                            // Perform animation here (e.g., scale the text)
                            text9.setScale(1.2f, 1.2f);
                            state = Court;


                        }

                    }
                }

                if (p.type == sf::Event::MouseButtonReleased)
                {
                    if (p.mouseButton.button == sf::Mouse::Left)
                    {
                        // Mouse left button is released
                        // Reset the text scale to its original size
                        text9.setScale(1.0f, 1.0f);

                    }

                }

            }
//            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//            {
//                state = toss;
//            }
        }
        if (state == Court)
        {

            window.clear();
            window.draw(background4);

            text2.setFont(font);
            text2.setCharacterSize(40); // setting the character size in pixels
            text2.setFillColor(sf::Color::White); // setting the color of the font
            text2.setStyle(sf::Text::Bold); // text style
            text2.setPosition(90,200); // position of the text
            text2.setString(" HARD COURT "); // the contents of the string that needs to be displayed
            text4.setFont(font);
            text4.setCharacterSize(40); // setting the character size in pixels
            text4.setFillColor(sf::Color::White); // setting the color of the font
            text4.setStyle(sf::Text::Bold); // text style
            text4.setPosition(560,200); // position of the text
            text4.setString(" CLAY COURT "); // the contents of the string that needs to be displayed

            window.draw(text2);
            window.draw(text4);

            sf::Event event;
            while (window.pollEvent(event))
            {

                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                if (event.type == sf::Event::MouseMoved)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (text2.getGlobalBounds().contains(mousePos)) {
                        // Mouse is hovering over the text
                        text2.setFillColor(sf::Color::Red);
                        window.draw(text2);
                    }
                    if (text4.getGlobalBounds().contains(mousePos)) {
                        // Mouse is hovering over the text
                        text4.setFillColor(sf::Color::Red);
                        window.draw(text4);
                    }
                }

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        click.play();
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        if (text2.getGlobalBounds().contains(mousePos))
                        {
                            // Mouse left button is pressed while hovering over the text
                            // Perform animation here (e.g., scale the text)
                            text2.setScale(1.2f, 1.2f);
                            state = toss;
                            ball.setPosition(70, 240);
                            court = 1;

                        }
                        else if (text4.getGlobalBounds().contains(mousePos))
                        {
                            // Mouse left button is pressed while hovering over the text
                            // Perform animation here (e.g., scale the text)
                            text4.setScale(1.2f, 1.2f);
                            state = toss;
                            ball.setPosition(650, 240);
                            court = 2;
                        }
                    }
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        // Mouse left button is released
                        // Reset the text scale to its original size
                        text2.setScale(1.0f, 1.0f);
                        text4.setScale(1.0f, 1.0f);
                    }

                }
            }

        }

        if (state == toss)
        {
            window.clear();
            if (court == 1)
            {
                window.draw(background3);
            }
            else if (court == 2)
            {
                window.draw(background2);
            }


            text2.setFont(font);
            text2.setCharacterSize(40); // setting the character size in pixels
            text2.setFillColor(sf::Color::Black); // setting the color of the font
            text2.setStyle(sf::Text::Bold); // text style
            text2.setPosition(90,200); // position of the text
            text2.setString(" HEADS "); // the contents of the string that needs to be displayed
            text4.setFont(font);
            text4.setCharacterSize(40); // setting the character size in pixels
            text4.setFillColor(sf::Color::Black); // setting the color of the font
            text4.setStyle(sf::Text::Bold); // text style
            text4.setPosition(460,200); // position of the text
            text4.setString(" TAILS "); // the contents of the string that needs to be displayed

            window.draw(text2);
            window.draw(text4);

            sf::Event event;
            while (window.pollEvent(event))
            {

                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                if (event.type == sf::Event::MouseMoved)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (text2.getGlobalBounds().contains(mousePos)) {
                        // Mouse is hovering over the text
                        text2.setFillColor(sf::Color::Red);
                        window.draw(text2);
                    }
                    if (text4.getGlobalBounds().contains(mousePos)) {
                        // Mouse is hovering over the text
                        text4.setFillColor(sf::Color::Red);
                        window.draw(text4);
                    }
                }

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        click.play();
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        if (text2.getGlobalBounds().contains(mousePos))
                        {
                            // Mouse left button is pressed while hovering over the text
                            // Perform animation here (e.g., scale the text)
                            text2.setScale(1.2f, 1.2f);
                            state = ready;
                            ball.setPosition(70, 240);

                        }
                        else if (text4.getGlobalBounds().contains(mousePos))
                        {
                            // Mouse left button is pressed while hovering over the text
                            // Perform animation here (e.g., scale the text)
                            text4.setScale(1.2f, 1.2f);
                            state = ready;
                            ball.setPosition(650, 240);
                        }
                    }
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        // Mouse left button is released
                        // Reset the text scale to its original size
                        text2.setScale(1.0f, 1.0f);
                        text4.setScale(1.0f, 1.0f);
                    }

                }
            }

        }

        if (state == ready)
        {

            paddle1.setPosition(50, 200);
            paddle2.setPosition(680, 200);
            YourScore1 = to_string(score1);
            YourScore2 = to_string(score2);

            text5.setFont(font2); // select the font
            text5.setCharacterSize(24); // setting the character size in pixels
            text5.setFillColor(sf::Color::Yellow); // setting the color of the font
            text5.setStyle(sf::Text::Bold); // text style
            text5.setPosition(800,400);
            text5.setString("PLayer 1 ");

            text6.setFont(font2); // select the font
            text6.setCharacterSize(24); // setting the character size in pixels
            text6.setFillColor(sf::Color::Yellow); // setting the color of the font
            text6.setStyle(sf::Text::Bold); // text style
            text6.setPosition(800,440);
            text6.setString("Player 2 ");

            text7.setFont(font2); // select the font
            text7.setCharacterSize(24); // setting the character size in pixels
            text7.setFillColor(sf::Color::Yellow); // setting the color of the font
            text7.setStyle(sf::Text::Bold); // text style
            text7.setPosition(960,400);
            text7.setString(YourScore1);

            text8.setFont(font2); // select the font
            text8.setCharacterSize(24); // setting the character size in pixels
            text8.setFillColor(sf::Color::Yellow); // setting the color of the font
            text8.setStyle(sf::Text::Bold); // text style
            text8.setPosition(960,440);
            text8.setString(YourScore2);




            if (court == 1)
            {
                window.draw(background3);
            }
            else if (court == 2)
            {
                window.draw(background2);
            }
            window.draw(paddle1);
            window.draw(paddle2);
            window.draw(ball);
            window.draw(text5);
            window.draw(text6);
            window.draw(text7);
            window.draw(text8);

            sf::Event event;
            while (window.pollEvent(event))
            {
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B)
                {
                    click.play();
                    state = play;
                }
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

        }


        if (state == play)
        {
            checkCollision(ball, paddle1, paddle2,hit, ballVelocity, gen, angle);

            if(ball.getPosition().x+ ball.getRadius() * 2 > 750)
            {
                score2++;
                YourScore2 = to_string(score2);
            }
            if(ball.getPosition().x < 0)
            {
                score1++;
                YourScore1 = to_string(score1);
            }

            if (score1 > 10 || score2 > 10)
            {
                state = winner;
            }





            // Process events
            sf::Event event;
            while (window.pollEvent(event))
            {

                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                movePaddle(event,paddle2, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right);
                movePaddle(event, paddle1, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);



                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        // Get the position where the mouse was clicked
                        sf::Vector2f clickPosition(event.mouseButton.x, event.mouseButton.y);
                        // Move the sprite to the clicked position
                        if (event.mouseButton.x > 375)
                        {
                            paddle2.setPosition(clickPosition);
                        }

                        else
                        {
                            paddle1.setPosition(clickPosition);
                        }

                    }
                }


            }
            text5.setFont(font2); // select the font
            text5.setCharacterSize(24); // setting the character size in pixels
            text5.setFillColor(sf::Color::Yellow); // setting the color of the font
            text5.setStyle(sf::Text::Bold); // text style
            text5.setPosition(800,400);
            text5.setString("PLayer 1 ");

            text6.setFont(font2); // select the font
            text6.setCharacterSize(24); // setting the character size in pixels
            text6.setFillColor(sf::Color::Yellow); // setting the color of the font
            text6.setStyle(sf::Text::Bold); // text style
            text6.setPosition(800,440);
            text6.setString("Player 2 ");

            text7.setFont(font2); // select the font
            text7.setCharacterSize(24); // setting the character size in pixels
            text7.setFillColor(sf::Color::Yellow); // setting the color of the font
            text7.setStyle(sf::Text::Bold); // text style
            text7.setPosition(960,400);
            text7.setString(YourScore1);

            text8.setFont(font2); // select the font
            text8.setCharacterSize(24); // setting the character size in pixels
            text8.setFillColor(sf::Color::Yellow); // setting the color of the font
            text8.setStyle(sf::Text::Bold); // text style
            text8.setPosition(960,440);
            text8.setString(YourScore2);




            // Clear the window
            window.clear();

            // Draw paddles and ball
            if (court == 1)
            {
                window.draw(background3);
            }
            else if (court == 2)
            {
                window.draw(background2);
            }
            window.draw(score);
            window.draw(paddle1);
            window.draw(paddle2);
            window.draw(ball);
            window.draw(text5);
            window.draw(text6);
            window.draw(text7);
            window.draw(text8);

        }


        if (state == winner)
        {
            window.clear();
            text3.setFont(font);
            text3.setCharacterSize(35); // setting the character size in pixels
            text3.setFillColor(sf::Color::Yellow); // setting the color of the font
            text3.setStyle(sf::Text::Bold); // text style
            text3.setPosition(50,200); // position of the text
            if (score1 > score2)
            {
                text3.setString("       Player 1 wins!\n "
                                "You move to the second round\n"); // the contents of the string that needs to be displayed
                text9.setPosition(100,400);
                text9.setString("Next Round");
                button.setPosition(100, 400);
                text10.setPosition(500,400);
                text10.setString("End Game");
                button2.setPosition(500,400);

            }
            else
            {
                text3.setString("       Player 2 wins!\n "
                                "You move to the second round\n"); // the contents of the string that needs to be displayed
                text9.setPosition(100,400);
                text9.setString("Next Round");
                button.setPosition(100, 400);
                text10.setPosition(500,400);
                text10.setString("End Game");
                button2.setPosition(500,400);
            }
            sf::Event p;
            while (window.pollEvent(p)) // window event
            {
                if (p.type == sf::Event::Closed)
                {
                    window.close();
                }
                if (p.type == sf::Event::MouseMoved)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (text9.getGlobalBounds().contains(mousePos)) {
                        // Mouse is hovering over the text
                        text9.setFillColor(sf::Color::Red);
                        window.draw(text9);
                    }

                }

                if (p.type == sf::Event::MouseButtonPressed)
                {
                    if (p.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        if (text9.getGlobalBounds().contains(mousePos))
                        {
                            click.play();
                            // Mouse left button is pressed while hovering over the text
                            // Perform animation here (e.g., scale the text)
                            text9.setScale(1.2f, 1.2f);
                            state = toss;


                        }
                        if (text10.getGlobalBounds().contains(mousePos))
                        {
                            click.play();
                            // Mouse left button is pressed while hovering over the text
                            // Perform animation here (e.g., scale the text)
                            text9.setScale(1.2f, 1.2f);
                            window.close();


                        }


                    }
                }

                if (p.type == sf::Event::MouseButtonReleased)
                {
                    if (p.mouseButton.button == sf::Mouse::Left)
                    {
                        // Mouse left button is released
                        // Reset the text scale to its original size
                        text9.setScale(1.0f, 1.0f);

                    }

                }

            }
            sf::Event event;
            while (window.pollEvent(event))
            {
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N)
                {
                    state = Court;
                    score1 = 0;
                    score2 = 0;
                }
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
                {
                    state = end;
                }


            }


            if (court == 1)
            {
                window.draw(background3);
            }
            else if (court == 2)
            {
                window.draw(background2);
            }
            window.draw(text3);
            window.draw(button);
            window.draw(button2);
            window.draw(text9);
            window.draw(text10);

        }

        if (state == end)
        {
            window.close();
        }



        // Display the contents of the window
        window.display();
    }

    return 0;

}




