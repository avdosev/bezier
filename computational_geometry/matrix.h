//
// Created by avdosev on 06.11.2019.
//

#pragma once

#include <array>
#include <vector>
#include <functional>

template <class T, size_t num>
class matrix {
private:
    template <class _T, size_t _num>
    using array = std::array<_T, _num>;
    using vector = std::vector<T>;

    array<array<T, num>, num> m;
public:
    T determinant() {
        constexpr auto size = num;
        constexpr size_t x = 0, y = 0;

        if (size == 2)
            return m[y][x]*m[y+1][x+1] - m[y+1][x]*m[y][x+1];

        T res = 0;
        for (size_t i = 0; i < size; i++) {
            auto minor_ = this->minor(x, y+i).determinant();
            res += T( bool(i&1) ? -1 : 1) * m[y+i][x] * minor_;
        }

        return res;
    }

    /*
     * разбиение на минор с исключением x и y
     */
    matrix<T, num-1> minor(size_t x, size_t y) {
        matrix<T, num-1> buff;
        size_t b_i = 0;
        for (size_t i = 0; i < num; i++) {
            if (i == y) continue;
            size_t b_j = 0;
            for (size_t j = 0; j < num; j++) {
                if (j == x) continue;
                buff[b_i][b_j] = m[i][j];
                b_j++;
            }
            b_i++;
        }
        return buff;
    }

    array<T, num>& operator[] (size_t index) {
        return m[index];
    }
};

template<class T>
class matrix <T, 1> {
private:
    template <class _T, size_t _num>
    using array = std::array<_T, _num>;

    array<T, 1> m;
public:
    T determinant() {
        // я не уверен что нужно возвращать
        return m[0];
    }

    array<T, 1>& operator[] (size_t index) {
        return m;
    }
};