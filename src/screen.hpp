//#include <SDL2/SDL.h>

using std::cout;
using std::cerr;
using std::endl;

class Screen {
    public:
        GLFWwindow* window;
        int width, height;
        Screen(const char* name, int width, int height);
        void draw(vector<GLfloat>& vertices); 
        void update();
        void clear();
        bool input(Camera& camera);
};


// ==============
// IMPLEMENTATION
// ==============

Screen::Screen(const char* name, int width, int height) {
    this->width = width;
    this->height = height;

    if (!glfwInit()) cerr << "Failed to initialize GLFW" << endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Request at least OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use core profile
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    this->window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (window == NULL) cerr << "Failed to create GLFW window" << endl;

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1); // vsync

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) 
        cerr << "Failed to initialize GLAD" << endl;

    glad_glViewport(0, 0, width, height); 
    glad_glMatrixMode(GL_PROJECTION);
    glad_glLoadIdentity();
    glad_glOrtho(0, width, 0, height, 0, 1);
    glad_glMatrixMode(GL_MODELVIEW);
    glad_glLoadIdentity();
    cout << glad_glGetString(GL_VERSION) << endl;
}


void Screen::draw(vector<GLfloat>& vertices) {
    glad_glEnableClientState(GL_VERTEX_ARRAY);
        glad_glVertexPointer(3, GL_FLOAT, 0, vertices.data());
        glad_glDrawArrays(GL_LINES, 0, vertices.size() / 3);
    glad_glDisableClientState(GL_VERTEX_ARRAY);
}

void Screen::update() {
    glfwSwapBuffers(window);
}

void Screen::clear() {
    glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


bool Screen::input(Camera& c) {
    glfwPollEvents(); // gotta call this somewhere

    if (glfwWindowShouldClose(window)) return false; 
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) return false; 

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cout << "lol w key" << endl;
        c.pos.z -= 9.0;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        c.pos.z += 9.0;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        c.pos.x -= 9.0;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        c.pos.x += 9.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        c.pos.y += 9.0;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        c.pos.y -= 9.0;
    }

    // arrows?

    return true; // Keep the window open by default
}