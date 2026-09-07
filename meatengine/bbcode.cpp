#include <meatengine/bbcode.hpp>
#include <sstream>

namespace meatengine::BBCode {
    std::vector<TextFragment> parse(const std::string& input, unsigned int default_size) {
        std::vector<TextFragment> result;

        struct StyleState {
            sf::Color color;
            unsigned int size;
            bool bold, italic, underlined;
        };

        std::vector<StyleState> style_state;
        StyleState current;
        current.color = sf::Color::White;
        current.size = default_size;
        current.bold = false;
        current.italic = false;
        current.underlined = false;

        std::string buffer;
        size_t pos = 0;
        while (pos < input.length()) {
            if (input[pos] == '[') {
                if (pos + 1 < input.length() && input[pos + 1] == '[') {
                    buffer += '[';
                    pos += 2;
                    continue;
                }
                size_t end = input.find(']', pos);
                if (end == std::string::npos) {
                    buffer += input[pos++];
                    continue;
                }
                std::string tag = input.substr(pos + 1, end - pos - 1);
                pos = end + 1;

                if (!tag.empty() && tag[0] == '/') {
                    std::string closeTag = tag.substr(1);
                    if (!buffer.empty()) {
                        result.emplace_back(buffer, current.color, current.size,
                                            current.bold, current.italic, current.underlined);
                        buffer.clear();
                    }
                    if (!style_state.empty()) {
                        current = style_state.back();
                        style_state.pop_back();
                    } else {
                        current.color = sf::Color::White;
                        current.size = default_size;
                        current.bold = false;
                        current.italic = false;
                        current.underlined = false;
                    }
                    continue;
                }

                style_state.push_back(current);
                if (!buffer.empty()) {
                    result.emplace_back(buffer, current.color, current.size, current.bold, current.italic, current.underlined);
                    buffer.clear();
                }

                if (tag == "b") {
                    current.bold = true;
                } else if (tag == "i") {
                    current.italic = true;
                } else if (tag == "u") {
                    current.underlined = true;
                } else if (tag.rfind("color=", 0) == 0) {
                    std::string colorStr = tag.substr(6);
                    current.color = parse_color(colorStr);
                } else if (tag.rfind("size=", 0) == 0) {
                    try {
                        int sz = std::stoi(tag.substr(5));
                        if (sz > 0) current.size = static_cast<unsigned int>(sz);
                    } catch (...) {}
                } else {
                    style_state.pop_back();
                }
                continue;
            }
            buffer += input[pos++];
        }
        if (!buffer.empty()) {
            result.emplace_back(buffer, current.color, current.size, current.bold, current.italic, current.underlined);
        }
        return result;
    }

    sf::Color parse_color(const std::string& str) {
        if (str.empty()) return sf::Color::White;

        if (str[0] == '#') {
            std::string hex = str.substr(1);
            unsigned int r=0, g=0, b=0, a=255;
            if (hex.length() == 6) {
                std::stringstream ss;
                ss << std::hex << hex;
                unsigned int rgb;
                ss >> rgb;
                r = (rgb >> 16) & 0xFF;
                g = (rgb >> 8) & 0xFF;
                b = rgb & 0xFF;
            } else if (hex.length() == 8) {
                std::stringstream ss;
                ss << std::hex << hex;
                unsigned int rgba;
                ss >> rgba;
                r = (rgba >> 24) & 0xFF;
                g = (rgba >> 16) & 0xFF;
                b = (rgba >> 8) & 0xFF;
                a = rgba & 0xFF;
            }
            return sf::Color(r, g, b, a);
        }

        static const std::unordered_map<std::string, sf::Color> color_map = {
            {"black", sf::Color::Black}, {"white", sf::Color::White},
            {"red", sf::Color::Red}, {"green", sf::Color::Green},
            {"blue", sf::Color::Blue}, {"cyan", sf::Color::Cyan},
            {"magenta", sf::Color::Magenta}, {"yellow", sf::Color::Yellow},
            {"gray", sf::Color(128,128,128)}, {"grey", sf::Color(128,128,128)}
        };
        auto it = color_map.find(str);
        if (it != color_map.end()) return it->second;
        return sf::Color::White;
    }
    
} // namespace meatengine::BBCode
