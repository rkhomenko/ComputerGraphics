#include <Lab01Widget.hpp>

#include <QDebug>

#include <cmath>

Lab01Widget::Lab01Widget(QWidget* parent)
    : OpenGLWidget(parent) {}

void Lab01Widget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

void Lab01Widget::resizeGL(int width, int height) {}

void Lab01Widget::paintGL() {
    const float delta = 0.00001;
    const float a = 0.3;

    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_POINT_SMOOTH);

    drawAxises();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (float x = 0.; x < a - delta; x += delta) {
        auto y = std::sqrt((x * x * x) / (a - x));
        glVertex2f(x, y);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for (float x = 0.; x < a - delta; x += delta) {
        auto y = - std::sqrt((x * x * x) / (a - x));
        glVertex2f(x, y);
    }
    glEnd();

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xFF);

    glBegin(GL_LINES);
    glVertex3f(a, -1.0, 0.0);
    glVertex3f(a, 1.0, 0.0);
    glEnd();

    glDisable(GL_LINE_STIPPLE);

    glFlush();
}

void Lab01Widget::drawAxises() {
    const auto width = this->width();
    const auto height = this->height();
    const auto step = 0.2f;

    auto k = (1.0 * height) / width;

    glColor3f(0, 0, 1.);
    glLineWidth(1.);

    // OX
    glBegin(GL_LINES);
    glVertex3f(-1.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glEnd();

    // OY
    glBegin(GL_LINES);
    glVertex3f(0.0, -1.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();

    glColor3f(0.752941, 0.752941, 0.752941);

    for (auto y = step; y <= 1.0; y += step) {
        glBegin(GL_LINES);
        glVertex3f(-1.0, y, 0.0);
        glVertex3f(1.0, y, 0.0);
        glEnd();
    }

    for (auto y = -step; y >= -1.0; y -= step) {
        glBegin(GL_LINES);
        glVertex3f(-1.0, y, 0.0);
        glVertex3f(1.0, y, 0.0);
        glEnd();
    }

    for (auto x = step; x < 1.0; x += step) {
        glBegin(GL_LINES);
        glVertex3f(x, -1.0, 0.0);
        glVertex3f(x, 1.0, 0.0);
        glEnd();
    }

    for (auto x = -step; x > -1.0; x -= step) {
        glBegin(GL_LINES);
        glVertex3f(x, -1.0, 0.0);
        glVertex3f(x, 1.0, 0.0);
        glEnd();
    }

    glFlush();
}
