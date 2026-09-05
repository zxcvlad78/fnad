#pragma once

#include <meatengine/meatengine.hpp>
#include <fnafcpp/fnafcpp.hpp>


namespace fnafcpp::packed_entity {
    namespace jumpscare {
        inline entt::entity spawn(
            entt::registry& registry,
            const std::string& texture_path,
            const std::string& spritesheet_path
        ) {
            if (texture_path.empty() || spritesheet_path.empty()) return entt::null;

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

            return entity;
        }
    }
}