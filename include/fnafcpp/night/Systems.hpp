#pragma once
#include <entt/entt.hpp>
#include <fnafcpp/night/Components.hpp>

namespace NightSystems {
    void update(entt::registry& registry, float dt);
    void handle_events(entt::registry& registry);
}