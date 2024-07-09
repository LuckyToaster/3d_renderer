#include <iostream>
#include <thread>
#include <chrono>
#include <armadillo>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "screen.hpp"
//#include "shape.hpp"
#include "projector.hpp"

using std::cout;
using std::endl;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;
using arma::vec;
using arma::mat;


int main() {
    Screen screen("Muh sooper dooper fast renderer", 1200, 600);
    //Shape shape = Shape::getCube();
    Shape2 shape = Shape2::getCube();

    Camera camera = {vec3(400.0, 200.0, 500.0), vec3(0.0, 0.0, 0.0)};
    vec3 surface(400.0f, 200.0f, 200.0f);
    //vec surface = { 400.0, 200.0, 200.0 };

    cout << glGetString(GL_VERSION) << endl;

    while (screen.input(camera)) {
        //for (Line& line : shape.lines) {
        for (long unsigned int i = 0; i < shape.vertices.size(); i++) {
            //line.p1 = vecRotateXYZ(line.p1, 0.02, 0.02, 0.02);
            //line.p2 = vecRotateXYZ(line.p2, 0.02, 0.02, 0.02);
            //vec p1 = project(line.p1, camera.pos, camera.orientation, surface);
            //vec p2 = project(line.p2, camera.pos, camera.orientation, surface);
            //screen.drawline(p1(0), p1(1), p2(0), p2(1));

            shape.projectedVertices[i] = glmProject(shape.vertices[i], camera.pos, camera.orientation, surface);
            
        }

        vector<GLfloat> projected = shape.getProjectedVerticesAsGLfloat();

        screen.draw(projected);
        screen.update();
        sleep_for(milliseconds(16)); // ~60hz
        //SDL_Delay(16);
        screen.clear();
    } 
    return 0;
}