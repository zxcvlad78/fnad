#pragma once

#include <meatengine/meatengine.hpp>
#include <fnafcpp/animatronic/Components.hpp>

namespace fnafcpp::console_commands {
    inline void init(meatengine::MainLoop& main_loop) {
        meatengine::Console::get_instance().register_command(
            "ai.level",
            [&main_loop](const std::vector<std::string>& args) {
                if (args.size() != 2) return;
                std::string id = args[0];

                try {
                    auto view = main_loop.get_registry().view<Animatronic>();
                    for (auto [e, a] : view.each()) {
                        if (a.id == id || id == "*") {
                            a.ai_level = std::stoi(args[1]);
                            meatengine::Console::get_instance().print_success("ai.level " + a.id + ": " + std::to_string(a.ai_level));
                        }
                    }
                } catch (const std::exception& e) {
                    meatengine::Console::get_instance().print_error(e.what());
                }

            },
            "Set AI level for animatronic",
            "ai.level <string> <int>"
        );
        meatengine::Console::get_instance().register_command(
            "ai.roll_interval",
            [&main_loop](const std::vector<std::string>& args) {
                if (args.size() != 1) return;

                try {
                    AnimatronicMovement::roll_interval = std::stof(args[0]);
                } catch (const std::exception& e) {
                    meatengine::Console::get_instance().print_error(e.what());
                }

            },
            "Set AI roll interval",
            "ai.roll_interval <float>"
        );
    }
}