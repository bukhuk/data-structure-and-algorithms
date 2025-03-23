#pragma once

template <typename T>
class FenwickTree {
   public:
    FenwickTree() {
    }

    FenwickTree(size_t array_size, T value) :
        array_size_{array_size},
        array_{new T[array_size_]},
        data_{new T[array_size + 1]} {
        std::fill(array_, array_ + array_size_, value);
        Initialize();
    }

   private:
    void Initialize() {
        for (size_t i = 1; i <= array_size_; i++) {
            *std::next(data_, i) += *std::next(array_, i);
            if (i + (i & -1) <= array_size_) {
                *std::next(data_, i + (i & -1)) += *std::next(array_, i);
            }
        }
    }

    T* array_;
    T* data_;
    size_t array_size_;
};