#include <fstream>
#include <iostream>

#include "computational_geometry/computational_geometry.h"

std::ostream& operator << (std::ostream& stream, point_t point) {
    auto& coordinate = point.coordinates;
    stream << coordinate[0] << " " << coordinate[1] << " " << coordinate[2];
    return stream;
}

std::istream& operator >> (std::istream& stream, point_t& point) {
    for (auto& coordinate : point.coordinates) {
        stream >> coordinate;
    }
    return stream;
}

int main() {

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
    size_t count_prop_points;

    std::cin >> count_prop_points;

    vector_points prop_points;

    for (size_t i = 0; i < count_prop_points; i++) {
        point_t tmp_point;
        std::cin >> tmp_point;
        prop_points.push_back(tmp_point);
    }


    point_t points_for_plane[3];
    for (int i = 0; i < 3; i++) {
        for (auto& coordinate : points_for_plane[i].coordinates) {
            std::cin >> coordinate;
        }
    }

    // просчитываем безье
    auto bezier_points = bezier_line(prop_points, 0.0001);

    // создаем на базе трех точек объект плоскость
    plane_t plane(points_for_plane[0], points_for_plane[1], points_for_plane[2]);

    // проецируем на плоскость
    auto projected_points = projection_on_plane(bezier_points, plane);

    for (auto res : projected_points)
        std::cout << res << "\n" ;

    return 0;
}