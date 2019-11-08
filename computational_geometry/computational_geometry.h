#pragma once

#include <vector>
#include <algorithm>
#include <valarray>
#include <array>

#include "matrix.h"
#include "vec.h"

// с ним у меня почему то вылетает, возможно это не популярный котейнер
// using point_t = std::valarray<double>;
using  point_t = vec<double, 3>;
using vector_points = std::vector<point_t>;

point_t bezier(vector_points points, double t);
vector_points bezier_line(vector_points points, double eps);

struct plane_t {
    using equ_t = std::array<double, 4>;
    equ_t equation;

    plane_t(point_t p1, point_t p2, point_t p3);

    plane_t(equ_t equat) : equation(equat) { };

    point_t normal();
};


point_t projection_on_plane(point_t point, plane_t plane);

vector_points projection_on_plane(vector_points points, plane_t plane);