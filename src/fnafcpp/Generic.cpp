#include <fnafcpp/Generic.hpp>
#include <meatengine/Generic.hpp>
#include <meatengine/sprite/Components.hpp>

#include <algorithm>

namespace fnafcpp {
    namespace GenericSystems {
        void update(entt::registry& reg, sf::RenderWindow& window, float dt) {
            office_panorama(reg, window, dt);
        }

        void office_panorama(entt::registry& reg, sf::RenderWindow& window, float dt) {
            auto view = reg.view<Transform, Sprite, OfficePanorama>();

            sf::Vector2u window_size = window.getSize();
            sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

            const float BASE_SIZE = 300.f;
            float multiplier = window_size.x / 1280.f;
            float active_zone = BASE_SIZE * multiplier;

            
            for (auto [e, t, s, op] : view.each()) {
                float sprite_width = s.sprite.getTextureRect().size.x * t.scale.x;
                if (sprite_width <= window_size.x) continue;
                
                float min_x = window_size.x - sprite_width;
                float max_x = 0.f;

                float move_dir = 0.f;
                if (mouse_position.x < active_zone) {
                    move_dir = 1.f;
                } else if (mouse_position.x > window_size.x - active_zone) {
                    move_dir = -1.f;
                }

                t.position.x += move_dir * op.move_speed * dt;
                t.position.x = std::clamp(t.position.x, min_x, max_x);

                printf(
                    "min_x: %f, pos_x: %f, sprite_width: %f, scale_x: %f\n",
                    min_x, t.position.x, sprite_width, t.scale.x
                );
            }
        }

    }
    
}