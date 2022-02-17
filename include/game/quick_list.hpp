#pragma once

#include "tinyengine/tinyengine.hpp"

template <typename T>
class QuickList final {
public:
    using condition_func = std::function<bool(const T&)>;
    using destroy_func = std::function<void(const T&)>;

    void Add(const T& elem) {
        datas_.push_back(elem);
    }

    bool Empty() const { return datas_.empty(); }

    void RemoveAll(condition_func findFunc,
                   destroy_func destroyFunc = nullptr) {
        std::size_t idx = 0;
        while (idx < datas_.size()) {
            if (datas_.size() > idx && findFunc(datas_[idx])) {
                std::swap(datas_[idx], datas_[datas_.size() - 1]);
                if (destroyFunc) {
                    destroyFunc(datas_.back());
                }
                datas_.pop_back();
            } else {
                idx ++;
            }
        }
    }

    void Clear(condition_func condition = nullptr, destroy_func destroy = nullptr) {
        if (destroy && condition) {
            RemoveAll(condition, destroy);
        }
        datas_.clear();
    }

    // for debug
    void PrintAll(std::function<void(const T&)> func = nullptr) {
        printf("QuickList: ");
        for (auto& elem : datas_) {
            if (func == nullptr) {
                std::cout << elem << ", ";
            } else {
                func(elem);
            }
        }
        printf("\n");
    }


    size_t Size() const { return datas_.size(); }
    T& Get(size_t idx) { return datas_[idx]; }


    using const_iterator = typename std::vector<T>::const_iterator;

    const_iterator begin() const { return datas_.begin(); }
    const_iterator end() const { return datas_.end(); }

private:
    std::vector<T> datas_;
};
