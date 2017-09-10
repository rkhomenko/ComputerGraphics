#ifndef CG_LABS_LAB01WIDGET_HPP_
#define CG_LABS_LAB01WIDGET_HPP_

#include <OpenGLWidget.hpp>

#include <vector>

class QOpenGLShaderProgram;

class Lab01Widget : public OpenGLWidget {
public:
    Lab01Widget(QWidget* parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

private:
    static const auto NUM_VERTICES = 4;
    static const auto DIMENTION = 2;
    static const GLfloat AxesVertices[ NUM_VERTICES * DIMENTION];
    static const char* VertexShaderSource;
    static const char* FragmentAxesShaderSource;
    static const char* FragmentCurveShaderSource;

    QOpenGLShaderProgram* AxesProgram;
    QOpenGLShaderProgram* CurveProgram;
    GLuint AxesPositionAttr;
    GLuint CurvePositionAttr;
    std::vector<GLfloat> CurveVertices;
};

#endif // CG_LABS_LAB01WIDGET_HPP_
