#include <fnafcpp/animatronic/Systems.hpp>
#include <meatengine/rng.hpp>

namespace AnimatronicSystems {
    void update(entt::registry& registry, float dt) {
        for (auto [e, a, am, amp] : registry.view<
            Animatronic,
            AnimatronicMovement,
            AnimatronicMovePath
            >().each()
        ) {
            if (am.is_move_cooldown()) {
                am.move_timer += dt;
                continue;
            }

            am.move_timer = 0.f;

            uint8_t rint = meatengine::rng::random(uint8_t(0), a.aggression);
            if (rint <= a.aggression) {
                amp.move();
                registry.emplace_or_replace<EventAnimatronicMove>(e);
            }
        }
    }
} // namespace AnimatronicSystems