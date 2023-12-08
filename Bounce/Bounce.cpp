// Bounce.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Menu.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

const float KB_SPEED = 0.3;

void Thud(PhysicsBodyCollisionResult result) {
    cout << "thud";
}

void MovePlayer1(PhysicsRectangle& player1, int elaspedMS) {
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        Vector2f newPos(player1.getCenter());
        newPos.y = newPos.y - (KB_SPEED * elaspedMS);
        player1.setCenter(newPos);
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        Vector2f newPos(player1.getCenter());
        newPos.y = newPos.y + (KB_SPEED * elaspedMS);
        player1.setCenter(newPos);
    }
}

void nav(Menu menu) {
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        menu.MoveUp();
        return;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        cout << "down";
        menu.MoveDown();
        return;
    }
}

void MovePlayer2(PhysicsRectangle& player2, int elaspedMS) {
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        Vector2f newPos(player2.getCenter());
        newPos.y = newPos.y - (KB_SPEED * elaspedMS);
        player2.setCenter(newPos);
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        Vector2f newPos(player2.getCenter());
        newPos.y = newPos.y + (KB_SPEED * elaspedMS);
        player2.setCenter(newPos);
    } 
}

void increaseV(PhysicsCircle& ball) {
    ball.setVelocity(Vector2f(ball.getVelocity().x * 1.05, ball.getVelocity().y * 1.05));
}

int main()
{

    RenderWindow window(VideoMode(800, 600), "Ping Pong");

    Menu menu(window.getSize().x, window.getSize().y);

    sf::Sprite bg;
    sf::Texture texture;

    texture.loadFromFile("startBG.png");
    bg.setTexture(texture);

    int option = -1;

    while (window.isOpen()) {
        sf::Event event;

        int sel = -1;

        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;
                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;

                case sf::Keyboard::Return:
                    sel = menu.GetSelected();
                    cout << "selected: " << sel << "\n";
                    break;
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        if (sel != -1) {
            option = sel;
            window.close();
        }

        window.clear();
        window.draw(bg);
        menu.draw(window);
        window.display();
    }
    

    
    if (option == 0) {

        RenderWindow window2(VideoMode(800, 600), "Easy");

        sf::Sprite bg;
        sf::Texture texture;

        texture.loadFromFile("easyBG.png");
        bg.setTexture(texture);

        World world(Vector2f(0, 0));
        PhysicsCircle ball;
        ball.setCenter(Vector2f(400, 300));
        ball.setRadius(15);
        ball.setVelocity(Vector2f(0.3, 0.3));
        world.AddPhysicsBody(ball);

        int rally = 0;

        sf::SoundBuffer buffer;

        if (buffer.loadFromFile("hitDot.wav")) {
            cout << "Sound Error";
        }

        int code[13] = {0, 0, 2, 0, 1, 0, 0, 2, 1, 0, 1, 1, 2};

        int iter = 0;

        sf::Sound hit[3];
        hit[0].setBuffer(buffer);

        sf::SoundBuffer buffer2;

        if (buffer2.loadFromFile("hitDash.wav")) {
            cout << "Sound Error";
        }

        hit[1].setBuffer(buffer2);

        Text text;
        Font font;
        if (font.loadFromFile("glories.ttf")) {
            text.setFont(font);
        }
        else {
            cout << "fail";
        }
        text.setPosition(Vector2f(345, 20));
        text.setCharacterSize(20);
        text.setString("Rally Count:");

        Text text2;
        text2.setFont(font);
        text2.setPosition(Vector2f(400, 50));
        text2.setCharacterSize(20);
        stringstream stream;
        stream << rally;
        string str_rally;

        Text winner;
        winner.setFont(font);
        winner.setPosition(Vector2f(330, 80));
        winner.setCharacterSize(20);

        stream >> str_rally;
        text2.setString(str_rally);
        cout << "\n";
        PhysicsRectangle player1;
        player1.setSize(Vector2f(15, 100));
        player1.setCenter(Vector2f(770, 300));
        world.AddPhysicsBody(player1);
        player1.setStatic(true);
        player1.onCollision = [&ball, &player1, &rally, &text2, &hit, &iter, &code](PhysicsBodyCollisionResult result) {
            if (result.object2 == ball) {
                rally++;
                stringstream stream;
                stream << rally;
                string str_rally;

                stream >> str_rally;

                if (iter >= 13) {
                    iter = 0;
                }
                
                
                 
                if (code[iter] != 2) {
                    hit[code[iter]].play();
                }
                
                text2.setString(str_rally);
                if(code[iter] != 2) {
                    hit[code[iter]].play();
                }
                iter++;
            }
            };

        PhysicsRectangle player2;
        player2.setSize(Vector2f(15, 100));
        player2.setCenter(Vector2f(30, 300));
        world.AddPhysicsBody(player2);
        player2.setStatic(true);
        player2.onCollision = [&ball, &player2, &rally, &text2, &hit, &iter, &code](PhysicsBodyCollisionResult result) {
            if (result.object2 == ball) {
                rally++;
                stringstream stream;
                stream << rally;
                string str_rally;

                if (iter >= 13) {
                    iter = 0;
                }

                stream >> str_rally;
                text2.setString(str_rally);
                
                
                
                if (code[iter] != 2) {
                    hit[code[iter]].play();
                }
                iter++;
            }
            };

        PhysicsRectangle floor;
        floor.setSize(Vector2f(800, 20));
        floor.setCenter(Vector2f(400, 600));
        floor.setFillColor(sf::Color::Red);
        floor.setStatic(true);
        floor.onCollision = [&](PhysicsBodyCollisionResult result) {
            if (result.object2 == player1) {
                player1.setVelocity(Vector2f(0, 0));
            }
            if (result.object2 == player2) {
                player2.setVelocity(Vector2f(0, 0));
            }
            };
        world.AddPhysicsBody(floor);


        PhysicsRectangle ceil;
        ceil.setSize(Vector2f(800, 20));
        ceil.setCenter(Vector2f(400, 0));
        ceil.setFillColor(sf::Color::Red);
        ceil.setStatic(true);
        ceil.onCollision = [&](PhysicsBodyCollisionResult result) {
            if (result.object2 == player1) {
                player1.setVelocity(Vector2f(0, 0));
            }
            if (result.object2 == player2) {
                player2.setVelocity(Vector2f(0, 0));
            }
            };
        world.AddPhysicsBody(ceil);

        sf::SoundBuffer endB;

        if (!endB.loadFromFile("game-over.wav")) {
            cout << "Sound Error";
        }

        sf::Sound gameOver;
        gameOver.setBuffer(endB);


        PhysicsRectangle left;
        left.setSize(Vector2f(20, 2000));
        left.setCenter(Vector2f(0, 0));
        left.setFillColor(sf::Color::Red);
        left.setStatic(true);
        left.onCollision = [&](PhysicsBodyCollisionResult result) {
            if (result.object2 == ball) {
                ball.setCenter(Vector2f(410, 400));
                ball.setVelocity(Vector2f(0, 0));
                gameOver.play();
                winner.setString("Player 1 wins!");
            }
            };
        world.AddPhysicsBody(left);


        PhysicsRectangle right;
        right.setSize(Vector2f(20, 2000));
        right.setCenter(Vector2f(800, 0));
        right.setStatic(true);
        right.setFillColor(sf::Color::Red);
        right.onCollision = [&](PhysicsBodyCollisionResult result) {
            if (result.object2 == ball) {
                ball.setCenter(Vector2f(410, 400));
                ball.setVelocity(Vector2f(0, 0));
                gameOver.play();
                winner.setString("Player 2 wins!");
                
            }
            };
        world.AddPhysicsBody(right);

        

        Clock clock;
        Time lastTime(clock.getElapsedTime());
        
        while (true) {
            // calculate MS since last frame

            Time currentTime(clock.getElapsedTime());
            Time deltaTime(currentTime - lastTime);
            int deltaTimeMS(deltaTime.asMilliseconds());
            if (deltaTimeMS > 0) {
                world.UpdatePhysics(deltaTimeMS);
                lastTime = currentTime;
                MovePlayer1(player1, deltaTimeMS);
                MovePlayer2(player2, deltaTimeMS);
            }


            

            window2.clear(Color(0, 0, 0));
            window2.draw(bg);
            window2.draw(ball);
            window2.draw(floor);
            window2.draw(ceil);
            window2.draw(left);
            window2.draw(text);
            window2.draw(text2);
            window2.draw(winner);
            window2.draw(right);
            window2.draw(player2);
            window2.draw(player1);


            window2.display();
        }
    }

    if (option == 1) {

        RenderWindow window2(VideoMode(800, 600), "Hard");

        sf::Sprite bg;
        sf::Texture texture;

        texture.loadFromFile("hardBG.png");
        bg.setTexture(texture);

        World world(Vector2f(0, 0));
        PhysicsCircle ball;
        ball.setCenter(Vector2f(400, 300));
        ball.setRadius(15);
        ball.setVelocity(Vector2f(0.3, 0.3));
        world.AddPhysicsBody(ball);

        int rally = 0;

        sf::SoundBuffer buffer;

        if (buffer.loadFromFile("hitDot.wav")) {
            cout << "Sound Error";
        }

        int code[13] = { 0, 0, 2, 0, 1, 0, 0, 2, 1, 0, 1, 1, 2 };

        int iter = 0;

        sf::Sound hit[3];
        hit[0].setBuffer(buffer);

        sf::SoundBuffer buffer2;

        if (buffer2.loadFromFile("hitDash.wav")) {
            cout << "Sound Error";
        }

        hit[1].setBuffer(buffer2);


        Text text;
        Font font;
        if (font.loadFromFile("glories.ttf")) {
            text.setFont(font);
        }
        else {
            cout << "fail";
        }
        text.setPosition(Vector2f(345, 20));
        text.setCharacterSize(20);
        text.setString("Rally Count:");

        Text text2;
        text2.setFont(font);
        text2.setPosition(Vector2f(400, 50));
        text2.setCharacterSize(20);
        stringstream stream;
        stream << rally;
        string str_rally;

        stream >> str_rally;
        text2.setString(str_rally);

        PhysicsRectangle player1;
        player1.setSize(Vector2f(15, 100));
        player1.setCenter(Vector2f(770, 300));
        world.AddPhysicsBody(player1);
        player1.setStatic(true);
        player1.onCollision = [&ball, &player1, &rally, &text2, &hit, &code, &iter](PhysicsBodyCollisionResult result) {
            if (result.object2 == ball) {
                rally++;
                stringstream stream;
                stream << rally;
                string str_rally;

                stream >> str_rally;
                cout << str_rally << "\n";

                text2.setString(str_rally);
                increaseV(ball);
                if (iter >= 13) {
                    iter = 0;
                }

                
                if (code[iter] != 2) {
                    hit[code[iter]].play();
                }
                iter++;

            }
            };

        PhysicsRectangle player2;
        player2.setSize(Vector2f(15, 100));
        player2.setCenter(Vector2f(30, 300));
        world.AddPhysicsBody(player2);
        player2.setStatic(true);
        player2.onCollision = [&ball, &player2, &rally, &text2, &iter, &code, &hit](PhysicsBodyCollisionResult result) {
            if (result.object2 == ball) {
                rally++;
                stringstream stream;
                stream << rally;
                string str_rally;

                stream >> str_rally;
                cout << str_rally << "\n";
                text2.setString(str_rally);
                increaseV(ball);
                if (iter >= 13) {
                    iter = 0;
                }

                
                if (code[iter] != 2) {
                    hit[code[iter]].play();
                }
                iter++;
            }
            };

        PhysicsRectangle floor;
        floor.setSize(Vector2f(800, 20));
        floor.setCenter(Vector2f(400, 600));
        floor.setFillColor(sf::Color::Red);
        floor.setStatic(true);
        floor.onCollision = [&](PhysicsBodyCollisionResult result) {
            if (result.object2 == player1) {
                player1.setVelocity(Vector2f(0, 0));
            }
            if (result.object2 == player2) {
                player2.setVelocity(Vector2f(0, 0));
            }
            };
        world.AddPhysicsBody(floor);


        PhysicsRectangle ceil;
        ceil.setSize(Vector2f(800, 20));
        ceil.setCenter(Vector2f(400, 0));
        ceil.setFillColor(sf::Color::Red);
        ceil.setStatic(true);
        ceil.onCollision = [&](PhysicsBodyCollisionResult result) {
            if (result.object2 == player1) {
                player1.setVelocity(Vector2f(0, 0));
            }
            if (result.object2 == player2) {
                player2.setVelocity(Vector2f(0, 0));
            }
            };
        world.AddPhysicsBody(ceil);

        sf::SoundBuffer endB;

        if (!endB.loadFromFile("game-over.wav")) {
            cout << "Sound Error";
        }

        sf::Sound gameOver;
        gameOver.setBuffer(endB);

        Text winner;
        winner.setFont(font);
        winner.setPosition(Vector2f(330, 80));
        winner.setCharacterSize(20);

        PhysicsRectangle left;
        left.setSize(Vector2f(20, 2000));
        left.setCenter(Vector2f(0, 0));
        left.setFillColor(sf::Color::Red);
        left.setStatic(true);
        left.onCollision = [&](PhysicsBodyCollisionResult result) {
            if (result.object2 == ball) {
                ball.setCenter(Vector2f(410, 400));
                ball.setVelocity(Vector2f(0, 0));
                gameOver.play();
                winner.setString("Player 1 wins!");
            }
            };
        world.AddPhysicsBody(left);

        PhysicsRectangle right;
        right.setSize(Vector2f(20, 2000));
        right.setCenter(Vector2f(800, 0));
        right.setStatic(true);
        right.setFillColor(sf::Color::Red);
        right.onCollision = [&](PhysicsBodyCollisionResult result) {
            if (result.object2 == ball) {
                ball.setCenter(Vector2f(410, 400));
                ball.setVelocity(Vector2f(0, 0));
                gameOver.play();
                winner.setString("Player 2 wins!");
            }
            };
        world.AddPhysicsBody(right);

        ball.setVelocity(Vector2f(-0.3, -0.3));

        cout << "entered";
        Clock clock;
        Time lastTime(clock.getElapsedTime());

        while (true) {
            // calculate MS since last frame

            Time currentTime(clock.getElapsedTime());
            Time deltaTime(currentTime - lastTime);
            int deltaTimeMS(deltaTime.asMilliseconds());
            if (deltaTimeMS > 0) {
                world.UpdatePhysics(deltaTimeMS);
                lastTime = currentTime;
                MovePlayer1(player1, deltaTimeMS);
                MovePlayer2(player2, deltaTimeMS);
            }




            window2.clear(Color(0, 0, 0));
            window2.draw(bg);
            window2.draw(ball);
            window2.draw(floor);
            window2.draw(ceil);
            window2.draw(left);
            window2.draw(text);
            window2.draw(text2);
            window2.draw(winner);
            window2.draw(right);
            window2.draw(player2);
            window2.draw(player1);


            window2.display();
        }
    }
}
