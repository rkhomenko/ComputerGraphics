#ifndef CG_LABS_OPENGLWIDGET_HPP_
#define CG_LABS_OPENGLWIDGET_HPP_

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
public:
    OpenGLWidget(QWidget* parent = nullptr);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
};

#endif  // CG_LABS_OPENGLWIDGET_HPP_
