#include <meatengine/MainLoop.hpp>

namespace meatengine {

MainLoop::MainLoop(const std::string& title, sf::VideoMode default_mode) 
    : m_prev_mode(default_mode) 
{
    m_window.create(m_prev_mode, title);
    m_window.setFramerateLimit(144);
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
                    m_window.create(sf::VideoMode::getDesktopMode(), "Game", sf::State::Fullscreen);
                } else {
                    m_window.create(m_prev_mode, "Game", sf::State::Windowed);
                }
                m_window.setFramerateLimit(m_target_fps);
            }
        }

        if (m_current_state) {
            m_current_state->handle_event(*event, m_registry);
        }
    }
}

void MainLoop::run(std::unique_ptr<GameState> initial_state) {
    change_state(std::move(initial_state));

    while (m_window.isOpen()) {
        if (m_next_state) {
            if (m_current_state) m_current_state->on_exit(m_registry);
            m_registry.clear();
            m_current_state = std::move(m_next_state);
            m_current_state->on_enter(m_registry);
        }

        process_events();

        float dt = m_clock.restart().asSeconds();

        if (m_current_state) {
            m_current_state->update(m_window, m_registry, dt);
        }

        m_window.clear(sf::Color::Black);
        
        if (m_current_state) {
            m_current_state->render(m_window, m_registry, dt);
        }

        m_window.setView(m_window.getDefaultView());
        m_window.display();
    }
}

} // namespace meatengine
