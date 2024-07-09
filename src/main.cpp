#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL_opengl.h>

#include "shape.hpp"
#include "screen.hpp"
#include "projector.hpp"

using std::cout;
using std::endl;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

int main() {
    Screen screen("Muh sooper dooper fast renderer", 1200, 600);
    Shape shape = Shape::getCube();
    Camera c = Camera::getDefault();
    vec3 surface(400.0f, 200.0f, 200.0f);

    cout << glGetString(GL_VERSION) << endl;

    while (screen.input(c)) {
        for (auto i = 0; i < shape.vertices.size(); i++) {
            shape.vertices[i] = rotateXYZ(shape.vertices[i], 2.0f, 2.0f, 2.0f);
            shape.projected[i] = project(shape.vertices[i], c.pos, c.orientation, surface);
        }

        vector<GLfloat> projected = shape.getProjectedAsGLfloat();
        screen.draw(projected);
        screen.update();
        sleep_for(milliseconds(16)); // ~60hz or use SDL_Delay(16);
        screen.clear();
    } 
    return 0;
}