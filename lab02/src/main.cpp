#include <Lab02MainWindow.hpp>

#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Khomenko and Co");
    QCoreApplication::setApplicationName("Computer Graphics Lab02");

    Lab02MainWindow window;
    window.show();

    return app.exec();
}
