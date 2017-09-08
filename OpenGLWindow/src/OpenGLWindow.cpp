#include <OpenGLWindow.hpp>
#include <OpenGLWidget.hpp>
#include <OpenGLWidgetVariables.hpp>

#include <QtWidgets>
#include <QRegExp>
#include <QRegExpValidator>
#include <QDebug>

#include <random>

OpenGLWindow::OpenGLWindow(QOpenGLWidget* openGLWidget) {
    const char* regexStr =
        "(\\s*([a-zA-Z]{1,6})\\s*=\\s*(\\d{1,6}(\\.\\d{1,6})?)\\s*;)+";

    Width = MIN_WIDTH;
    setMinimumSize(MIN_WIDTH, MIN_HEIGHT);

    auto layout = new QVBoxLayout;

    QRegExp rx(regexStr);
    auto validator = new QRegExpValidator(rx);

    LineEdit = new QLineEdit;
    LineEdit->setFixedWidth(MIN_WIDTH / 2);
    LineEdit->setValidator(validator);
    connect(LineEdit, &QLineEdit::returnPressed, this, &OpenGLWindow::setVariables);

    layout->addWidget(LineEdit);
    layout->addWidget(openGLWidget);

    auto widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
}

void OpenGLWindow::setVariables() {
    const char* regexStr = "([a-zA-Z]{1,6})=(\\d{1,6}(\\.\\d{1,6})?)";
    const auto SPACE = QChar(' ');
    const auto SEP = QChar(';');

    if (!LineEdit->hasAcceptableInput()) {
        qDebug() << "No acceptable input in LineEdit!";
    }

    auto input = LineEdit->displayText();
    input.remove(SPACE, Qt::CaseInsensitive);

    auto lines = input.split(SEP);
    QRegularExpression re(regexStr);
    OpenGLWidgetVariables variables;
    for (const auto& line : lines) {
        auto match = re.match(line);
        if (match.hasMatch()) {
            auto variableName = match.captured(1);
            auto variableValue = match.captured(2);
            if (Variables.indexOf(variableName) < 0) {
                qDebug() << "Undefined variable " << variableName << "!";
                return;
            }
            variables.insert(
                std::make_pair(
                    variableName.toStdString(),
                    variableValue.toDouble()
                )
            );
        }
    }

    Widget->setVariables(variables);
}

void OpenGLWindow::defineVariables(const QList<QString>& list) {
    const double BEGIN = 0.;
    const double END = 2.;
    std::uniform_real_distribution<double> unif(BEGIN, END);
    std::random_device rd;
    std::default_random_engine re(rd());

    QString variablesExample = "";
    for (auto& var : list) {
        variablesExample += var + " = " + QString::number(unif(re), 'f', 2) + "; ";
    }

    LineEdit->setPlaceholderText(variablesExample);
    Variables = list;
}
