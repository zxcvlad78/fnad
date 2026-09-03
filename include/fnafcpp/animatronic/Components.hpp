#pragma once

#include <entt/entt.hpp>
#include <string>
#include <unordered_map>

#include <meatengine/Resources.hpp>

struct Animatronic {
    std::string name = "";
    std::string id = "";
    uint8_t aggression = 1;
};

struct AnimatronicMovement {
    float move_timer = 0.f;
    const float MOVE_INTERVAL = 5.f;
    
    bool is_move_cooldown() { return move_timer < MOVE_INTERVAL; }
};

struct AnimatronicMovePath {
private:
    uint8_t room_idx = 0;
public:
    void set_room_idx(uint8_t val) {
        int rooms_size = rooms.size();
        if (val > rooms_size) room_idx = rooms_size;
        room_idx = val;
    }
    uint8_t get_room_idx() { return room_idx; }
    std::string get_room_id() { return rooms.at(room_idx); }

    void move() {
        if (rooms.empty()) return;
        
        room_idx++;
        if (room_idx >= rooms.size()) {
            room_idx = 0;
        }
    }

    std::unordered_map<uint8_t, std::string> rooms;

    //bool at_office() { return rooms.at(current_room_idx). }
};

struct EventAnimatronicMove {  };