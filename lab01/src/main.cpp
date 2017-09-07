#include <OpenGLWindow.hpp>
#include <OpenGLWidget.hpp>

#include <QApplication>
#include <QSurfaceFormat>

#include <initializer_list>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Khomenko and Co");
    QCoreApplication::setApplicationName("Computer Graphics Lab01");

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    auto widget = new OpenGLWidget();

    OpenGLWindow window(widget);
    window.defineVariables({ "a", "B"});
    window.show();
    return app.exec();
}
