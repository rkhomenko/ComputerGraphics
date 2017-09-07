#include <Lab01Widget.hpp>

Lab01Widget::Lab01Widget(QWidget* parent)
    : OpenGLWidget(parent) {}

void Lab01Widget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void Lab01Widget::resizeGL(int width, int height) {}

void Lab01Widget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
}
