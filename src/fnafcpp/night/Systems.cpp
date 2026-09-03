#include <fnafcpp/night/Systems.hpp>
#include <algorithm>

namespace NightSystems {
    void update(entt::registry& registry, float dt) {
        auto night_view = registry.view<Night>();
        auto power_sources_view = registry.view<PowerSource>();
        auto power_consumers_view = registry.view<PowerConsumer>();

        for (auto [e, n] : night_view.each()) { // night
            if (n.time_left > 0.f) {
                n.time_left -= dt;
            } else {
                n.time_left = 0.f;
                registry.emplace_or_replace<EventGameOver>(e);
                continue;
            }
        }

        float power_consumed = 0.f;
        for (auto [e, pc] : power_consumers_view.each()) { // power consumers
            if (!pc.is_active) continue;
            power_consumed += pc.value;
        }
        power_consumed *= dt;


        for (auto [e, ps] : power_sources_view.each()) { // power sources
            if (power_consumed <= 0.f) break;
            if (ps.value <= 0.f) continue;

            float take = std::min(power_consumed, ps.value);
            ps.value -= take;
            power_consumed -= take;
        }
        
        handle_events(registry);
    }

    void handle_events(entt::registry& registry) {
        for (auto [e, event] : registry.view<EventGameOver>().each()) { // 
            if (event.is_player_alive) {
                printf("Pobeda!\n");
            }
            registry.remove<EventGameOver>(e);
        }
    }
} // namespace NightSystems
