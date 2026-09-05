#pragma once

#include <meatengine/meatengine.hpp>
#include <fnafcpp/fnafcpp.hpp>
#include <GameUI.hpp>

class FnadGame : public meatengine::GameState {
    sf::Vector2f window_sizef;
    

public:
    void on_enter(sf::RenderWindow& window, entt::registry& registry) override {

        //bg
        {auto entity = registry.create();
            registry.emplace<ZIndex>(entity, -1);
            auto& transform = registry.emplace<Transform>(entity);
            registry.emplace<FullScreenScale>(entity);
            
            auto& sprite = registry.emplace<Sprite>(entity,
                meatengine::ResourceLoader::load<meatengine::Texture>("res/bg.jpg")
            );
        }

        // night
        {auto entity = registry.create();
            auto& night = registry.emplace<Night>(entity);
            night.set_duration(18.f);
        }

        // power sources
        for (short i = 0; i < 5; i++) {
            auto entity = registry.create();
            registry.emplace<PowerSource>(entity);
        }

        // power consumers
        for (short i = 0; i < 6; i++) {
            auto entity = registry.create();
            auto& pc = registry.emplace<PowerConsumer>(entity);
            pc.is_active = true;
        }

        // power fredi
        {auto entity = registry.create();
            auto& animatronic = registry.emplace<Animatronic>(entity); {
                animatronic.name = "Darky";
                animatronic.id = "darky";
            }
            auto& movement = registry.emplace<AnimatronicMovement>(entity);
            auto& move_path = registry.emplace<AnimatronicMovePath>(entity); {
                move_path.rooms.push_back("scene");
                move_path.rooms.push_back("sex");
                move_path.rooms.push_back("piske");
                move_path.rooms.push_back("pe4ko");
                move_path.rooms.push_back("vozle_ofic");
                move_path.rooms.push_back("office");
            }
        }

        {auto entity = registry.create();
            auto& animatronic = registry.emplace<Animatronic>(entity); {
                animatronic.name = "Waper";
                animatronic.id = "waper";
            }
            auto& movement = registry.emplace<AnimatronicMovement>(entity);
            auto& move_path = registry.emplace<AnimatronicMovePath>(entity); {
                move_path.rooms.push_back("box");
                move_path.rooms.push_back("shkaf");
                move_path.rooms.push_back("under_krovat_bed");
                move_path.rooms.push_back("office");
            }
        }

        // {auto entity = registry.create();
        //     auto& timer = registry.emplace<Timer>(entity); {
        //         timer.wait_time = 5.f;
        //         timer.timeout_func = [](entt::registry& reg) {
        //             auto scream_entity = reg.create();
        //             auto& transform = reg.emplace<Transform>(scream_entity);
        //             reg.emplace<FullScreenScale>(scream_entity);

        //             reg.emplace<Sprite>(scream_entity,
        //                 meatengine::ResourceLoader::load<meatengine::Texture>("res/villager.png")
        //             );
        //             auto& sprite_anim = reg.emplace<SpriteAnimation>(scream_entity,
        //                 meatengine::ResourceLoader::load<meatengine::SpriteSheet>("res/villager.json")
        //             ); {
        //                 sprite_anim.play("default");
        //             }

        //             meatengine::SoundPlayer::play(
        //                 meatengine::ResourceLoader::load<meatengine::SoundBuffer>("res/villager.mp3")
        //             );
        //         };
        //     }

        //     timer.start();
        // }
    }

    void handle_event(sf::RenderWindow& window, entt::registry& registry, const sf::Event& event) override {
        
    }

    void update(sf::RenderWindow& window, entt::registry& registry, float dt) override {
        TimerSystems::update(registry, dt);
        SpriteSystems::update(registry, window, dt);
        NightSystems::update(registry, dt);
        AnimatronicSystems::update(registry, dt);
    }
    
    void render(sf::RenderWindow& window, entt::registry& registry, float dt) override {
        CameraSystems::update(registry, window, dt);
        RenderSystems::render(registry, window);
        GameUI::render(registry, window, dt);
    }

    void on_exit(sf::RenderWindow& window, entt::registry& registry) override {}
};
