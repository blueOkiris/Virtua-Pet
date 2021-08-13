/*
 * Author: Dylan Turner
 * Description: Short functions for cleaner code
 */

#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>

namespace vpet {
    namespace util {
        template<typename T>
        inline T distance(sf::Vector2<T> from, sf::Vector2<T> to) {
            return static_cast<T>(std::sqrt(
                std::pow(to.x - from.x, 2) + std::pow(to.y - from.y, 2)
            ));
        }

        template<typename T>
        inline T angle(sf::Vector2<T> dir) {
            return std::atan2(dir.x, -dir.y); // Note "up" is 0, CW+
        }

        template<typename T>
        inline T sign(T value) {
            return value > 0 ? 1 : (value < 0 ? -1 : 0);
        }
    }
}