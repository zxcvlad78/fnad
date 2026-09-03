#pragma once
#include <string>
#include <sstream>
#include "SFML/Graphics.hpp"

namespace parsing {
    inline sf::Color str_to_color(const std::string& str) {
        std::stringstream ss(str);
        int r = 0, g = 0, b = 0, a = 255;
    
        if (ss >> r >> g >> b) {
            ss >> a; 
        }
    
        return sf::Color(
            static_cast<std::uint8_t>(r), 
            static_cast<std::uint8_t>(g), 
            static_cast<std::uint8_t>(b), 
            static_cast<std::uint8_t>(a)
        );
    }
    inline std::string color_to_str(const sf::Color& color) {
        return std::to_string(color.r) + " " + std::to_string(color.g) + " " + std::to_string(color.b) + " " + std::to_string(color.a);
    }
}