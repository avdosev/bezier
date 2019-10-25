#pragma  once

struct point {
    double x,y;
};

point operator * (point pp, double mu) {
    return point{pp.x*mu, pp.y*mu};
}

point operator * (double mu, point pp) {
    return point{pp.x*mu, pp.y*mu};
}

point operator + (point pp, double mu) {
    return point{pp.x+mu, pp.y+mu};
}

point operator + (double mu, point pp) {
    return point{pp.x+mu, pp.y+mu};
}

point operator + (point mu, point pp) {
    return point{pp.x+mu.x, pp.y+mu.y};
}
