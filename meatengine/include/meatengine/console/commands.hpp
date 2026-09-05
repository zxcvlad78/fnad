#pragma once

#include <entt/entt.hpp>
#include <SFML/Audio.hpp>
#include <meatengine/meatengine.hpp>


namespace meatengine::console_commands {
    inline void init(sf::RenderWindow& window) {
        Console::get_instance().register_command(
            "cfg.save",
            [](const std::vector<std::string>& args) {
                Console::get_instance().config_file->save();
            },
            "Save cfg file",
            "cfg.save"
        );
        Console::get_instance().register_command(
            "fps_max",
            [&window](const std::vector<std::string>& args) {
                if (!args.empty()) {
                    try {
                        int fps = std::stoi(args[0]);
                        window.setFramerateLimit(fps);
                    } catch (const std::exception& e) {
                        Console::get_instance().print_error(e.what());
                    }
                }
            },
            "Set target framerate",
            "fps_max <int>"
        );
        Console::get_instance().register_command(
            "volume",
            [&window](const std::vector<std::string>& args) {
                if (!args.empty()) {
                    try {
                        //float vol = std::stoi(args[0]);
                        sf::Listener::setGlobalVolume(std::stoi(args[0]));
                    } catch (const std::exception& e) {
                        Console::get_instance().print_error(e.what());
                    }
                }
            },
            "Set audio volume (0.0-100.0)",
            "volume <float>"
        );
        Console::get_instance().register_command(
            "speed",
            [](const std::vector<std::string>& args) {
                if (!args.empty()) {
                    try {
                        float val = std::stof(args[0]);
                        if (val >= 0.f) {
                            meatengine::MainLoop::dt_scale = val;
                            Console::get_instance().print_success("Speed scale set to: " + std::to_string(val));
                        } else {
                            Console::get_instance().print_error("Speed scale must be positive");
                        }
                    } catch (const std::exception& e) {
                        Console::get_instance().print_error(e.what());
                    }
                } else {
                    Console::get_instance().print_success("Current speed scale: " + std::to_string(meatengine::MainLoop::dt_scale));
                }
            },
            "Set time speed multiplier",
            "speed <float>"
        );

        // Test
        // for (uint8_t i = 0; i < 25; i ++) {
        //     std::string str_i = std::to_string(i);
        //     Console::get_instance().register_command(
        //         "sas" + str_i,
        //         [](const std::vector<std::string>& args) { },
        //         "pro100 sas nomer " + str_i,
        //         "nikak))"
        //     );
        // }
    }
}