#include <Lab01Widget.hpp>

#include <QDebug>
#include <QOpenGLShaderProgram>

#include <cmath>

Lab01Widget::Lab01Widget(QWidget* parent)
    : OpenGLWidget(parent) {}

void Lab01Widget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Lab01Widget::resizeGL(int width, int height) {}

void Lab01Widget::paintGL() {
    drawAxises();
}

void Lab01Widget::drawAxises() {
    const auto AXES_NUM = 2;
    const auto DIMENTION = 2;
    const auto POINTS_NUM = 2;
    const auto OX_INDEX = 0;
    const auto OY_INDEX = 1;
    const auto X_INDEX = 0;
    const auto Y_INDEX = 0;
    const GLfloat axesVertices[] = {
        -1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, -1.0f,
        0.0f,  1.0f
    };
    const GLfloat axesColors[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };
    const char* vertexShader =
        "attribute highp vec4 positionAttr;\n"
        "attribute lowp vec4 colorAttr;\n"
        "varying lowp vec4 color;\n"
        "void main() {\n"
        "    color = colorAttr;\n"
        "    gl_Position = positionAttr;\n"
        "}\n";
    const char* fragmentShader =
        "varying lowp vec4 color;\n"
        "void main() {\n"
        "    gl_FragColor = color;\n"
        "}\n";

    GLuint positionAttr, colorAttr;
    auto program = new QOpenGLShaderProgram(this);
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShader);
    program->link();
    qDebug() << program->log();
    positionAttr = program->attributeLocation("positionAttr");
    colorAttr = program->attributeLocation("colorAttr");

    program->bind();

    glVertexAttribPointer(positionAttr, 2, GL_FLOAT, GL_FALSE, 0, axesVertices);
    glVertexAttribPointer(colorAttr, 3, GL_FLOAT, GL_FALSE, 0, axesColors);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_LINES, 0, 4);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    program->release();
}
