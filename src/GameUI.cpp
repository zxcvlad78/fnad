#include <GameUI.hpp>

#include <meatengine/ResourceLoader.hpp>

#include <fnafcpp/night/Components.hpp>
#include <fnafcpp/animatronic/Components.hpp>

namespace GameUI {
    sf::Font font = meatengine::ResourceLoader::load<meatengine::Font>("res/fonts/mainfont.ttf")->res;

    void render(entt::registry& registry, sf::RenderWindow& window, float dt) {
        render_power_sources(registry, window, dt);
        render_power_consumers(registry, window, dt);
        render_animatronic_pos(registry, window, dt);
        render_time(registry, window, dt);
    }

    void render_animatronic_pos(entt::registry& registry, sf::RenderWindow& window, float dt) {
        static sf::Text text(font);
        text.setPosition({255.f, 5.f});
        text.setString("Animatronics");
        window.draw(text); 

        sf::Vector2f text_pos = text.getPosition();
        uint16_t text_csize = text.getCharacterSize();

        int txt_count = 0;

        for (auto [e, a, amp] : registry.view<Animatronic, AnimatronicMovePath>().each()) {
            sf::Text a_text(font);
            a_text.setString(
                a.name + ": " + std::to_string(amp.get_room_idx() + 1) + "/" + std::to_string(amp.rooms.size())
                + " (" + amp.get_room_id() + ")"
            );

            a_text.setPosition({
                text_pos.x,
                text_pos.y + text_csize + 5.f + (text_csize + 5.f) * txt_count
            });
            
            txt_count++;
            window.draw(a_text);
        }
    }

    void render_time(entt::registry& registry, sf::RenderWindow& window, float dt) {
        static sf::Text text(font);
        uint16_t text_csize = 12;
        text.setFillColor({200, 200, 200});
        text.setCharacterSize(text_csize);
        
        sf::Vector2f window_sizef = static_cast<sf::Vector2f>(window.getSize());

        auto e = registry.view<Night>().front();
        if (registry.valid(e)) {
            auto& night = registry.get<Night>(e);
            text.setString("Time Left: " + std::to_string(night.time_left));
        }

        text.setPosition({5.f, window_sizef.y - (text_csize + 5.f)});
        window.draw(text); 
    }

    void render_power_sources(entt::registry& registry, sf::RenderWindow& window, float dt) {
        //static sf::RectangleShape bg;
        //bg.setPosition({15.f, 15.f});

        static sf::Text text(font);
        text.setPosition({5.f, 5.f});
        text.setString("Power Sources");
        window.draw(text); 

        sf::Vector2f text_pos = text.getPosition();
        uint16_t text_csize = text.getCharacterSize();

        static sf::Vector2f ps_bg_base_size = {100.f, 25.f};

        int ps_count = 0;
        float total_size_y = 0.f;

        for (auto [e, ps] : registry.view<PowerSource>().each()) {
            sf::RectangleShape ps_bg;
            ps_bg.setFillColor(sf::Color(25, 25, 25));
            ps_bg.setSize(ps_bg_base_size);
            ps_bg.setPosition({
                5.f,
                text_pos.y + text_csize + 5.f + (ps_bg_base_size.y + 5.f) * ps_count
            });

            sf::RectangleShape ps_fg;
            ps_fg.setFillColor(sf::Color(225, 225, 225));
            ps_fg.setPosition(ps_bg.getPosition());
            
            sf::Vector2f ps_bg_size = ps_bg.getSize();
            float ratio = ps.max_value > 0.0f ? (ps.value / ps.max_value) : 0.0f;
            float width = ps_bg_size.x * ratio;
            ps_fg.setSize({width, ps_bg_size.y});

            window.draw(ps_bg);
            window.draw(ps_fg);

            ps_count++;
        }

    }

    void render_power_consumers(entt::registry& registry, sf::RenderWindow& window, float dt) {

    }
}; // namespace GameUI