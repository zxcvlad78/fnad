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
            if (a.ai_level == 0) {
                continue;
            }

            uint8_t rint = meatengine::rng::random(uint8_t(0), Animatronic::MAX_AI_LEVEL);
            if (rint <= a.ai_level) {
                amp.move();
                registry.emplace_or_replace<EventAnimatronicMove>(e);
            }
        }
    }
} // namespace AnimatronicSystems