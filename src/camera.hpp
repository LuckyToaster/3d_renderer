using arma::vec;

struct Camera {
    vec pos;
    vec orientation;
};

void moveForward(Camera &camera, double distance) {
    // Assuming orientation[0] is the yaw angle
    camera.pos(0) += distance * cos(camera.orientation(0));
    camera.pos(1) += distance * sin(camera.orientation(0));
}

// Function to strafe the camera left or right
void strafe(Camera &camera, double distance) {
    // Assuming orientation[0] is the yaw angle
    camera.pos(0) += distance * sin(camera.orientation(0));
    camera.pos(1) -= distance * cos(camera.orientation(0));
}

// Function to change the camera's yaw (looking left or right)
void turn(Camera &camera, double angle) {
    camera.orientation(0) += angle;
}
