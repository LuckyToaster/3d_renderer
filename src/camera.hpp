using glm::vec3;

class Camera {
    public:
        vec3 pos;
        vec3 orientation;
        static Camera getDefault();
        void strafe(Camera& c, float distance);
};

Camera Camera::getDefault() {
    return Camera{vec3(400.0, 200.0, 500.0), vec3(0.0, 0.0, 0.0)};
}

// Function to strafe the camera left or right ==> wtf?
void Camera::strafe(Camera& c, float distance) {
    c.pos.x += distance * sin(c.orientation.x);
    c.pos.y -= distance * cos(c.orientation.x);
}
