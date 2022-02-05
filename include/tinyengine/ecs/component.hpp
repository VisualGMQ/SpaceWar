_Pragma("once")

#include "pch.hpp"
#include "pool.hpp"

using ComponentId = unsigned int;

class Component {
public:
    friend class Pool<Component>;

    virtual ~Component() = default;
    inline bool IsAlive() const { return alive_; }
    virtual void Release() = 0;

private:
    bool alive_;
};

class ComponentIdx final {
public:
    template <typename T>
    static ComponentId Get() {
        static_assert(std::is_base_of_v<Component, T> && !std::is_same_v<Component, T>);
        static ComponentId id = count_ ++;
        return id;
    }

    inline static ComponentId GetCount() { return count_; }

private:
    static ComponentId count_;
};

struct ComponentPool{
};

extern std::unordered_map<ComponentId, Pool<Component>> gComponentPool;
