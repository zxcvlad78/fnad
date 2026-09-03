#pragma once
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

namespace meatengine {

class GameState {
public:
    virtual ~GameState() = default;

    virtual void on_enter(entt::registry& registry) = 0;
    virtual void handle_event(const sf::Event& event, entt::registry& registry) = 0;
    virtual void update(sf::RenderWindow& window, entt::registry& registry, float dt) = 0;
    virtual void render(sf::RenderWindow& window, entt::registry& registry, float dt) = 0;
    virtual void on_exit(entt::registry& registry) = 0;
};

} // namespace meatengine
