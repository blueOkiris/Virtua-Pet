/*
 * Author: Dylan Turner
 * Description: Implementation of Snake behavior
 */

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <GameSettings.hpp>
#include <Utility.hpp>
#include <Engine.hpp>
#include <Snake.hpp>

using namespace vpet;

SnakeTongue::SnakeTongue(void) : _animCounter(0) {
}

void SnakeTongue::draw(
        sf::RenderTarget &target, sf::RenderStates states) const {
    auto y =
        SNAKE_MAX_WIDTH * (1 + 4 * std::sin(_animCounter) / 2)
        - SNAKE_MAX_WIDTH * 1.25;
    if(y < 0) {
        return;
    }

    sf::RectangleShape tongue;
    tongue.setFillColor(SNAKE_TONGUE_FILL);
    tongue.setOutlineColor(SNAKE_TONGUE_OLINE_COL);
    tongue.setOutlineThickness(SNAKE_TONGUE_OLINE_THIK);
    tongue.setSize(SNAKE_TONGUE_SIZE);
    tongue.setOrigin(SNAKE_MAX_WIDTH / 2 - SNAKE_TONGUE_SIZE.x / 2, y);
    tongue.setPosition(headPos);
    tongue.rotate(headRot);
    target.draw(tongue);
}

void SnakeTongue::update(void) {
    _animCounter += SNAKE_TONGUE_ANIM_SPEED;
    if(_animCounter > SNAKE_TONGUE_MAX_ANIM) {
        _animCounter = 0;
    }
}

SnakeSegment::SnakeSegment(void) : child(nullptr), move(false) {
}

void SnakeSegment::update(void) {
    if(child != nullptr) {
        child->position = _positions[SNAKE_PATH_SIZE - 1];
        child->move = move;
    }

    if(!move) {
        return;
    }
    for(int i = SNAKE_PATH_SIZE - 1; i >= 1; i--) {
        _positions[i] = _positions[i - 1];
    }
    _positions[0] = position;
}

SnakeBody::SnakeBody(void) : SnakeSegment(), _segmentId(0) {
}

void SnakeBody::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::CircleShape body;

    // Make body smaller as it goes behind
    auto pos = static_cast<double>(SNAKE_SEGMENTS - 1 - _segmentId);
    auto radius =
        pos * static_cast<double>(SNAKE_MAX_WIDTH - SNAKE_MIN_WIDTH)
        / SNAKE_SEGMENTS + SNAKE_MIN_WIDTH;
    
    body.setRadius(radius);
    body.setFillColor(SNAKE_FILL_COLOR);
    body.setOutlineColor(SNAKE_BORDER_COLOR);
    body.setOutlineThickness(SNAKE_BORDER_WIDTH);
    body.setOrigin(radius, radius);
    body.setPosition(position);
    target.draw(body);
}

void SnakeBody::setSegmentId(const int id) {
    _segmentId = id;
}

SnakeHead::SnakeHead(void) : SnakeSegment() {
}

void SnakeHead::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::CircleShape head;
    head.setRadius(SNAKE_MAX_WIDTH);
    head.setFillColor(SNAKE_FILL_COLOR);
    head.setOutlineColor(SNAKE_BORDER_COLOR);
    head.setOutlineThickness(SNAKE_BORDER_WIDTH);
    head.setOrigin(SNAKE_MAX_WIDTH, SNAKE_MAX_WIDTH);
    head.setPosition(position);
    target.draw(head);
}

Snake::Snake(void) :
        _state(SnakeBehavior::Hide),
        _rot(90.0), _moveDir(90.0), _rotDiffAcc(0.0) {
    _head.position = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    _head.child = &_bodies[0];
    for(int i = 1; i < SNAKE_SEGMENTS; i++) {
        _bodies[i - 1].setSegmentId(i);
        if(i != SNAKE_SEGMENTS - 1) {
            _bodies[i - 1].child = &_bodies[i];
        }
    }
}

void Snake::update(void) {
    switch(_state) {
        case SnakeBehavior::Hide:
            if(util::distance(_head.position, HIDEOUT_BACK_LOC) > 10) {
                _head.move = true;
                _moveDir =
                    util::angle(HIDEOUT_BACK_LOC - _head.position) * 180 / 3.14;
            } else {
                _state = SnakeBehavior::PokeHead;
            }
        break;

        case SnakeBehavior::PokeHead:
            if(util::distance(_head.position, HIDEOUT_POKE_HEAD_LOC) > 10) {
                _head.move = true;
                _moveDir =
                    util::angle(HIDEOUT_POKE_HEAD_LOC - _head.position)
                    * 180 / 3.14;
            } else {
                _head.move = false;
            }
        break;
        
        case SnakeBehavior::Curious:
            break;
        
        case SnakeBehavior::Thristy:
            break;
        
        case SnakeBehavior::Uncomfortable:
            break;
    }

    _moveSnake();

    _head.update();
    for(auto &body : _bodies) {
        body.update();
    }

    _tongue.headPos = _head.position;
    _tongue.headRot = _rot;
    _tongue.update();
}

void Snake::_moveSnake(void) {
    if(!_head.move) {
        return;
    }
    
    // Move head towards move dir
    _rotDiffAcc += SNAKE_SWIVEL_SPEED * 3.14 / FPS;
    _rot = _moveDir + SNAKE_SWIVEL_AMOUNT * sin(_rotDiffAcc);

    _head.position.x += SNAKE_HEAD_SPEED / FPS * std::sin(_rot * 3.14 / 180);
    _head.position.y += SNAKE_HEAD_SPEED / FPS * -std::cos(_rot * 3.14 / 180);
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_tongue);

    for(int i = SNAKE_SEGMENTS - 1; i >= 1; i--) {
        target.draw(_bodies[i - 1]);
    }
    target.draw(_head);

    sf::CircleShape leftEye;
    leftEye.setRadius(SNAKE_EYE_SIZE);
    leftEye.setFillColor(SNAKE_EYE_FILL_COLOR);
    leftEye.setOutlineColor(SNAKE_EYE_BORDER_COLOR);
    leftEye.setOutlineThickness(SNAKE_EYE_BORDER_WIDTH);
    leftEye.setOrigin(SNAKE_MAX_WIDTH + SNAKE_EYE_SIZE, SNAKE_EYE_SIZE);
    leftEye.setPosition(_head.position);
    leftEye.rotate(_rot);
    target.draw(leftEye);

    sf::CircleShape rightEye;
    rightEye.setRadius(SNAKE_EYE_SIZE);
    rightEye.setFillColor(SNAKE_EYE_FILL_COLOR);
    rightEye.setOutlineColor(SNAKE_EYE_BORDER_COLOR);
    rightEye.setOutlineThickness(SNAKE_EYE_BORDER_WIDTH);
    rightEye.setOrigin(-SNAKE_MAX_WIDTH + SNAKE_EYE_SIZE, SNAKE_EYE_SIZE);
    rightEye.setPosition(_head.position);
    rightEye.rotate(_rot);
    target.draw(rightEye);
}
