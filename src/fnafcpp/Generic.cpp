#include <fnafcpp/Generic.hpp>
#include <meatengine/Generic.hpp>
#include <meatengine/sprite/Components.hpp>

#include <algorithm>
#include <corecrt_math_defines.h>

namespace fnafcpp {
    namespace GenericSystems {
        void update(entt::registry& reg, sf::RenderWindow& window, float dt) {
            office_panorama(reg, window, dt);
        }

        void office_panorama(entt::registry& reg, sf::RenderWindow& window, float dt) {
            auto view = reg.view<Transform, Sprite, OfficePanorama>();

            sf::Vector2u window_size = window.getSize();
            sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

            const float BASE_SIZE = 450.f;
            float multiplier = window_size.x / 1280.f;
            float active_zone = BASE_SIZE * multiplier;
            float window_center = window_size.x / 2.f;

            float normalized = std::abs(mouse_position.x - window_center) / window_center;
            
            float mouse_speed_multiplier = std::pow(normalized, 3.4f); // pow
            //float mouse_speed_multiplier = std::sin((M_PI / 2.0f) * normalized); // sin
 
            float move_dir = 0.f;
            if (mouse_position.x < active_zone) {
                move_dir = 1.f;
            } else if (mouse_position.x > window_size.x - active_zone) {
                move_dir = -1.f;
            }
            
            for (auto [e, t, s, op] : view.each()) {
                float sprite_width = s.sprite.getTextureRect().size.x * t.scale.x;
                if (sprite_width <= window_size.x) continue;
                
                float min_x = window_size.x - sprite_width;
                float max_x = 0.f;

                t.position.x += move_dir * op.move_speed * mouse_speed_multiplier * dt;
                t.position.x = std::clamp(t.position.x, min_x, max_x);
            }
        }

    }
    
}