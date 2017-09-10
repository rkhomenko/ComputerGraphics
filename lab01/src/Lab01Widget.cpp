#include <Lab01Widget.hpp>

#include <QDebug>
#include <QOpenGLShaderProgram>

#include <vector>
#include <cmath>

const GLfloat Lab01Widget::AxesVertices[] = {
    -1.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, -1.0f,
    0.0f,  1.0f
};

const char* Lab01Widget::VertexShaderSource =
    "attribute highp vec4 positionAttr;\n"
    "void main() {\n"
    "    gl_Position = positionAttr;\n"
    "}\n";

const char* Lab01Widget::FragmentAxesShaderSource =
    "void main() {\n"
    "    gl_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n";

const char* Lab01Widget::FragmentCurveShaderSource =
    "void main() {\n"
    "    gl_FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
    "}\n";

Lab01Widget::Lab01Widget(QWidget* parent)
    : OpenGLWidget(parent) {

    const float STEP = 0.000001;
    const auto NUM_VERTICES = 2 * static_cast<long>(1.0 / STEP);

    CurveVertices.reserve(NUM_VERTICES);

    GLfloat x = 0.0f;
    for (int i = 0; i < NUM_VERTICES; i++) {
        auto y = std::sqrt(x * x * x / (2 - x));
        CurveVertices.push_back(x);
        CurveVertices.push_back(y);
        x += STEP;
    }
}

void Lab01Widget::initializeGL() {
    initializeOpenGLFunctions();

    AxesProgram = new QOpenGLShaderProgram(this);
    AxesProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, VertexShaderSource);
    AxesProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, FragmentAxesShaderSource);
    if (!AxesProgram->link()) {
        qDebug() << AxesProgram->log();
    }
    AxesPositionAttr = AxesProgram->attributeLocation("positionAttr");

    CurveProgram = new QOpenGLShaderProgram(this);
    CurveProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, VertexShaderSource);
    CurveProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, FragmentCurveShaderSource);
    if (!CurveProgram->link()) {
        qDebug() << CurveProgram->log();
    }
    CurvePositionAttr = CurveProgram->attributeLocation("positionAttr");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Lab01Widget::resizeGL(int width, int height) {}

void Lab01Widget::paintGL() {
    AxesProgram->bind();

    glVertexAttribPointer(AxesPositionAttr, 2, GL_FLOAT, GL_FALSE, 0, AxesVertices);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_LINES, 0, 4);

    glDisableVertexAttribArray(0);

    AxesProgram->release();

    CurveProgram->bind();

    glVertexAttribPointer(CurvePositionAttr, 2, GL_FLOAT, GL_FALSE, 0, CurveVertices.data());
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_LINE_STRIP, 0, CurveVertices.size() / 2);

    glDisableVertexAttribArray(0);

    CurveProgram->release();
}
