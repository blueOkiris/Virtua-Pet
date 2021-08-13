/*
 * Author: Dylan Turner
 * Description: Contains the code to handle updating and drawing to the window
 */

#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

namespace vpet {
    class GameObject : public sf::Drawable {
        public:
            virtual void draw(
                sf::RenderTarget &target, sf::RenderStates states
            ) const override = 0;
            virtual void update(void) = 0;
    };

    class Background : public GameObject {
        private:
            sf::Color _color;
        
        public:
            Background(const sf::Color &color);

            void draw(
                sf::RenderTarget &target, sf::RenderStates
            ) const override;
            void update(void) override;
    };

    class Engine {
        private:
            sf::RenderWindow &_win;
            std::vector<GameObject *> _objs;

            void _updateObjs(void);
            void _renderObjs(void);
        public:
            Engine(
                sf::RenderWindow &win,
                const std::vector<GameObject *> &objs
            );
    };
}