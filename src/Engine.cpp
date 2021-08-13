/*
 * Author: Dylan Turner
 * Description: Implementation of Engine system
 */

#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <GameSettings.hpp>
#include <Engine.hpp>

using namespace vpet;

Background::Background(const sf::Color &color) : _color(color) {
}

void Background::draw(sf::RenderTarget &target, sf::RenderStates) const {
    sf::RectangleShape shape;
    shape.setFillColor(_color);
    shape.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

    target.draw(shape);
}

void Background::update(void) {
}

Engine::Engine(
        sf::RenderWindow &win,
        const std::vector<GameObject *> &objs) : _win(win), _objs(objs) {
    auto lastTime = std::chrono::system_clock::now();
    double acc = 0.0;
    while(_win.isOpen()) {
        // Calculate delta for calculations
        const auto currTime = std::chrono::system_clock::now();
        const auto deltaTimeChrono =
            std::chrono::duration_cast<std::chrono::duration<double>>(
                currTime - lastTime
            );
        lastTime = currTime;
        const auto deltaTime = deltaTimeChrono.count();
        acc += deltaTime;

        // Update everytime we go over fps
        while(acc > 1.0 / FPS) {
            // Event processing
            sf::Event event;
            while(_win.pollEvent(event)) {
                switch(event.type) {
                    case sf::Event::Closed:
                        _win.close();
                        break;
                    
                    default:
                        break;
                }
            }

            _updateObjs();

            acc -= 1.0 / FPS;
        }

        _win.clear();
        _renderObjs();
        _win.display();
    }
}

void Engine::_updateObjs(void) {
    for(auto obj : _objs) {
        obj->update();
    }
}

void Engine::_renderObjs(void) {
    for(const auto obj : _objs) {
        obj->draw(_win, sf::RenderStates::Default);
    }
}
