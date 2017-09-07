#include <OpenGLWidget.hpp>

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent) {}

void OpenGLWidget::setVariables(const OpenGLWidgetVariables& variables) {
    Variables = variables;
}

double OpenGLWidget::getVariable(const std::string& variableName) const {
    auto result = Variables.find(variableName);
    if (result == Variables.end()) {
        return 0;
    }
    return result->second;
}
