#include <OpenGLWidget.hpp>

#include <QDebug>

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent) {}

void OpenGLWidget::setVariables(OpenGLWidgetVariables* variables) {
    if (Variables != nullptr) {
        delete Variables;
    }
    Variables = variables;
    emit VariablesChanged();
}

float OpenGLWidget::getVariable(const QString& variableName) const {
    auto result = Variables->find(variableName);
    if (result == Variables->end()) {
        return 0;
    }
    return result.value();
}

bool OpenGLWidget::isEmptyVariables() const {
    bool result = true;
    if (Variables != nullptr) {
        result = Variables->isEmpty();
    }
    return result;
}
