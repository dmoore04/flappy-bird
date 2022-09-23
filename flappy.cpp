#include "flappy.hpp"
#include <iostream>

FlappyBird::FlappyBird()
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 600), "Flappy Bird", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);
    window->setPosition(sf::Vector2i(0, 0));

    gravity = frame = {0};
    space = {220.f};
    count = score = {0};
    gameover = add = {false};

    bg.loadFromFile("./resources/img/background.png");
    flappy.loadFromFile("./resources/img/flappy.png");
    pipe.loadFromFile("./resources/img/pipe.png");

    font.loadFromFile("./resources/font/flappybird.ttf");
    txt_gameover.setFont(font);
    txt_gameover.setString("Press SPACE to restart");
    txt_gameover.setPosition(200, 300);
    txt_gameover.setCharacterSize(50);
    txt_gameover.setOutlineThickness(3);

    txt_score.setFont(font);
    txt_score.setString(std::to_string(score));
    txt_score.setPosition(10, 10);
    txt_score.setCharacterSize(50);
    txt_score.setOutlineThickness(3);

    background = std::make_shared<sf::Sprite>();
    bird = std::make_shared<sf::Sprite>();
    pipeBottom = std::make_shared<sf::Sprite>();
    pipeTop = std::make_shared<sf::Sprite>();

    background->setTexture(bg);
    bird->setTexture(flappy);
    pipeBottom->setTexture(pipe);
    pipeTop->setTexture(pipe);

    bird->setPosition(
        500.f - flappy.getSize().x / 2.f,
        300.f - flappy.getSize().y / 2.f);
    bird->setScale(2.f, 2.f);
    bird->setTextureRect(sf::IntRect(0, 0, 34, 24));

    pipeBottom->setScale(1.5f, 1.5f);
    pipeTop->setScale(1.5f, -1.5f);
};

void FlappyBird::events()
{
    if (gameover && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        score = 0;
        pipes.clear();
        txt_score.setString(std::to_string(score));
        gravity = 0.f;

        bird->setPosition(
            500.f - flappy.getSize().x / 2.f,
            300.f - flappy.getSize().y / 2.f);
        gameover = false;
    }
    auto e = std::make_shared<sf::Event>();
    while (window->pollEvent(*e))
    {
        if (e->type == sf::Event::Closed)
        {
            window->close();
        }
    }
}

void FlappyBird::draw()
{
    window->clear(sf::Color::Black);
    window->draw(*background);

    for (auto &pipe : pipes)
    {
        window->draw(pipe);
    }

    window->draw(*bird);
    window->draw(txt_score);

    if (gameover)
    {
        window->draw(txt_gameover);
    }

    window->display();
    ++count;
}

void FlappyBird::movePipes()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        gravity = -8.f;
        bird->setRotation(-frame);
    }
    else
    {
        bird->setRotation(frame + gravity);
    }

    if (count % 150 == 0)
    {
        int pos = std::rand() % 275 + 175;

        pipeBottom->setPosition(1000, pos + space);
        pipeTop->setPosition(1000, pos);

        pipes.push_back(*pipeBottom);
        pipes.push_back(*pipeTop);
    }

    for (std::size_t i{}; i < pipes.size(); i++)
    {
        if (pipes[i].getGlobalBounds().intersects(bird->getGlobalBounds()))
        {
            gameover = true;
        }

        if (pipes[i].getPosition().x < -100)
        {
            pipes.erase(pipes.begin() + i);
        }

        pipes[i].move(-3, 0);

        if (pipes[i].getPosition().x == 298 && !add)
        {
            txt_score.setString(std::to_string(++score));
            add = true;
        }
        else
        {
            add = false;
        }
    }
}

void FlappyBird::setAnimeBird()
{
    frame += 0.15f;

    if (frame > 3)
    {
        frame -= 3;
    }

    bird->setTextureRect(sf::IntRect(34 * (int)frame, 0, 34, 24));
}

void FlappyBird::moveBird()
{
    bird->move(0, gravity);
    gravity += 0.5f;

    if (bird->getPosition().y > 1400 || bird->getPosition().y < -400)
    {
        gameover = true;
    }
}

void FlappyBird::game()
{
    if (!gameover)
    {
        setAnimeBird();
        moveBird();
        movePipes();
    }
}

void FlappyBird::run()
{
    while (window->isOpen())
    {
        events();
        draw();
        game();
    }
}