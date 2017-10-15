#include <PyramideV8.hpp>

#include <cmath>

PyramideV8::PyramideV8() {
    InitPyramide();
}

void PyramideV8::InitPyramide() {
    const float ANGLE = std::atan(1);
    const float R_BASE = 1.0f;
    const float R_CUT = 0.5f;
    const float HEGHT = 1.0f;

    for (auto i = 0; i < BASE_VERTEX_COUNT; i++) {
        Vertex v = {
            {R_BASE * std::cos(i * ANGLE), R_BASE * std::sin(i * ANGLE), 0, 1}};
        Vertexes[i] = v;
    }

    for (auto i = BASE_VERTEX_COUNT; i < 2 * BASE_VERTEX_COUNT; i++) {
        Vertex v = {{R_CUT * std::cos(i * ANGLE), R_CUT * std::sin(i * ANGLE),
                     HEGHT, 1}};
        Vertexes[i] = v;
    }
}
