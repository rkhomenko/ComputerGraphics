#include <Canvas.hpp>

#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Khomenko and Co");
    QCoreApplication::setApplicationName("Computer Graphics Lab01");

    Canvas canvas;
    canvas.show();
    return app.exec();
}
