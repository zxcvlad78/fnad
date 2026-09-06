#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

#include <functional>
#include <unordered_set>

struct ChildOf { entt::entity entity; };

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

    static sf::Transform get_global(entt::registry& registry, entt::entity entity) {
        sf::Vector2f pos(0.f, 0.f);
        entt::entity current = entity;
        
        std::vector<entt::entity> chain;
        while (true) {
            chain.push_back(current);
            if (!registry.any_of<ChildOf>(current)) break;
            current = registry.get<ChildOf>(current).entity;
        }
        
        sf::Transform sft;
        for (auto it = chain.rbegin(); it != chain.rend(); ++it) {
            if (registry.all_of<Transform>(*it)) {
                const auto& t = registry.get<Transform>(*it);
                sft.translate(t.position);
                sft.rotate(t.rotation_degrees);
                sft.scale(t.scale);
            }
        }
        
        return sft;
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

struct Velocity {
    float x = 0.0f;
    float y = 0.0f;
    bool normalize = true;
};

