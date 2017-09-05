#include <OpenGLWidget.hpp>

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent) {}

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void OpenGLWidget::resizeGL(int width, int height) {}

void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
}
