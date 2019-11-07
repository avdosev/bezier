#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <valarray>
#include <array>

#include "matrix.h"

using point_t = std::valarray<double>;
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

vector_points bezier_line(vector_points points, double eps) {
    vector_points res;
    res.reserve(unsigned(1./eps));
    auto step = eps;
    for (auto t = 0.0; t <= 1.0; t += step) {
        res.push_back(bezier(points, t));
    }
    return res;
}

struct plane_t {
    using equ_t = std::array<double, 4>;
    equ_t equation;
    
    plane_t(point_t p1, point_t p2, point_t p3) {
        double mat[3][2] = {
                {p2[0]-p1[0], p3[0]-p1[0]},
                {p2[1]-p1[1], p3[1]-p1[1]},
                {p2[2]-p1[2], p3[2]-p1[2]}
        };
        equation[0] = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0];
        equation[1] = mat[0][0] * mat[2][1] - mat[2][1] * mat[2][0];
        equation[2] = mat[0][0] * mat[1][1] - mat[1][1] * mat[2][0];
        equation[3] = equation[0]*p1[0] + equation[1]*p1[1] + equation[2]*p1[2];
    }

    plane_t(equ_t equat) : equation(equat) {
        std::cout << "puk2";
    };

    point_t normal() {
        auto& equ = this->equation;
        return {equ[0], equ[1], equ[2]};
    }
};


point_t projection_on_plane(point_t point, plane_t plane) {
    // переходим к уравнению двух пересекающихся плоскостей
    // и юзаем метод крамера ( не зря же я написал определитель для матрицы )
    point_t res;
    auto normal = plane.normal();
    // TODO заполнить доконца
    std::array<std::array<double, 4>, 3> equ{
            std::array<double, 4>{normal[1], -normal[0], 0., normal[1]*-point[0] - normal[0]*-point[1]},
            std::array<double, 4>{normal[2], -normal[0], 0., normal[2]*-point[0] - normal[0]*-point[2]},
            std::array<double, 4>{ plane.equation[0], plane.equation[1], plane.equation[2], -plane.equation[3] }
    };

    using matrix_t = matrix<double, 3>;

    matrix_t matr;
    // заполняет всю матрицу
    auto fill_matrix = [&matr, &equ](){
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                matr[i][j] = equ[i][j];
            }
        }
    };
    // заполняет столбец матрицы
    auto fill_column = [&matr, &equ](size_t index){
        for (size_t j = 0; j < 3; j++) {
            matr[index][j] = equ[3][j];
        }
    };

    fill_matrix();
    auto det = matr.determinant();
    for (auto i = 0; i < 3; i++) {
        fill_matrix();
        fill_column(0);
        auto det_by_coordinate = matr.determinant();
        res[i] = det_by_coordinate / det;
    }

    return res;
}

vector_points projection_on_plane(vector_points points, plane_t plane) {
    vector_points res;
    for (auto point : points) {
        res.push_back(projection_on_plane(point, plane));
    }
    return res;
}

int main() {
    std::cout << "puk";
    /*
    Требуется реализовать функцию проецирования кривой Безье в заданном интервале на плоскость по нормали.
    Кривая должна быть построена по заданному набору опорных точек. Плоскость должна быть построена по заданным трём точкам.
    Положение искомых точек найти с точностью 10-5
    */

    // примерный алгоритм работы
    // получаем набор точек у пользователя
    // по точкам создаем набор точек кривой
    // по точкам кривой проецируем
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
        file << "[ " << p[0] << ", " << p[1] << " ]";
        if(t+step < 1.0) {
            file << ",\n";
        } else {
            file << "\n";
        }
    }
    file << "] \n";

    file.close();
    /*plane_t plane(plane_t::equ_t {2,-2,1,-2});
    point_t point{-2.,4., 4.};

    auto res = projection_on_plane(point, plane);
    std::cout << res[0] << " " << res[1] << " " << res[2] << "\n" ;*/

    return 0;
}