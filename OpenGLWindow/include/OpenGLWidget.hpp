#ifndef CG_LABS_OPENGLWIDGET_HPP_
#define CG_LABS_OPENGLWIDGET_HPP_

#include <OpenGLWidgetVariables.hpp>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QList>
#include <QString>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
public:
    OpenGLWidget(QWidget* parent = nullptr);

    void setVariables(const OpenGLWidgetVariables& variables);

protected:
    double getVariable(const std::string& variableName) const;

    virtual void initializeGL() = 0;
    virtual void resizeGL(int width, int height) = 0;
    virtual void paintGL() = 0;

private:
    OpenGLWidgetVariables Variables;
};

#endif  // CG_LABS_OPENGLWIDGET_HPP_
