#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "camera.hpp"

using std::vector;
using std::sqrt;
using std::atan2;
using std::cos;
using std::sin;

class Screen {
    SDL_Event e;
    SDL_Window* window;
    //SDL_Renderer* renderer;
    SDL_GLContext context; // only when using opengl for rendering 
    vector<SDL_FPoint> points;
    public:
        int width, height;
        Screen(int width, int height);
        void pixel(float x, float y);
        void line(float x1, float y1, float x2, float y2);
        void show();
        bool input(Camera& camera);
        void clear();
};

// ==============
// IMPLEMENTATION
// ==============

Screen::Screen(int width, int height) {
    this->width = width;
    this->height = height;
    this->window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    this->context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(SDL_FALSE); // the fuck this do
    glViewport(0, 0, width, height); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void Screen::pixel(float x, float y) {
    SDL_FPoint p = {x, y};
    points.emplace_back(p);
}


void Screen::show() {
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    //for (auto& point: points) SDL_RenderDrawPointF(renderer, point.x, point.y);
    //SDL_RenderPresent(renderer);

    glClear(GL_COLOR_BUFFER_BIT);

    // Draw each point
    glColor3f(1.0f, 0.0f, 0.0f); // Set the color to red
    glBegin(GL_POINTS);
    for (auto& point : points) {
        glVertex2f(point.x, point.y);
    }
    glEnd();

    glFlush();
    SDL_GL_SwapWindow(window);
}


void Screen::clear() {
    points.clear();
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    //SDL_RenderClear(renderer);

    // opengl
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}


/*
void Screen::line(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = sqrt( dx * dx + dy * dy);
    float angle = atan2(dy, dx);

    for (float i = 0; i < length; i++) 
        pixel(x1 + cos(angle) * i, y1 + sin(angle) * i);
}*/

void Screen::line(float x1, float y1, float x2, float y2) {
    GLfloat vertices[] = {x1, y1, 0, x2, y2, 0 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_LINES, 0, 2); // draw line, first elem, n_elems
    glDisableClientState(GL_VERTEX_ARRAY);
    SDL_GL_SwapWindow(window);
}


bool Screen::input(Camera& camera) {
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
            //SDL_DestroyRenderer(renderer);
            //SDL_DestroyWindow(window);

            // only for opengl
            SDL_GL_DeleteContext(context); 
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_w: camera.pos(2) -= 6.0; break; // forward / backward is Z axis
                case SDLK_s: camera.pos(2) += 6.0; break;
                case SDLK_a: camera.pos(0) += 6.0; break; // left / right is X axis 
                case SDLK_d: camera.pos(0) -= 6.0; break;
                case SDLK_q: camera.pos(1) += 6.0; break; // up / down is Y axis
                case SDLK_e: camera.pos(1) -= 6.0; break;
                case SDLK_UP: camera.orientation(2) += 0.1; break;
                case SDLK_DOWN: camera.orientation(2) -= 0.1; break;
                case SDLK_LEFT: camera.orientation(0) -= 0.1; break;
                case SDLK_RIGHT: camera.orientation(0) += 0.1; break;
                default: std::cout << "some other key pressed" << std::endl; break;
            }
        }
    }
    return true;
}