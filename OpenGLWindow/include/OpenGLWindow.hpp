#ifndef CG_LABS_OPENGLWINDOW_HPP_
#define CG_LABS_OPENGLWINDOW_HPP_

#include <QMainWindow>

class QOpenGLWidget;

class OpenGLWindow : public QMainWindow {
    Q_OBJECT

public:
    OpenGLWindow(QOpenGLWidget* widget);

private:
    const int MIN_WIDTH = 640;
    const int MIN_HEIGHT = 480;

    int Width;
    int Height;
};

#endif // CG_LABS_OPENGLWINDOW_HPP_
