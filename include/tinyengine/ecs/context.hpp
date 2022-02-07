_Pragma("once")

#include "tinyengine/pool.hpp"
#include "component.hpp"

class Entity;

class Context final {
public:
    friend class Entity;
    Entity* CreateEntity();

    bool HasEntity(Entity* entity);
    Pool<Entity>::ElemContainer& GetEntities();
    void DestroyEntity(Entity* entity);
    int GetEntityNum() const;

    template <typename T, typename... Args>
    T* CreateComponent(Args... args) {
        ComponentId id = ComponentIdx::Get<T>();
        auto it = gComponentPool.find(id);
        if (it != gComponentPool.end()) {
            return it->second.Create<T>(args...);
        } else {
            gComponentPool[id] = Pool<Component>();
            return gComponentPool[id].Create<T>(args...);
        }
    }

    template <typename T>
    void DestroyComponent(T* elem) {
        DestroyComponentById(elem, ComponentIdx::Get<T>());
    }

    inline void DestroyComponentById(Component* elem, int id) {
        auto it = gComponentPool.find(id);
        if (it != gComponentPool.end()) {
            gComponentPool[id].Destroy(elem);
        }
    }

private:
    Pool<Entity> entities_;

    void onComponentUpdate(Entity*, ComponentId, Component*);
};
