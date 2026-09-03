#pragma once
#include "ResourceLoader.hpp"

#undef max

class SoundPlayer {
private:
    static constexpr size_t POOL_SIZE = 32;
    sf::SoundBuffer dummyBuffer;
    std::vector<sf::Sound> pool;
    std::vector<int> priorities;
    size_t next = 0;

public:
    SoundPlayer() {
        pool.reserve(POOL_SIZE);
        priorities.reserve(POOL_SIZE);
        for (size_t i = 0; i < POOL_SIZE; ++i) {
            pool.emplace_back(dummyBuffer);
            priorities.emplace_back(0);
        }
    }

    void play(sf::SoundBuffer& buffer,
        sf::Vector2f position = {0.f, 0.f},
        float min_distance = 100.f,
        int priority = 0,
        float attenuation = 1.f
    ) {
        int free_slot = -1;
        int lowest_priority_slot = -1;
        int lowest_priority = std::numeric_limits<int>::max();

        for (size_t i = 0; i < POOL_SIZE; ++i) {
            if (pool[i].getStatus() == sf::Sound::Status::Stopped) {
                free_slot = static_cast<int>(i);
                break;
            }
            if (priorities[i] < lowest_priority) {
                lowest_priority = priorities[i];
                lowest_priority_slot = static_cast<int>(i);
            }
        }

        int slot_to_use = -1;

        if (free_slot != -1) {
            slot_to_use = free_slot;
        } else {
            if (priority > lowest_priority) {
                slot_to_use = lowest_priority_slot;
                pool[slot_to_use].stop();
            } else {
                return;
            }
        }

        auto& sound = pool[slot_to_use];
        sound.stop();
        sound.setBuffer(buffer);
        sound.setPosition({position.x, position.y, 0.f});
        sound.setRelativeToListener(false);
        sound.setMinDistance(min_distance);
        sound.setAttenuation(attenuation);
        priorities[slot_to_use] = priority;

        sound.play();
    }


    
    void play(entt::resource<sf::SoundBuffer> buffer,
        sf::Vector2f position = {0.f, 0.f},
        float min_distance = 100.f,
        int priority = 0,
        float attenuation = 1.f
    ) {
        if (buffer) play(*buffer,
            position,
            min_distance,
            priority,
            attenuation
        );
    }
};

extern SoundPlayer soundplayer;