/*
 * Author: Dylan Turner
 * Description: 
 */

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <GameSettings.hpp>
#include <Engine.hpp>
#include <Snake.hpp>
#include <Environment.hpp>

int main(void) {
    sf::RenderWindow window(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        WINDOW_TITLE
    );

    vpet::Background bg(BG_COLOR);
    vpet::Snake snake;
    vpet::HideOut hideOut;

    std::vector<vpet::GameObject *> gameObjs;
    gameObjs.push_back(&bg);
    gameObjs.push_back(&snake);
    gameObjs.push_back(&hideOut);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    vpet::Engine engine(window, gameObjs);
    return 0;
}
