#include <meatengine/render/Systems.hpp>
#include <meatengine/sprite/Systems.hpp>

namespace RenderSystems {
    void render(entt::registry& registry, sf::RenderWindow& window) {
        if (!enabled) return;

        SpriteSystems::render(registry, window);

    }
}