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


// ==================================
// OBTAIN DIFFERENT ROTATION MATRICES
// ==================================

const vec3 IDENTITY_X = vec3(1.0f, 0.0f, 0.0f);
const vec3 IDENTITY_Y = vec3(0.0f, 1.0f, 0.0f);
const vec3 IDENTITY_Z = vec3(0.0f, 0.0f, 1.0f);

__attribute__((always_inline))
inline mat4 getXRotationMat(float angle) {
    return rotate(mat4(1.0f), radians(angle), IDENTITY_X);
}

__attribute__((always_inline))
inline mat4 getYRotationMat(float angle) {
    return rotate(mat4(1.0f), radians(angle), IDENTITY_Y);
}

__attribute__((always_inline))
inline mat4 getZRotationMat(float angle) {
    return rotate(mat4(1.0f), radians(angle), IDENTITY_Z);
}

__attribute__((always_inline)) 
inline mat4 getXYZRotationMat(float x_angle, float y_angle, float z_angle) {
    return getXRotationMat(x_angle) * getYRotationMat(y_angle) * getZRotationMat(z_angle);
}

// ========================
// ROTATE POINTS / VERTICES
// ========================

__attribute__((always_inline)) 
inline vec4 rotateX(vec4 point, float angle) {
    return getXRotationMat(angle) * point;
}

__attribute__((always_inline)) 
inline vec4 rotateY(vec4 point, float angle) {
    return getYRotationMat(angle) * point;
}

__attribute__((always_inline)) 
inline vec4 rotateZ(vec4 point, float angle) {
    return getZRotationMat(angle) * point;
}

__attribute__((always_inline))
inline vec4 rotateXYZ(vec4 point, float x_angle, float y_angle, float z_angle) {
    return getXYZRotationMat(x_angle, y_angle, z_angle) * point;
}

__attribute__((always_inline))
inline vec4 translate(vec4 point, float x, float y, float z) {
    return translate(mat4(1.0f), vec3(x, y, z)) * point;
}

__attribute__((always_inline))
inline vec3 project(vec4 p, vec3 cam, vec3 orient, vec3 surface) {
    bool cam_is_zero = cam.x == 0.0f && cam.y == 0.0f && cam.z == 0.0f;
    bool orient_is_zero = orient.x == 0.0f && orient.y == 0.0f && orient.z == 0.0f;

    if (cam_is_zero && orient_is_zero) 
        return vec3(p.x, p.y, 0.0f);

    vec4 cam_v4(cam, 0.0f);
    vec4 d;
    if (orient_is_zero) d = p - cam_v4;
    else d = getXYZRotationMat(orient.x, orient.y, orient.z) * (p - cam_v4);

    return vec3((surface.z / d.z * d.x) + surface.x, (surface.z / d.z * d.y) + surface.y, 0.0f); 
}