#pragma once
#include <SFML/Graphics.hpp>

struct Night {
private:
    float duration = 60.f * 8.f;
public:
    void set_duration(float new_value) {
        duration = new_value;
        time_left = duration;
    }
    float get_duration() { return duration; }
    float time_left = duration;
};

struct EventGameOver {
    bool is_player_alive = false;
};

struct PowerSource {
    float max_value = 100.f;
    float value = max_value;
};

struct PowerConsumer {
    float value = 1.f; // per second
    bool is_active = false;
};
