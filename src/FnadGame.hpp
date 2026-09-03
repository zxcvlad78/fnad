#include <meatengine/meatengine.hpp>
#include <fnafcpp/fnafcpp.hpp>
#include <GameUI.hpp>

class FnadGameState : public meatengine::GameState {
    sf::Vector2f window_sizef;

public:
    void on_enter(entt::registry& registry) override {
        //bg
        {auto entity = registry.create();
            registry.emplace<ZIndex>(entity, -1);
            auto& transform = registry.emplace<Transform>(entity);
            registry.emplace<FullScreenScale>(entity);
            
            auto& sprite = registry.emplace<Sprite>(entity,
                resourceloader.load<sf::Texture, sf::TextureLoader>("res/bg.jpg")
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
            }
            auto& movement = registry.emplace<AnimatronicMovement>(entity);
            auto& move_path = registry.emplace<AnimatronicMovePath>(entity); {
                move_path.rooms.emplace(0, "scene");
                move_path.rooms.emplace(1, "sex");
                move_path.rooms.emplace(2, "piske");
                move_path.rooms.emplace(3, "pe4ko");
                move_path.rooms.emplace(4, "vozle_ofic");
                move_path.rooms.emplace(5, "ofic");
            }
        }

        {auto entity = registry.create();
            auto& animatronic = registry.emplace<Animatronic>(entity); {
                animatronic.name = "Waper";
            }
            auto& movement = registry.emplace<AnimatronicMovement>(entity);
            auto& move_path = registry.emplace<AnimatronicMovePath>(entity); {
                move_path.rooms.emplace(0, "box");
                move_path.rooms.emplace(1, "shkaf");
                move_path.rooms.emplace(2, "under_krovat_bed");
                move_path.rooms.emplace(2, "ofic");
            }
        }

        {auto entity = registry.create();
            auto& timer = registry.emplace<Timer>(entity); {
                timer.wait_time = 5.f;
                timer.timeout_func = [](entt::registry& reg) {
                    auto scream_entity = reg.create();
                    auto& transform = reg.emplace<Transform>(scream_entity);
                    reg.emplace<FullScreenScale>(scream_entity);

                    reg.emplace<Sprite>(scream_entity,
                        resourceloader.load<sf::Texture, sf::TextureLoader>("res/villager.png")
                    );
                    auto& sprite_anim = reg.emplace<SpriteAnimation>(scream_entity,
                        resourceloader.load<Spritesheet::Resource, Spritesheet::Loader>("res/villager.json")
                    ); { sprite_anim.play("default"); }

                    soundplayer.play(
                        resourceloader.load<sf::SoundBuffer, sf::SoundBufferLoader>("res/villager.mp3")
                    );
                };
            }

            timer.start();
        }
    }

    void handle_event(const sf::Event& event, entt::registry& registry) override {
        
    }

    void update(sf::RenderWindow& window, entt::registry& registry, float dt) override {
        SpriteSystems::update(registry, window, dt);
        TimerSystems::update(registry, dt);
        NightSystems::update(registry, dt);
        AnimatronicSystems::update(registry, dt);
    }
    
    void render(sf::RenderWindow& window, entt::registry& registry, float dt) override {
        CameraSystems::update(registry, window, dt);
        RenderSystems::render(registry, window);
        GameUI::render(registry, window, dt);
    }

    void on_exit(entt::registry& registry) override {}
};
