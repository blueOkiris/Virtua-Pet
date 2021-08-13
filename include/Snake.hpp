/*
 * Author: Dylan Turner
 * Description: The Snake object used in the game
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <GameSettings.hpp>
#include <vector>
#include <memory>
#include <Engine.hpp>

namespace vpet {
    enum class SnakeBehavior {
        Hide, PokeHead, // Comfortable states
        Curious, Thristy,
        Uncomfortable
    };

    class SnakeTongue : public GameObject {
        private:
            float _animCounter;
            
        public:
            sf::Vector2f headPos;
            float headRot;
            
            SnakeTongue(void);

            void update(void) override;
            void draw(
                sf::RenderTarget &target, sf::RenderStates states
            ) const override;
    };

    class SnakeSegment : public GameObject {
        private:
            sf::Vector2f _positions[SNAKE_PATH_SIZE];

        public:
            sf::Vector2f position;
            SnakeSegment *child;
            bool move;

            SnakeSegment(void);
            void update(void) override;
    };

    class SnakeBody : public SnakeSegment {
        private:
            int _segmentId;
        
        public:
            SnakeBody(void);
            void setSegmentId(const int id);

            void draw(
                sf::RenderTarget &target, sf::RenderStates states
            ) const override;
    };

    class SnakeHead : public SnakeSegment {
        public:
            SnakeHead(void);

            void draw(
                sf::RenderTarget &target, sf::RenderStates states
            ) const override;
    };

    class Snake : public GameObject {
        private:
            SnakeHead _head;
            SnakeBody _bodies[SNAKE_SEGMENTS - 1];
            SnakeTongue _tongue;

            SnakeBehavior _state;
            float _rot, _moveDir, _rotDiffAcc;

            void _moveSnake(void);

        public:
            Snake();

            void draw(
                sf::RenderTarget &target, sf::RenderStates states
            ) const override;
            void update(void) override;
    };
}
