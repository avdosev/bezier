#include <iostream>

/*
Требуется реализовать функцию проецирования кривой Безье в заданном интервале на плоскость по нормали.
Кривая должна быть построена по заданному набору опорных точек. Плоскость должна быть построена по заданным трём точкам.
Положение искомых точек найти с точностью 10-5
*/

#include <vector>
#include <algorithm>
#include <cmath>
#include "point.h"

using vector_points = std::vector<point>;

point bezier(vector_points points, double t) {
    if (points.size() == 3) {
        return pow((1-t), 2)*points[0] + 2.0*t*(1-t)*points[1] + pow(t, 2)*points[2];
    } else if (points.size() == 2) {
        return (1-t)*points[0]+t*points[1];
    } else {
        /* чет хз */
        return point();
    }
}

int main() {
    // примерный алгоритм работы
    // получаем набор точек у пользователя
    // по точкам создаем набор точек кривой
    // выводим результат
    double step = 0.005;
    vector_points points{
            {7, 2},
            {5, 7},
            {10, 3}
    };
    for (auto t = 0.0; t <= 1.0; t += step) {
        auto p = bezier(points, t);
        std::cout << "[ " << p.x << ", " << p.y << " ], " << std::endl;
    }
    return 0;
}