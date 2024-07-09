using std::vector;
using glm::vec4;
using glm::vec3;

class Shape {
    public:
        vector<vec4> vertices; // each pair is a line
        vector<vec3> projected; // used to store the projected vertices
        vector<GLfloat> getProjectedAsGLfloat();
        vector<GLfloat> getVerticesAsGLfloat();
        static Shape getCube();
        Shape(vector<glm::vec4>&& vertices_) : vertices(std::move(vertices_)) {
            this->projected.reserve(vertices.size());
            this->projected.resize(vertices.size(), vec3(0.0f));
        }
};


vector<GLfloat> Shape::getProjectedAsGLfloat() {
    vector<GLfloat> res; 
    for (vec3 v : projected) {
        res.push_back(v.x);
        res.push_back(v.y);
        res.push_back(v.z);
    }
    return res;
}


vector<GLfloat> Shape::getVerticesAsGLfloat() {
    vector<GLfloat> res;
    for (vec4 v : vertices) {
        res.push_back(v.x);
        res.push_back(v.y);
        res.push_back(v.z);
    }
    return res; // we move bc this way we just return a ptr and size
}


Shape Shape::getCube() {
    vector<vec4> vertices = {
        vec4(100.0f, 100.0f, 100.0f, 1.0f), vec4(200.0f, 100.0f, 100.0f, 1.0f), // Line from p1 to p2
        vec4(100.0f, 100.0f, 100.0f, 1.0f), vec4(100.0f, 100.0f, 200.0f, 1.0f), // Line from p1 to p5
        vec4(100.0f, 100.0f, 100.0f, 1.0f), vec4(100.0f, 0.0f, 100.0f, 1.0f), // Line from p1 to p3
        vec4(100.0f, 100.0f, 200.0f, 1.0f), vec4(100.0f, 0.0f,  200.0f, 1.0f), // Line from p5 to p7
        vec4(100.0f, 100.0f, 200.0f, 1.0f), vec4(200.0f, 100.0f, 200.0f, 1.0f), // Line from p5 to p6
        vec4(200.0f, 100.0f, 200.0f, 1.0f), vec4(200.0f, 100.0f, 100.0f, 1.0f), // Line from p6 to p2
        vec4(200.0f, 100.0f, 200.0f, 1.0f), vec4(200.0f, 0.0f,  200.0f, 1.0f), // Line from p6 to p8
        vec4(200.0f, 0.0f,  200.0f,  1.0f), vec4(200.0f, 0.0f,  100.0f, 1.0f), // Line from p8 to p4
        vec4(200.0f, 0.0f,  100.0f,  1.0f), vec4(200.0f, 100.0f, 100.0f, 1.0f), // Line from p4 to p2
        vec4(200.0f, 0.0f,  100.0f,  1.0f), vec4(100.0f, 0.0f,  100.0f, 1.0f), // Line from p4 to p3
        vec4(100.0f, 0.0f,  200.0f,  1.0f), vec4(100.0f, 0.0f,  100.0f, 1.0f), // Line from p7 to p3
        vec4(100.0f, 0.0f,  200.0f,  1.0f), vec4(200.0f, 0.0f,  200.0f, 1.0f), // Line from p7 to p8
    };
    return std::move(Shape(std::move(vertices)));
}