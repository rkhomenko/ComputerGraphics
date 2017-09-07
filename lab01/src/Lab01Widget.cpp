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
    using Point = float[2];

    Point p1 = { 0., 0. };
    Point p2 = { 0., 0. };

    glClear(GL_COLOR_BUFFER_BIT);
    float delta = 0.001;
    float a = 1.;

    auto width = static_cast<float>(this->width());
    auto height = static_cast<float>(this->height());

    glColor3f(0.0, 0.0, 1.0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex3f(-1. * width / 2., 0., 0.);
    glVertex3f(width / 2., 0., 0.);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0., -1. * height / 2, 0.);
    glVertex3f(0., height / 2, 0.);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    for (float x = 0.; x < a - delta; x += delta) {
        p1[0] = p2[0] = x;
        p1[1] = std::sqrt((x * x * x) / (a - x));
        p2[1] = -p1[1];

        glBegin(GL_POINTS);
        glVertex2fv(p1);
        glVertex2fv(p2);
        glEnd();
    }
    glFlush();
}
