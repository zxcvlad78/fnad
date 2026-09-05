#include <meatengine/MainLoop.hpp>

#include <meatengine/Resources.hpp>
#include <meatengine/ResourceLoader.hpp>
#include <meatengine/console/Console.hpp>

namespace meatengine {

MainLoop::MainLoop(const std::string& title, sf::VideoMode default_mode) 
    : m_prev_mode(default_mode), m_window_title(title) 
{
    m_window.create(m_prev_mode, title);
    m_window.setFramerateLimit(144);

    // потом как нибудь
    entt::resource<meatengine::Font> mainfont = meatengine::ResourceLoader::load<meatengine::Font>("res/fonts/mainfont.ttf");
    if (mainfont.handle()) {
        meatengine::Console::get_instance().init(
            m_window,
            mainfont->res,
            16
        );
    }
    //
}

void MainLoop::change_state(std::unique_ptr<GameState> new_state) {
    m_next_state = std::move(new_state);
}

void MainLoop::process_events() {
    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::F11) {
                m_fullscreen = !m_fullscreen;
                if (m_fullscreen) {
                    m_window.create(sf::VideoMode::getDesktopMode(), m_window_title, sf::State::Fullscreen);
                } else {
                    m_window.create(m_prev_mode, m_window_title, sf::State::Windowed);
                }
                m_window.setFramerateLimit(m_target_fps);
            }
        }

        // потом как нибудь
        meatengine::Console::get_instance().handle_event(*event, m_window);
        //

        if (m_current_state) {
            m_current_state->handle_event(m_window, m_registry, *event);
        }
    }
}

void MainLoop::run(std::unique_ptr<GameState> initial_state) {
    change_state(std::move(initial_state));

    while (m_window.isOpen()) {
        if (m_next_state) {
            if (m_current_state) m_current_state->on_exit(m_window, m_registry);
            m_registry.clear();
            m_current_state = std::move(m_next_state);
            m_current_state->on_enter(m_window, m_registry);
        }

        process_events();

        float dt = m_clock.restart().asSeconds() * dt_scale;

        if (m_current_state) {
            m_current_state->update(m_window, m_registry, dt);
        }

        // потом как нибудь
        meatengine::Console::get_instance().update(m_window, dt);
        //

        m_window.clear(sf::Color::Black);
        
        if (m_current_state) {
            m_current_state->render(m_window, m_registry, dt);
        }

        // потом как нибудь
        meatengine::Console::get_instance().render(m_window);
        //

        m_window.setView(m_window.getDefaultView());
        m_window.display();
    }
}

} // namespace meatengine
