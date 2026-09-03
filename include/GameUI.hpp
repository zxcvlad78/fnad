#pragma once
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

namespace GameUI {
    void render(entt::registry& registry, sf::RenderWindow& window, float dt);
    void render_animatronic_pos(entt::registry& registry, sf::RenderWindow& window, float dt);
    void render_time(entt::registry& registry, sf::RenderWindow& window, float dt);
    void render_power_sources(entt::registry& registry, sf::RenderWindow& window, float dt);
    void render_power_consumers(entt::registry& registry, sf::RenderWindow& window, float dt);
}; // namepspace GameUI