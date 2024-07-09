//using arma::vec;

using glm::vec3;



struct Camera {
    vec3 pos;
    vec3 orientation;
};

// Function to strafe the camera left or right ==> wtf?
void strafe(Camera &camera, double distance) {
    // Assuming orientation[0] is the yaw angle
    camera.pos.x += distance * sin(camera.orientation.x);
    camera.pos.y -= distance * cos(camera.orientation.x);
}
