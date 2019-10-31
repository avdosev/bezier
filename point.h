#pragma  once

#include <cmath>
#include <array>

template <class T, size_t size>
class vec {
public:
    using coord_t = std::array<T, size>;
    coord_t coordinates;

    vec() : coordinates() {}
    vec(coord_t arr) : coordinates(arr) {}
    vec(T s) {
        coordinates.fill(s);
    }
    vec(const vec& v) : coordinates(v.coordinates) {}

    // нужно для инициализации будто это структура
    template<typename ...E>
    vec(E... list) : coordinates{{std::forward<E>(list)...}} {}

    vec& operator=(const vec& v) {
        coordinates = v.coordinates;
        return *this;
    }

    vec& operator+=(vec v) {
        for (size_t i = 0; i < size; i++) {
            coordinates[i] += v.coordinates[i];
        }
        return *this;
    }

    vec& operator-=(vec v) {
        for (size_t i = 0; i < size; i++) {
            coordinates[i] -= v.coordinates[i];
        }
        return *this;
    }

    vec operator+(vec v) {
        vec tmp = *this;
        tmp += v;
        return tmp;
    }

    vec operator-(vec v) {
        vec tmp = *this;
        tmp -= v;
        return tmp;
    }

    vec& operator+=(double s) {
        for (size_t i = 0; i < size; i++) {
            coordinates[i] += s;
        }
        return *this;
    }
    vec& operator-=(double s) {
        for (size_t i = 0; i < size; i++) {
            coordinates[i] -= s;
        }
        return *this;
    }

    vec& operator*=(double s) {
        for (size_t i = 0; i < size; i++) {
            coordinates[i] *= s;
        }
        return *this;
    }
    vec& operator/=(double s) {
        for (size_t i = 0; i < size; i++) {
            coordinates[i] /= s;
        }
        return *this;
    }

    void set(coord_t arr) {
        *this = arr;
    }

    vec& normalize() {
        if (length() == 0) return *this;
        *this *= (1.0 / length());
        return *this;
    }

    double length() const {
        T sum = 0;
        for (auto item : coordinates) {
            sum += item*item;
        }
        return std::sqrt(sum);
    }

};

template <class T, size_t size>
vec<T, size> operator+(vec<T, size> left, double s) {
    left += s;
    return left;
}

template <class T, size_t size>
vec<T, size> operator-(vec<T, size> left, double s) {
    left -= s;
    return left;
}

template <class T, size_t size>
vec<T, size> operator*(vec<T, size> left, double s) {
    left *= s;
    return left;
}

template <class T, size_t size>
vec<T, size> operator/(vec<T, size> left, double s) {
    left /= s;
    return left;
}

template <class T, size_t size>
vec<T, size> operator+(double s, vec<T, size> right) {
    right += s;
    return right;
}

template <class T, size_t size>
vec<T, size> operator-(double s, vec<T, size> right) {
    right -= s;
    return right;
}

template <class T, size_t size>
vec<T, size> operator*(double s, vec<T, size> right) {
    right *= s;
    return right;
}

template <class T, size_t size>
vec<T, size> operator/(double s, vec<T, size> right) {
    right /= s;
    return right;
}
