#pragma once

#include "tinyengine/tinyengine.hpp"

template <typename T>
class QuickList final {
public:
    void Add(const T& elem) {
        datas_.push_back(elem);
    }

    void RemoveAll(std::function<bool(const T&)> func) {
        int idx = 0;
        while (idx < datas_.size()) {
            if (func(datas_[idx]) && datas_.size() > idx) {
                std::swap(datas_[idx], datas_[datas_.size() - 1]);
                datas_.pop_back();
            } else {
                idx ++;
            }
        }
    }
    void Clear() { datas_.clear(); }

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

    using const_iterator = typename std::vector<T>::const_iterator;

    const_iterator begin() const { return datas_.begin(); }
    const_iterator end() const { return datas_.end(); }

private:
    std::vector<T> datas_;
};