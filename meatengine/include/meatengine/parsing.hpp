#pragma once
#include <string>
#include <sstream>
#include "SFML/Graphics.hpp"


namespace meatengine::parsing {
    inline sf::Color str_to_color(const std::string& str) {
        std::stringstream ss(str);
        int r = 0, g = 0, b = 0, a = 255;
    
        if (ss >> r >> g >> b) { ss >> a; }
    
        return sf::Color(r, g, b, a);
    }

    inline sf::Color str_to_color(const std::vector<std::string>& args) {
        if (args.size() < 3 || args.size() > 4) return sf::Color::Black;
        int r = std::stoi(args[0]);
        int g = std::stoi(args[1]);
        int b = std::stoi(args[2]);
        int a = (args.size() == 4) ? std::stoi(args[3]) : 255;
        return sf::Color(r, g, b, a);
    }

    inline std::string color_to_str(const sf::Color& color) {
        return std::to_string(color.r) + " " + std::to_string(color.g) + " " + std::to_string(color.b) + " " + std::to_string(color.a);
    }
}