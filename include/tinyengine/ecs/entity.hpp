#pragma once

#include "tinyengine/pch.hpp"
#include "tinyengine/pool.hpp"
#include "component.hpp"
#include "context.hpp"

class Entity final {
public:
    friend class Pool<Entity>;

    template <typename T, typename... Args>
    void Add(Args... args) {
        if (!alive_) {
            std::cout << "Entity::Add(): entity is die, can't add component." << std::endl;
        } else {
            T* comp = context_->CreateComponent<T>(args...);
            components_[ComponentIdx::Get<T>()] = comp;
        }
    }

    inline void Init(Context* context) {
        context_ = context;
    }
    inline void Release() {
        components_.clear();
    }

    template <typename T>
    const T* Get() const {
        if constexpr (!std::is_base_of_v<Component, T>) {
            std::cout << "Entity::Get() const: the type T is not inherit from Component" << std::endl;
            return nullptr;
        } else {
            return (T*)Get(ComponentIdx::Get<T>());
        }
    }

    Component* Get(ComponentId id) const {
        if (!alive_) {
            std::cout << "Entity::Get(id) const: entity is die, can't get anything from it." << std::endl;
            return nullptr;
        }
        auto it = components_.find(id);
        if (it == components_.end()) {
            return nullptr;
        } else {
            return it->second;
        }
    }

    template <typename T>
    T* Use() {
        if (!alive_) {
            std::cout << "Entity::Use() const: entity is die, can't get anything from it." << std::endl;
            return nullptr;
        }
        auto it = components_.find(ComponentIdx::Get<T>());
        if (it == components_.end()) {
            return nullptr;
        } else {
            return (T*)it->second;
        }
    }

    template <typename T, typename... Args>
    void Replace(Args... args) {
        if (!alive_) {
            std::cout << "Entity::Replace() const: entity is die, can't replace component." << std::endl;
        } else {
            auto it = components_.find(ComponentIdx::Get<T>());
            if (it != components_.end()) {
                T* c = (T*)it->second;
                c->Init(args...);
            } else {
                Add<T>(args...);
            }
        }
    }

    template <typename T>
    void Remove() {
        Remove(ComponentIdx::Get<T>());
    }
    
    inline void Remove(ComponentId id) {
        if (!alive_) {
            std::cout << "Entity::Remove() const: entity is die, can't remove anything from it." << std::endl;
        } else {
            auto it = components_.find(id);
            if (it != components_.end()) {
                context_->DestroyComponentById(it->second, id);
                components_.erase(it);
            }
        }
    }

    template <typename ... Types>
    bool Has() const {
        if (!alive_) {
            std::cout << "Entity::Has() const: entity is die, can't query." << std::endl;
            return false;
        }
        return hasIter<Types ...>();
    }

    inline bool Has(ComponentId id) const {
        return components_.find(id) != components_.end();
    }

    inline void Reset() {
        for (ComponentId i = 0; i < ComponentIdx::GetCount(); i++) {
            auto it = components_.find(i);
            if (it != components_.end()) {
                components_.erase(it);
            }
        }
    }

    inline bool IsAlive() const { return alive_; }

private:
    std::unordered_map<ComponentId, Component*> components_;
    bool alive_;
    Context* context_ = nullptr;

    template <typename T, typename ... Types>
    bool hasIter() const {
        if constexpr (sizeof...(Types) == 0) {
            return Get<T>();
        } else {
            return Get<T>() && hasIter<Types ...>();
        }
    }
};
