#include <OpenGLWindow.hpp>

#include <QtWidgets>

OpenGLWindow::OpenGLWindow(QOpenGLWidget* widget) {
    Width = MIN_WIDTH;
    Height = MIN_HEIGHT;
    setMinimumSize(MIN_WIDTH, MIN_HEIGHT);

    widget->setParent(this);
    setCentralWidget(widget);
}
