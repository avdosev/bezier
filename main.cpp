#include <fstream>
#include <iostream>

/*
Требуется реализовать функцию проецирования кривой Безье в заданном интервале на плоскость по нормали.
Кривая должна быть построена по заданному набору опорных точек. Плоскость должна быть построена по заданным трём точкам.
Положение искомых точек найти с точностью 10-5
*/

#include <vector>
#include <algorithm>
#include "point.h"

using point_t = vec<double, 3>;
using vector_points = std::vector<point_t>;

point_t bezier(vector_points points, double t) {
    auto bezier2 = [](point_t first, point_t second, double t){
        return (1-t)*first+t*second;
    };
    auto bezier3 = [](point_t first, point_t second, point_t third, double t){
        return pow((1-t), 2)*first + 2.0*t*(1-t)*second + pow(t, 2)*third;
    };

    while(points.size() > 3) {
        for (vector_points::size_type i = 0; i < points.size()-1; i++) {
            points[i] = bezier2(points[i], points[i+1], t);
        }
        points.pop_back();
    }

    if (points.size() == 3) {
        return bezier3(points[0], points[1], points[2], t);
    } else if (points.size() == 2) {
        return bezier2(points[0], points[1], t);
    } else {
        return points.back();
    }
}

struct plane_t {
    point_t p1, p2, p3;
    std::array<double, 4> equation() {
        std::array<double, 4> res;
        double matrix[3][2] = {
                {p2[0]-p1[0], p3[0]-p1[0]},
                {p2[1]-p1[1], p3[1]-p1[1]},
                {p2[2]-p1[2], p3[2]-p1[2]}
        };
        res[0] = matrix[1][0]*matrix[2][1] - matrix[1][1]*matrix[2][0];
        res[1] = matrix[0][0]*matrix[2][1] - matrix[2][1]*matrix[2][0];
        res[2] = matrix[0][0]*matrix[1][1] - matrix[1][1]*matrix[2][0];
        res[3] = res[0]*p1[0] + res[1]*p1[1] + res[2]*p1[2];
        return res;
    }

    point_t normal() {
        auto equ = this->equation();
        return {equ[0], equ[1], equ[2]};
    }
};


point_t projection_on_plane(point_t point, plane_t plane) {

}

vector_points projection_on_plane(vector_points points, plane_t plane) {
    vector_points res;
    for (auto point : points) {
        res.push_back(projection_on_plane(point, plane));
    }
    return res;
}

int main() {
    // примерный алгоритм работы
    // получаем набор точек у пользователя
    // по точкам создаем набор точек кривой
    // выводим результат
    double step = 0.001;
    vector_points points{
            {7., 2.},
            {5., 7.},
            {10., 3.},
            {12., 6.},
            {4., 3.},
            {15., 7.},
            {3., 4.}
    };

    std::ofstream file("../bezier2d.json");

    if (!file.is_open()) {
        std::cout << "error" << std::endl;
    }

    file << "[ \n";
    // пока шаг не очень маленький можно так
    for (auto t = 0.0; t <= 1.0; t += step) {
        auto p = bezier(points, t);
        file << "[ " << p.coordinates[0] << ", " << p.coordinates[1] << " ]";
        if(t+step < 1.0) {
            file << ",\n";
        } else {
            file << "\n";
        }
    }
    file << "] \n";

    file.close();

    return 0;
}