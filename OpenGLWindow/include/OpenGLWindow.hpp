#ifndef CG_LABS_OPENGLWINDOW_HPP_
#define CG_LABS_OPENGLWINDOW_HPP_

#include <QMainWindow>
#include <QList>
#include <QString>

class QOpenGLWidget;
class QLineEdit;

class OpenGLWindow : public QMainWindow {
    Q_OBJECT

public:
    OpenGLWindow(QOpenGLWidget* widget);
    void defineVariables(const QList<QString>& list);

private slots:
    void setVariables();

private:
    static const int MIN_WIDTH = 640;
    static const int MIN_HEIGHT = 480;

    void setTextEditParams();

    int Width;
    int Height;
    QLineEdit* LineEdit;
    QList<QString> Variables;
};

#endif // CG_LABS_OPENGLWINDOW_HPP_
