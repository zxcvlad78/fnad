#pragma once
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include <memory>
#include "GameState.hpp"

namespace meatengine {

class MainLoop {
public:
    MainLoop(const std::string& title, sf::VideoMode default_mode = sf::VideoMode{sf::Vector2u(1280, 720)});
    ~MainLoop() = default;

    void run(std::unique_ptr<GameState> initial_state);
    void change_state(std::unique_ptr<GameState> new_state);

private:
    void process_events();

private:
    std::string m_window_title;
    sf::RenderWindow m_window;
    bool m_fullscreen = false;
    sf::VideoMode m_prev_mode;

    int m_target_fps = 144;

    sf::Clock m_clock;
    entt::registry m_registry;
    
    std::unique_ptr<GameState> m_current_state = nullptr;
    std::unique_ptr<GameState> m_next_state = nullptr;
};

} // namespace meatengine
