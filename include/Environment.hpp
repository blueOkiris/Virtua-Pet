/*
 * Author: Dylan Turner
 * Description: Definition of environment game objects
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <Engine.hpp>

namespace vpet {
    class HideOut : public GameObject {
        private:
            sf::Texture _png;
        
        public:
            HideOut(void);

            void draw(
                sf::RenderTarget &target, sf::RenderStates states
            ) const override;
            void update(void) override;
    };
}
