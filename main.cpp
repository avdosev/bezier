#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

#include "computational_geometry/computational_geometry.h"

std::ostream& operator << (std::ostream& stream, point_t point) {
    auto& coordinate = point.coordinates;
    stream << coordinate[0] << ", " << coordinate[1] << ", " << coordinate[2];
    return stream;
}

std::istream& operator >> (std::istream& stream, point_t& point) {
    char tmp;
    for (auto& coordinate : point.coordinates) {
        stream >> coordinate;
        stream.get(); // пускай сюда записывается запятая
    }
    return stream;
}

int main(int argc, char** argv) {

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

    if (argc < 2) {
        std::cout << "file not specified" << std::endl;
        std::cout << "bezier.exe [filename]";
        return 0;
    }

    std::string filename = argv[1];

    std::fstream file(filename, std::fstream::in);

    if (!file.is_open()) {
        std::cout << "file not open";
        return 0;
    }

    std::string prop_points_line, plane_points_line;
    std::getline(file, prop_points_line);
    std::getline(file, plane_points_line);

    vector_points prop_points;
    std::istringstream iss(prop_points_line);

    while (!iss.eof()) {
        point_t tmp_point;
        iss >> tmp_point;
        prop_points.push_back(tmp_point);
    }


    vector_points points_for_plane;
    points_for_plane.reserve(3);
    std::istringstream iss2(plane_points_line);
    while (!iss2.eof()) {
        point_t tmp_point;
        iss2 >> tmp_point;
        points_for_plane.push_back(tmp_point);
    }

    std::cout << "what i got:" << std::endl;
    std::copy(prop_points.begin(), prop_points.end(), std::ostream_iterator<point_t>(std::cout, " "));
    std::cout << std::endl;
    std::copy(points_for_plane.begin(), points_for_plane.end(), std::ostream_iterator<point_t>(std::cout, " "));
    std::cout << std::endl;

    // просчитываем безье
    auto bezier_points = bezier_line(prop_points, 0.001);

    // создаем на базе трех точек объект плоскость
    plane_t plane(points_for_plane[0], points_for_plane[1], points_for_plane[2]);

    // проецируем на плоскость
    auto projected_points = projection_on_plane(bezier_points, plane);

    std::cout << "projected points:\n";
    for (auto res : projected_points)
         std::cout << res << "\n" ;

    return 0;
}