#include <armadillo>
#include <vector>

using arma::vec;
using std::vector;

struct Line {
    vec p1;
    vec p2;
};

struct Shape {
    vector<Line> lines;
};

namespace Shapes {
    const vec p1 = {100.0, 100.0, 100.0};
    const vec p2 = {200.0, 100.0, 100.0};
    const vec p3 = {100.0, 0.0, 100.0};
    const vec p4 = {200.0, 0.0, 100.0};
    const vec p5 = {100.0, 100.0, 200.0};
    const vec p6 = {200.0, 100.0, 200.0};
    const vec p7 = {100.0, 0.0, 200.0};
    const vec p8 = {200.0, 0.0, 200.0};

    const Line l12 = { p1, p2 };
    const Line l15 = { p1, p5 };
    const Line l13 = { p1, p3 };
    const Line l57 = { p5, p7 };
    const Line l56 = { p5, p6 };
    const Line l62 = { p6, p2 };
    const Line l68 = { p6, p8 };
    const Line l84 = { p8, p4 };
    const Line l42 = { p4, p2 };
    const Line l43 = { p4, p3 };
    const Line l73 = { p7, p3 };
    const Line l78 = { p7, p8 };

    const vector<Line> lines = { l12, l15, l13, l57, l56, l62, l68, l84, l42, l43, l73, l78 };

    const Shape cube{ lines };
}
