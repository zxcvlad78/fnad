#pragma once

#include <meatengine/meatengine.hpp>
#include <fnafcpp/fnafcpp.hpp>


namespace fnafcpp::packed_entity {
    namespace jumpscare {
        inline entt::entity spawn(
            entt::registry& registry,
            const std::string& audio_path,
            const std::string& texture_path,
            const std::string& spritesheet_path
        ) {
            if (texture_path.empty() || spritesheet_path.empty()) return entt::null;

            meatengine::SoundPlayer::play(
                meatengine::ResourceLoader::load<meatengine::SoundBuffer>(audio_path)
            );

            auto entity = registry.create();
            registry.emplace<Transform>(entity);
            registry.emplace<FullScreenScale>(entity);

            auto& sprite = registry.emplace<Sprite>(entity,
                meatengine::ResourceLoader::load<meatengine::Texture>(texture_path)
            );
            auto& sprite_animation = registry.emplace<SpriteAnimation>(entity,
                meatengine::ResourceLoader::load<meatengine::SpriteSheet>(spritesheet_path)
            ); {
                sprite_animation.play("default");
            }
            auto& timer = registry.emplace<Timer>(entity); {
                timer.wait_time = 2.f;
                timer.timeout_func = [entity](entt::registry& reg) {
                    if (reg.valid(entity)) {
                        reg.destroy(entity);
                    }
                };

                timer.start();
            }

            return entity;
        }
    }
}