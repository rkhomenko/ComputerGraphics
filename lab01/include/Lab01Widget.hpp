#ifndef CG_LABS_LAB01WIDGET_HPP_
#define CG_LABS_LAB01WIDGET_HPP_

#include <OpenGLWidget.hpp>

#include <vector>

class QOpenGLShaderProgram;

class Lab01Widget : public OpenGLWidget {
    Q_OBJECT

public:
    Lab01Widget(QWidget* parent = nullptr);

public slots:
    void OnVariablesChanged();

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

private:
    void SetVariables();

    static const auto RED = 0;
    static const auto BLUE = 1;
    static const auto GREY = 2;
    static const auto LIGHT_BLUE = 3;

    static const char* VertexShaderSource;
    static const char* FragmentShaderSource;

    GLfloat GetX(int x);
    GLfloat GetY(int y);

    void DrawLines(const std::vector<GLfloat> points);
    void DrawLine(const std::vector<GLfloat> points);
    int DrawAxesAndGrid(int num);
    void DrawAsymptote(int a);
    void DrawCurve(int a, int B, int step);

    QOpenGLShaderProgram* Program;
    GLuint PositionAttr, ColorUniform;
    std::vector<GLfloat> CurveVertices;
    int A;
    int B;
};

#endif // CG_LABS_LAB01WIDGET_HPP_
