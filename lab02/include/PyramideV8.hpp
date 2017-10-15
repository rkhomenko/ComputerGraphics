#ifndef CG_LABS_LAB02_PYRAMIDEV8_HPP_
#define CG_LABS_LAB02_PYRAMIDEV8_HPP_

#include <array>
#include <vector>

class PyramideV8 {
public:
    using Vertex = std::array<float, 4>;

    PyramideV8();

private:
    static const auto BASE_VERTEX_COUNT = 8;
    void InitPyramide();

    std::array<Vertex, 2 * BASE_VERTEX_COUNT> Vertexes;
};

#endif  // CG_LABS_LAB02_PYRAMIDEV8_HPP_
