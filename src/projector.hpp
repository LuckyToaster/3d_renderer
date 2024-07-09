using glm::mat4;
using glm::vec4;
using glm::vec3;
using glm::radians;
using glm::rotate;
using glm::translate;

/* 
    see https://en.wikipedia.org/wiki/3D_projection -> mathematical formula
    see https://en.wikipedia.org//wiki/Rotation_matrix -> rotation matrices
    see https://en.wikipedia.org/wiki/Euler_angles#Tait%E2%80%93Bryan_angles 
        -> 3 angles (one for each axis)
        -> ORDER MATTERS: if we do XYZ rotation -> rot x, then rot y then rot z, (different order different result)
        -> to rotate point or 3x3 basis, we multiply it by its rotation matrices in the order we want
    maybe see quaternions? https://en.wikipedia.org/wiki/Rotation_formalisms_in_three_dimensions 
*/

const vec3 IDENTITY_X = vec3(1.0f, 0.0f, 0.0f);
const vec3 IDENTITY_Y = vec3(0.0f, 1.0f, 0.0f);
const vec3 IDENTITY_Z = vec3(0.0f, 0.0f, 1.0f);

__attribute__((always_inline))
inline mat4 getGlmXRotationMat(float angle) {
    return rotate(mat4(1.0f), radians(angle), IDENTITY_X);
}

__attribute__((always_inline))
inline mat4 getGlmYRotationMat(float angle) {
    return rotate(mat4(1.0f), radians(angle), IDENTITY_Y);
}

__attribute__((always_inline))
inline mat4 getGlmZRotationMat(float angle) {
    return rotate(mat4(1.0f), radians(angle), IDENTITY_Z);
}

__attribute__((always_inline)) 
inline mat4 getGlmXYZRotationMat(float x_angle, float y_angle, float z_angle) {
    return getGlmXRotationMat(x_angle) * getGlmYRotationMat(y_angle) * getGlmZRotationMat(z_angle);
}

__attribute__((always_inline)) 
inline vec4 glmRotateX(vec4 point, float angle) {
    return getGlmXRotationMat(angle) * point;
}

__attribute__((always_inline)) 
inline vec4 glmRotateY(vec4 point, float angle) {
    return getGlmYRotationMat(angle) * point;
}

__attribute__((always_inline)) 
inline vec4 glmRotateZ(vec4 point, float angle) {
    return getGlmZRotationMat(angle) * point;
}

__attribute__((always_inline))
inline vec4 glmRotateXYZ(vec4 point, float x_angle, float y_angle, float z_angle) {
    return getGlmXYZRotationMat(x_angle, y_angle, z_angle) * point;
}

__attribute__((always_inline))
inline vec4 translate(vec4 point, float x, float y, float z) {
    return glm::translate(mat4(1.0f), vec3(x, y, z)) * point;
}


vec3 glmProject(vec4 p, vec3 cam, vec3 orient, vec3 surface) {
    bool cam_is_zero = cam.x == 0.0f && cam.y == 0.0f && cam.z == 0.0f;
    bool orient_is_zero = orient.x == 0.0f && orient.y == 0.0f && orient.z == 0.0f;

    if (cam_is_zero && orient_is_zero) 
        return vec3(p.x, p.y, 0.0f);

    vec4 cam_v4(cam, 0.0f);
    vec4 d;

    if (orient_is_zero) d = p - cam_v4;
    else d = getGlmXYZRotationMat(orient.x, orient.y, orient.z) * (p - cam_v4);

    return vec3((surface.z / d.z * d.x) + surface.x, (surface.z / d.z * d.y) + surface.y, 0.0f); 
}

// =======================
// USING ARMADILLO LIBRARY
// =======================
/*using std::cerr;
using std::endl;
using std::cos;
using std::sin;
using arma::mat;
using arma::vec;

mat getXRotationMat(double angle) {
    mat res = {
        {1.0, 0.0, 0.0},
        {0.0, cos(angle), -sin(angle)},
        {0.0, sin(angle), cos(angle)}
    };
    return res;
}

mat getYRotationMat(double angle) {
    mat res = {
        {cos(angle), 0.0, sin(angle)},
        {0.0, 1.0, 0.0},
        {-sin(angle), 0.0, cos(angle)}
    };
    return res;
}

mat getZRotationMat(double angle) {
    mat res = {
        {cos(angle), -sin(angle), 0.0},
        {sin(angle), cos(angle), 0.0},
        {0.0, 0.0, 1.0}
    };
    return res;
}

mat getXYZRotationMat(double x_angle, double y_angle, double z_angle) {
    return getXRotationMat(x_angle) * getYRotationMat(y_angle) * getZRotationMat(z_angle);
}

mat rotateX(mat m, double angle ) {
    return m * getXRotationMat(angle);
}

mat rotateY(mat m, double angle) {
    return m * getYRotationMat(angle);
}

mat rotateZ(mat m, double angle) {
    return m * getZRotationMat(angle);
}

mat rotateXYZ(mat m, double x_angle, double y_angle, double z_angle) {
    return m * getXRotationMat(x_angle) * getYRotationMat(y_angle) * getZRotationMat(z_angle);
}

vec vecRotateX(vec v, double angle) {
    return (v.t() * getXRotationMat(angle)).t();
}

vec vecRotateY(vec v, double angle) {
    return (v.t() * getYRotationMat(angle)).t();
}

vec vecRotateZ(vec v, double angle) {
    return (v.t() * getZRotationMat(angle)).t();
}

vec vecRotateXYZ(vec v, double x_angle, double y_angle, double z_angle) {
    return (v.t() * getXRotationMat(x_angle) * getYRotationMat(y_angle) * getZRotationMat(z_angle)).t();
}


vec project(vec point, vec camera, vec orientation, vec surface) {
    if (point.size() < 3 || camera.size() < 3 || orientation.size() < 3 || surface.size() < 3)
        cerr << "please give points in 3D (vecs of size 3)" << endl;

    vec res(2);

    if (orientation.is_zero() && camera.is_zero()) {
        res(0) = point(0);
        res(1) = point(1);
        return res;
    }

    vec d(3);
    if (orientation.is_zero()) d = point - camera;
    else d = getXYZRotationMat(orientation(0), orientation(1), orientation(2)) * (point - camera);

    res(0) = (surface(2) / d(2) * d(0)) + surface(0);
    res(1) = (surface(2) / d(2) * d(1)) + surface(1);
    return res;
}*/

