#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

/*
WHY GLAD? even though that i can use opengl functions by importing opengl (SDL2/SDL_opengl.h in this case) 
a function that is only available on a certain opengl version or that is simply not supported by the 
graphics driver might be called, and glad will load all the opengl functions that are supported 
the driver and the opengl version because it will load the definitions in a 'glad.h' file.
This facilitates working with opengl because we don't have to do manual checking to see if something will work 
and we will have a list of all the functions we can call
*/
#include "glad/glad.h" 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "camera.hpp"
#include "projector.hpp"
#include "shape.hpp"
#include "screen.hpp"

using std::cout;
using std::endl;

using std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration;
using std::chrono::duration_cast;


int main() {
    Screen screen("Muh sooper dooper fast renderer", 1200, 600);
    Camera c = Camera::getDefault();
    vec3 surface(400.0f, 200.0f, 200.0f);
    Shape shape = Shape::getCube();

    double delta_t = 0.0; 
    time_point start = steady_clock::now();

    while (screen.input(c)) {
        time_point end = steady_clock::now();
        delta_t = duration_cast<duration<double>>(end - start).count();
        start = end;

        for (auto i = 0; i < shape.vertices.size(); i++) {
            shape.vertices[i] = rotateXYZ(shape.vertices[i], 2.0f, 2.0f, 2.0f);
            shape.projected[i] = project(shape.vertices[i], c.pos, c.orientation, c.surface);

            //cout << "vertex " << i << ": " << shape.vertices[i].x << endl;
            //cout << "projected vertex " << i << ": " << shape.projected[i].x << endl;
        }


        vector<GLfloat> projected = shape.getProjectedAsGLfloat();
        screen.draw(projected);
        screen.update();
        screen.clear();
        start = steady_clock::now();
    } 
    return 0;
}