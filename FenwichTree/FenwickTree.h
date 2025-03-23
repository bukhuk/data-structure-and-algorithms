#pragma once

#include <vector>

template <typename T>
class FenwickTree {
   public:
    FenwickTree() : array_{nullptr}, data_{nullptr}, array_size_{0} {
    }

    FenwickTree(const size_t& array_size, const T& value) :
        array_size_{array_size},
        array_{new T[array_size_ + 1]},
        data_{new T[array_size_ + 1]} {
        std::fill(array_ + 1, array_ + array_size_ + 1, value);
        Initialize();
    }

    FenwickTree(const std::vector<T>& array) :
        array_size_{array.size()},
        array_{new T[array_size_ + 1]},
        data_{new T[array_size_ + 1]} {
        for (size_t i = 1; i <= array_size_; i++) {
            *std::next(array_, i) = array[i - 1];
        }
        Initialize();
    }

    T GetSegment(const size_t left_border, const size_t right_border) {
        return GetPrefix(right_border + 1) - GetPrefix(left_border);
    }

    void Update(const size_t position, const T value) {
        for (size_t vertex = position; vertex <= array_size_; vertex += vertex & -vertex) {
            *std::next(data_, vertex) += value;
        }
    }

   private:
    void Initialize() {
        for (size_t i = 1; i <= array_size_; i++) {
            *std::next(data_, i) += *std::next(array_, i);
            if (i + (i & -i) <= array_size_) {
                *std::next(data_, i + (i & -i)) += *std::next(data_, i);
            }
        }
    }

    T GetPrefix(const size_t& border) {
        T result = 0;
        for (size_t vertex = border; vertex > 0; vertex -= vertex & -vertex) {
            result += *std::next(data_, vertex);
        }
        return result;
    }

    T* array_;
    T* data_;
    size_t array_size_;
};