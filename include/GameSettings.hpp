/*
 * Author: Dylan Turner
 * Description: Storage for all important settings in the game
 */

#pragma once

#define WINDOW_WIDTH            1280
#define WINDOW_HEIGHT           720
#define WINDOW_TITLE            "Virtua-Pet"
#define FPS                     60.0

#define SNAKE_MAX_WIDTH         20
#define SNAKE_MIN_WIDTH         8
#define SNAKE_FILL_COLOR        sf::Color::Green
#define SNAKE_BORDER_COLOR      sf::Color::Black
#define SNAKE_BORDER_WIDTH      4
#define SNAKE_SEGMENTS          25
#define SNAKE_HEAD_SPEED        256
#define SNAKE_SWIVEL_SPEED      1.25
#define SNAKE_SWIVEL_AMOUNT     45
#define SNAKE_PATH_SIZE         5

#define SNAKE_EYE_SIZE          6
#define SNAKE_EYE_FILL_COLOR    sf::Color::White
#define SNAKE_EYE_BORDER_COLOR  sf::Color::Black
#define SNAKE_EYE_BORDER_WIDTH  4

#define SNAKE_TONGUE_ANIM_SPEED 0.05
#define SNAKE_TONGUE_MAX_ANIM   (2 * 3.14)
#define SNAKE_TONGUE_SIZE       sf::Vector2f(8, 16)
#define SNAKE_TONGUE_FILL       sf::Color::Red
#define SNAKE_TONGUE_OLINE_COL  sf::Color::Black
#define SNAKE_TONGUE_OLINE_THIK 4

#define BG_COLOR                sf::Color(0x0F, 0x3F, 0x13, 0xFF)

#define HIDEOUT_PNG_SRC         "img/hideout.png"
#define HIDEOUT_BACK_LOC        sf::Vector2f(-30, -50)
#define HIDEOUT_POKE_HEAD_LOC   sf::Vector2f(380, 240)
