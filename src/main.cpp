#include <iostream>
#include <thread>
#include <chrono>
#include <armadillo>

#include "screen.hpp"
#include "shape.hpp"
#include "projector.hpp"

using std::cout;
using std::endl;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;
using arma::vec;


int main() {
    Screen screen(800, 400);
    const Shape& cube = Shapes::cube;
    vec camera = {50.0, 50.0, 0.0 };    // this also moves the camera / object but distorts it
    vec orientation = { 0.0, 0.0, 0.0 }; // hmmm this distorts the shit nigga
    vec surface = { 100.0, 100.0, 100.0 }; // moving around, (moves the camera or object idc)

    while (screen.input()) {
        for (const Line& line : cube.lines) {
            vec p1 = /*Projector::*/project(line.p1, camera, orientation, surface);
            vec p2 = /*Projector::*/project(line.p2, camera, orientation, surface);
            screen.line(p1(0), p1(1), p2(0), p2(1));
        }

        screen.show();
        sleep_for(milliseconds(16));
        screen.clear();

        //camera(0) += 1.0;
        //camera(1) += 1.0;
        //camera(2) += 1.0;
        //surface(0) += 1.0;
        //surface(1) += 1.0;
        //surface(2) += 1.0;
        //orientation(0) += 0.1;
        //orientation(1) += 0.01;
        orientation(2) += 0.05;
    } 
    return 0;
}