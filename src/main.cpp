#include <iostream>
#include <armadillo>
#include <cmath>
#include <SDL2/SDL.h>

using std::cout;
using std::endl;
using std::cerr;
using std::cos;
using std::sin;

using arma::mat;
using arma::vec;
//using namespace arma;


int main() {
    return 0;
}


// =================
// CLASS DEFINITIONS 
// =================

class Rotation {
    public:
        static mat x_mat(double angle);
        static mat y_mat(double angle);
        static mat z_mat(double angle);
        static mat x(mat m, double angle);
        static mat y(mat m, double angle);
        static mat z(mat m, double angle);
};

class Projection3D {
    public:
        vec point, camera, orientation, surface; 
        Projection3D(vec p, vec c, vec c_orientation, vec s);
        vec get_projection();
};

// =====================
// CLASS IMPLEMENTATIONS
// =====================

mat Rotation::x_mat(double angle) {
    mat res = {
        {1.0, 0.0, 0.0},
        {0.0, cos(angle), -sin(angle)},
        {0.0, sin(angle), cos(angle)}
    };
    return res;
}

mat Rotation::y_mat(double angle) {
    mat res = {
        {cos(angle), 0.0, sin(angle)},
        {0.0, 1.0, 0.0},
        {-sin(angle), 0.0, cos(angle)}
    };
    return res;
}

mat Rotation::z_mat(double angle) {
    mat res = {
        {cos(angle), -sin(angle), 0.0},
        {sin(angle), cos(angle), 0.0},
        {0.0, 0.0, 1.0}
    };
    return res;
}

mat Rotation::x(mat v, double angle ) {
    return v * Rotation::x_mat(angle);
}

mat Rotation::y(mat v, double angle) {
    return v * Rotation::y_mat(angle);
}

mat Rotation::z(mat v, double angle) {
    return v * Rotation::z_mat(angle);
}


Projection3D::Projection3D(vec p, vec c, vec c_orient, vec s) {
    if (p.size() == 3 && c.size() == 3 && c_orient.size() == 3 && s.size() == 3) {
        this->point = p;
        this->camera = c;
        this->orientation = c_orient;
        this->surface = s;
    } else cerr << "please give valid parameters" << endl;
}

vec Projection3D::get_projection() {
    vec res(2);

    if (point.is_zero() && camera.is_zero()) {
        res(0) = point(0);
        res(1) = point(1);
        return res;
    }

    vec d(3);
    if (orientation.is_zero()) d = point - camera;
    else d = Rotation::x_mat(orientation(0)) * Rotation::y_mat(orientation(1)) * Rotation::z_mat(orientation(2)) * (point - camera);

    res(0) = (surface(2) / d(2) * d(0)) + surface(0);
    res(1) = (surface(2) / d(2) * d(1)) + surface(1);
    return res;
}

