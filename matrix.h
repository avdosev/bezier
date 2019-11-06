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
        // https://ru.wikipedia.org/wiki/%D0%9A%D0%BE%D0%BD%D0%B4%D0%B5%D0%BD%D1%81%D0%B0%D1%86%D0%B8%D1%8F_%D0%94%D0%BE%D0%B4%D0%B6%D1%81%D0%BE%D0%BD%D0%B0
        std::function<T(size_t, size_t, size_t)> det = [this, det](size_t x, size_t y, size_t size){
            if (size == 1)
                return m[y][x];

            if (size == 2)
                return m[y][x]*m[y+1][x+1] - m[y+1][x]*m[y][x+1];

            matrix<T, 2> buff;
            for (size_t i = 0; i < 2; i++) {
                for (size_t j = 0; j < 2; j++) {
                    buff.m = det(y+i, x+j, size-1);
                }
            }

            return buff.determinant();
        };
        return det(0,0, num);
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
                buff.m[b_i][b_j];
                b_j++;
            }
            b_i++;
        }
        return buff;
    }
};