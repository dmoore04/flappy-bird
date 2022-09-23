#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class FlappyBird
{
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::Sprite> background, bird, pipeBottom, pipeTop;
    std::vector<sf::Sprite> pipes;
    sf::Texture bg, flappy, pipe;
    sf::Font font;
    sf::Text txt_score, txt_gameover;
    float gravity, frame, space;
    int count, score;
    bool gameover, add;

protected:
    void draw();
    void events();
    void game();
    void movePipes();
    void setAnimeBird();
    void moveBird();

public:
    FlappyBird();
    void run();
};