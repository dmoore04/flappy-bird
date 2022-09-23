#include "flappy.hpp"

int main()
{
    auto flappy = std::make_shared<FlappyBird>();
    flappy->run();
    std::srand(time(0));
    return 0;
}