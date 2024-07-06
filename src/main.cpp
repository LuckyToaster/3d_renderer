#include <iostream>
#include <thread>
#include <chrono>
#include <armadillo>

#include "screen.hpp"
#include "shape.hpp"
#include "projector.hpp"
//#include "camera.hpp"

using std::cout;
using std::endl;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;
using arma::vec;


int main() {
    Screen screen(800, 400);
    const Shape& shape = Shapes::cube;

    Camera camera = { {400.0, 200.0, 500.0}, {0.0, 0.0, 0.0} };
    vec surface = { 400.0, 200.0, 200.0 };  // what this do?

    while (screen.input(camera)) {
        for (const Line& line : shape.lines) {
            vec p1 = project(line.p1, camera.pos, camera.orientation, surface);
            vec p2 = project(line.p2, camera.pos, camera.orientation, surface);
            screen.line(p1(0), p1(1), p2(0), p2(1));
        }

        screen.show();
        sleep_for(milliseconds(16)); // ~60hz
        screen.clear();
    } 
    return 0;
}