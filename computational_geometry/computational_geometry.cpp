//
// Created by avdosev on 08.11.2019.
//

#include "computational_geometry.h"

plane_t::plane_t(point_t p1, point_t p2, point_t p3)  {
    // вектора точек
    point_t vecM1M2, vecM1M3;
    vecM1M2 = p2-p1;
    vecM1M3 = p3-p1;

    equation[0] = vecM1M2[1] * vecM1M3[2] - vecM1M2[2] * vecM1M3[1];
    equation[1] = -vecM1M2[0] * vecM1M3[2] + vecM1M2[2] * vecM1M3[0];
    equation[2] = vecM1M2[0] * vecM1M3[1] - vecM1M2[1] * vecM1M3[0];
    equation[3] = -equation[0]*p1[0] + equation[1]*p1[1] - equation[2]*p1[2];
}

point_t plane_t::normal() {
    auto& equ = this->equation;
    return {equ[0], equ[1], equ[2]};
}

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

point_t projection_on_plane(point_t point, plane_t plane) {
    // переходим к уравнению двух пересекающихся плоскостей
    // и юзаем метод крамера ( не зря же я написал определитель для матрицы )
    // окозалось что зря, использовать метод пересекающихся плоскостей окозалось нецелесообразно при плоскости паралельной оси ординат
    auto normal = plane.normal();

    double t = -((point*normal).sum()+plane.equation.back()) / ((normal*normal).sum());
    point_t res = normal * t + point;

    return res;
}

vector_points projection_on_plane(vector_points points, plane_t plane) {
    vector_points res;
    for (auto point : points) {
        res.push_back(projection_on_plane(point, plane));
    }
    return res;
}