#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

#include <functional>
#include <unordered_set>

struct Transform {
    sf::Vector2f position;
    sf::Angle rotation_degrees;
    sf::Vector2f scale = {1.f, 1.f};

    Transform& operator=(const Transform& t) {
        if (this != &t) {
            position = t.position;
            rotation_degrees = t.rotation_degrees;
            scale = t.scale;
        }
        return *this;
    }

    Transform& operator=(const Transform* t) {
        if (t != nullptr && this != t) {
            position = t->position;
            rotation_degrees = t->rotation_degrees;
            scale = t->scale;
        }
        return *this;
    }
};

struct Offset {
    sf::Vector2f position;

    void center(sf::Vector2f rect_size) {
        position = {
            -static_cast<float>(rect_size.x) / 2.f,
            -static_cast<float>(rect_size.y) / 2.f
        };
    }
};

struct ChildOf { entt::entity entity; };

struct Velocity {
    float x = 0.0f;
    float y = 0.0f;
    bool normalize = true;
};

