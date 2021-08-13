/*
 * Author: Dylan Turner
 * Description: Implementation of environment game objects
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include <GameSettings.hpp>
#include <Engine.hpp>
#include <Environment.hpp>

using namespace vpet;

HideOut::HideOut(void) {
    if(!_png.loadFromFile(HIDEOUT_PNG_SRC)) {
        std::cerr
            << "Failed to load file '" << HIDEOUT_PNG_SRC << "'!" << std::endl;
    }
}

void HideOut::update(void) {

}

void HideOut::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite spr;
    spr.setTexture(_png);
    target.draw(spr);
}
