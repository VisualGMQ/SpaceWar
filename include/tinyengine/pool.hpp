_Pragma("once")

#include "pch.hpp"

/*
 * Memory Pool.
 * To use this pool, your class must have:
 *  * `bool alive_` member
 *  * let Pool be it's friend class
 *  * `void Init(...)` function to init your object
 *  * `void Release()` function to release your object
 */
template <typename T>
class Pool {
public:
    using ElemContainer = std::vector<T*>;

    Pool(size_t capacity = 20) {
        datas_.reserve(capacity);
    }
    ~Pool() {
        for (size_t i = 0; i < datas_.size(); i++)
            delete datas_[i];
        while (!cache_.empty()) {
            delete cache_.top();
            cache_.pop();
        }
    }

    template <typename U = T, typename... Args>
    U* Create(Args... args) {
        static_assert(std::is_base_of_v<T, U>);
        if (GetReuseableNum() > 0) {
            U* elem = (U*)cache_.top();
            elem->Init(args ...);
            elem->alive_ = true;
            cache_.pop();
            datas_.push_back(elem);
            return elem;
        } else {
            U* elem = new U;
            datas_.push_back(elem);
            elem->Init(args ...);
            elem->alive_ = true;
            return (U*)datas_.back();
        }
    }

    void Destroy(T* elem) {
        auto it = std::find(datas_.begin(),
                            datas_.end(),
                            elem);
        if (it != datas_.end()) {
            (*it)->alive_ = false;
            (*it)->Release();
            cache_.push(*it);
            datas_.erase(it);
        }
    }

    std::vector<T*>& GetElems() { return datas_; }

    int GetNum() const { return datas_.size(); }
    int GetReuseableNum() const { return cache_.size(); }

private:
    ElemContainer datas_;
    std::stack<T*> cache_;
};
