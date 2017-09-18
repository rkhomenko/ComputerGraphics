#include <Lab01Widget.hpp>

#include <QApplication>
#include <QDebug>
#include <QOpenGLShaderProgram>

#include <array>
#include <vector>
#include <cmath>

const char* Lab01Widget::VertexShaderSource =
    "attribute highp vec4 posAttr;\n"
    "varying lowp vec4 col;\n"
    "uniform int colIndex;\n"
    "void main() {\n"
    "    col = vec4(0.0, 1.0, 0.0, 1.0);\n"
    "    if (colIndex == 0) {\n"
    "        col = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "    }\n"
    "    else if (colIndex == 1) {\n"
    "        col = vec4(0.0, 0.0, 1.0, 1.0);\n"
    "    }\n"
    "    else if (colIndex == 2) {\n"
    "        col = vec4(0.827, 0.827, 0.827, 1.0);\n"
    "    }\n"
    "    else if (colIndex == 3) {\n"
    "        col = vec4(0.529, 0.808, 0.922, 1.0);\n"
    "    }\n"
    "    else {\n"
    "        col = vec4(0.0, 0.0, 0.0, 1.0);\n"
    "    }\n"
    "    gl_Position = posAttr;\n"
    "}\n";

const char* Lab01Widget::FragmentShaderSource =
    "varying lowp vec4 col;\n"
    "void main() {\n"
    "    gl_FragColor = col;\n"
    "}\n";

Lab01Widget::Lab01Widget(QWidget* parent)
    : OpenGLWidget(parent) {

    A = 10;
    B = 20;

    connect(this, &OpenGLWidget::VariablesChanged, this, &Lab01Widget::OnVariablesChanged);
}

void Lab01Widget::OnVariablesChanged() {
    qDebug() << "Changed";
    //paintGL();
    repaint();
}

void Lab01Widget::SetVariables() {
    A = static_cast<int>(getVariable("a"));
    B = static_cast<int>(getVariable("B"));
}

void Lab01Widget::initializeGL() {
    initializeOpenGLFunctions();

    Program = new QOpenGLShaderProgram(this);
    Program->addShaderFromSourceCode(QOpenGLShader::Vertex, VertexShaderSource);
    Program->addShaderFromSourceCode(QOpenGLShader::Fragment, FragmentShaderSource);
    if (!Program->link()) {
        qDebug() << Program->log();
        QApplication::quit();

    }
    PositionAttr = Program->attributeLocation("posAttr");
    ColorUniform = Program->uniformLocation("colIndex");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Lab01Widget::resizeGL(int width, int height) {}

GLfloat Lab01Widget::GetX(int x) {
    const auto halfWidth = this->width() / 2;
    return static_cast<GLfloat>(x - halfWidth) / halfWidth;
}

GLfloat Lab01Widget::GetY(int y) {
    return y / (0.5f * this->height());
}

void Lab01Widget::DrawLines(const std::vector<GLfloat> points) {
    glVertexAttribPointer(PositionAttr, 2, GL_FLOAT, GL_FALSE, 0, points.data());
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_LINES, 0, points.size() / 2);
    glDisableVertexAttribArray(0);
}

void Lab01Widget::DrawLine(const std::vector<GLfloat> points) {
    glVertexAttribPointer(PositionAttr, 2, GL_FLOAT, GL_FALSE, 0, points.data());
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_LINE_STRIP, 0, points.size() / 2);
    glDisableVertexAttribArray(0);
}

int Lab01Widget::DrawAxesAndGrid(int num) {
    const auto INTS_PER_LINE = 4;
    const std::vector<GLfloat> OXOY = {
                                        -0.999f, -1.0f,
                                        -0.999f,  1.0f,
                                        -1.0f,  0.0f,
                                         1.0f,  0.0f
                                      };

    std::vector<GLfloat> OXAxes;
    std::vector<GLfloat> OYAxes;

    OXAxes.reserve(INTS_PER_LINE * num);
    OYAxes.reserve(INTS_PER_LINE * num);

    const auto step = ((this->width() < this->height()) ? this->width()
                                                        : this->height()) / num;

    auto x = step;
    for (auto i = 0; i < this->width() / num; i++) {
        const auto y = 1.0f;
        auto abs_x = GetX(x);
        std::array<GLfloat, 4> points = {
            abs_x, -y,
            abs_x, y
        };
        OYAxes.insert(OYAxes.end(), points.begin(), points.end());
        x += step;
    }

    auto y = step;
    for (auto i = 0; i < this->height() / num; i++) {
        const auto x = 1.0f;
        auto abs_y = GetY(y);
        std::array<GLfloat, 8> points {
            -x, abs_y,
             x, abs_y,
            -x, -abs_y,
             x, -abs_y
        };
        OXAxes.insert(OXAxes.end(), points.begin(), points.end());
        y += step;
    }

    Program->setUniformValue(ColorUniform, GREY);
    DrawLines(OXAxes);
    DrawLines(OYAxes);

    Program->setUniformValue(ColorUniform, RED);
    DrawLines(OXOY);

    return step;
}

void Lab01Widget::DrawAsymptote(int a) {
    const auto abs_a = GetX(a);
    std::vector<GLfloat> coords = { abs_a, -1.0f,
                                    abs_a,  1.0f };
    Program->setUniformValue(ColorUniform, LIGHT_BLUE);
    DrawLines(coords);
}

void Lab01Widget::DrawCurve(int a, int b, int step) {
    std::vector<GLfloat> coords;
    coords.reserve(b * step);

    auto max = std::min(a, b);

    for (int i = 0; i < max * step; i++) {
        auto x = i;
        auto y = std::sqrt(i * i * i / (a * step - i));
        coords.push_back(GetX(x));
        coords.push_back(GetY(y));
    }

    Program->setUniformValue(ColorUniform, BLUE);
    DrawLine(coords);

    for (auto i = 1; i < coords.size(); i += 2) {
        coords[i] = -coords[i];
    }
    DrawLine(coords);
}

void Lab01Widget::paintGL() {
    if (!isEmptyVariables()) {
        SetVariables();
    }

    Program->bind();

    auto step = DrawAxesAndGrid(11);
    DrawAsymptote(step * A);
    DrawCurve(A, B, step);

    Program->release();
}
