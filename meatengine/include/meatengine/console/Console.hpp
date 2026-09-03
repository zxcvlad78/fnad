#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <unordered_map>
#include <deque>
#include <algorithm>
#include <meatengine/config_file/ConfigFile.hpp>

namespace meatengine {
    struct TextSelection {
        int start;
        int end;

        void reset() {
            start = 0; end = 0; 
        }
        bool is_active() {
            return start != end;
        }
        int get_start() const { return (std::min)(start, end); }
        int get_end()   const { return (std::max)(start, end); }
    };

    class Console {
    public:
        struct Command {
            std::string name;
            std::function<void(const std::vector<std::string>&)> handler;
            std::string description;
            std::string usage;
        };

        TextSelection text_selection;
        ConfigFile* config_file = new ConfigFile("console.cfg");
        void load_cfg(sf::RenderWindow& window);

    private:
        bool visible = false;
        
        sf::RectangleShape background_rect;
        sf::RectangleShape input_rect;
        sf::RectangleShape head_rect;
        sf::RectangleShape scrollbar_track;
        sf::RectangleShape scrollbar_thumb;
        sf::RectangleShape cursor_rect;
        sf::RectangleShape suggestion_rect;
        sf::RectangleShape selection_rect;
        
        std::unique_ptr<sf::Text> input_rect_text;
        std::unique_ptr<sf::Text> output_text;
        std::unique_ptr<sf::Text> head_title;
        std::unique_ptr<sf::Text> suggestion_text;
        
        std::string input_string;
        std::string total_string;
        std::deque<std::string> command_history;
        int history_index = -1;
        size_t max_history = 50;
        
        float scroll_offset = 0.f;
        float max_scroll = 0.f;
        float scroll_speed = 20.f;
        
        size_t cursor_position = 0;
        float cursor_blink_time = 0.f;
        bool cursor_visible = true;
        
        std::unordered_map<std::string, Command> commands;
        
        struct ConsoleMessage {
            std::string text;
            sf::Color color;
        };

        std::deque<ConsoleMessage> messages;
        size_t max_messages = 100;
        
        sf::Font* font_ptr = nullptr;
        uint16_t char_size = 14;

        float console_width = 640.f;
        float console_height = 300.f;
        
        float input_padding = 10.f;

        float theme_outline_thickness = .1f;
        sf::Color theme_outline_color = sf::Color(30, 30, 40);
        sf::Color foreground_color = sf::Color(25, 25, 25, 255);
        sf::Color background_color = sf::Color(15, 15, 15, 240);
        sf::Color selection_color = sf::Color(255, 15, 15, 127);


        float previous_max_scroll = 0.f;
        bool was_at_bottom = false;  
    public:
        static Console& get_instance();
        
        void init(sf::RenderWindow& window, sf::Font& f, uint16_t character_size = 14);
        void update(sf::RenderWindow& window, float dt);
        void render(sf::RenderWindow& window);
        void handle_event(const sf::Event& event, sf::RenderWindow& window);
        
        bool save_config(const std::string& path);
        bool load_config(const std::string& path);

        void show();
        void hide();
        void toggle();
        bool is_visible() const { return visible; }
        
        void clear_selection();
        void remove_selection();
        void select_all();

        void print(const std::string& text, sf::Color color = sf::Color::White);
        void print_error(const std::string& text);
        void print_warning(const std::string& text);
        void print_success(const std::string& text);
        
        void register_command(const std::string& name,
                            std::function<void(const std::vector<std::string>&)> handler,
                            const std::string& description,
                            const std::string& usage
        );
        
        void unregister_command(const std::string& name);
        void execute_command(const std::string& command_line);
        
        std::vector<std::string> get_suggestions(const std::string& prefix);
        void autocomplete();

    private:
        Console() = default;
        
        void update_scrollbar(sf::RenderWindow& window);
        void update_cursor(float dt);
        void clamp_scroll();
        void add_to_history(const std::string& command);
        
        void register_default_commands();

    };

} // namespace meatengine