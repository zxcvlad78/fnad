#pragma once

#include <fnafcpp/animatronic/Components.hpp>

namespace AnimatronicSystems {
    void update(entt::registry& registry, float dt);
    void handle_events(entt::registry& registry);
} // namespace AnimatronicSystems