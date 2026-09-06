#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

namespace fnafcpp {
    namespace GenericSystems {
        void update(entt::registry& reg, sf::RenderWindow& window, float dt);

        void office_panorama(entt::registry& reg, sf::RenderWindow& window, float dt);

    }
    
    struct OfficePanorama { 
        float move_speed = 750.f;
    };
}