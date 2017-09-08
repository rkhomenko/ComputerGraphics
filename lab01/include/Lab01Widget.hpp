#ifndef CG_LABS_LAB01WIDGET_HPP_
#define CG_LABS_LAB01WIDGET_HPP_

#include <OpenGLWidget.hpp>

class Lab01Widget : public OpenGLWidget {
public:
    Lab01Widget(QWidget* parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

private:
    void drawAxises();
};

#endif // CG_LABS_LAB01WIDGET_HPP_
