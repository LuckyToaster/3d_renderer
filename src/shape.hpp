using std::vector;
using glm::vec4;

/*
struct Line {
    vec p1;
    vec p2;
};

class Shape {
    public:
        vector<Line> lines;
        static Shape getCube();
        static Shape getPyramid();
};

Shape Shape::getCube() {
    vec p1 = {100.0, 100.0, 100.0};
    vec p2 = {200.0, 100.0, 100.0};
    vec p3 = {100.0, 0.0, 100.0};
    vec p4 = {200.0, 0.0, 100.0};
    vec p5 = {100.0, 100.0, 200.0};
    vec p6 = {200.0, 100.0, 200.0};
    vec p7 = {100.0, 0.0, 200.0};
    vec p8 = {200.0, 0.0, 200.0};

    Line l12 = { p1, p2 };
    Line l15 = { p1, p5 };
    Line l13 = { p1, p3 };
    Line l57 = { p5, p7 };
    Line l56 = { p5, p6 };
    Line l62 = { p6, p2 };
    Line l68 = { p6, p8 };
    Line l84 = { p8, p4 };
    Line l42 = { p4, p2 };
    Line l43 = { p4, p3 };
    Line l73 = { p7, p3 };
    Line l78 = { p7, p8 };

    vector<Line> cube_lines = { l12, l15, l13, l57, l56, l62, l68, l84, l42, l43, l73, l78 };
    Shape cube { cube_lines };
    return cube;
}


Shape Shape::getPyramid() {
    vec t1 = {100.0, 100.0, 100.0};
    vec t2 = {200.0, 100.0, 100.0};
    vec t3 = {100.0, 0.0, 100.0};
    vec t4 = {150.0, 200.0, 150.0};

    Line t12 = { t1, t2 };
    Line t23 = { t2, t3 };
    Line t13 = { t1, t3 };
    Line t14 = { t1, t4};
    Line t24 = { t2, t4};
    Line t34 = { t3, t4};

    vector<Line> pyramid_lines = { t12, t23, t13, t14, t24, t34 };
    Shape pyramid = { pyramid_lines };
    return pyramid;
}
*/

using glm::vec4;

class Shape2 {
    public:
        vector<vec4> vertices; // each pair is a line
        vector<vec3> projectedVertices;
        Shape2(vector<glm::vec4>&& vertices_) : vertices(std::move(vertices_)) {
            this->projectedVertices.reserve(vertices.size());
        }
        vector<GLfloat> getVerticesAsGLfloat();
        static Shape2 getCube();
};

/*Shape2::Shape2(vector<glm::vec4>&& vertices_) : vertices(std::move(vertices_)) {
    this->projectedVertices.reserve(vertices.size());
}*/


vector<GLfloat> Shape2::getProjectedVerticesAsGLfloat() {
    vector<GLfloat> res; 
    for (vec3 v : projectedVertices) {
        res.push_back(v.x);
        res.push_back(v.y);
        res.push_back(v.z);
    }
    return std::move(res);
}


vector<GLfloat> Shape2::getVerticesAsGLfloat() {
    vector<GLfloat> res;
    for (vec4 v : vertices) {
        res.push_back(v.x);
        res.push_back(v.y);
        res.push_back(v.z);
    }
    return std::move(res); // we move bc this way we just return a ptr and size
}


Shape2 Shape2::getCube() {
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
    return std::move(Shape2(std::move(vertices)));
}