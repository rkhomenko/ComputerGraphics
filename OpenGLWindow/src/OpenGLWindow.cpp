#include <OpenGLWindow.hpp>

#include <QtWidgets>
#include <QRegExp>
#include <QRegExpValidator>
#include <QDebug>

#include <random>
#include <unordered_map>

OpenGLWindow::OpenGLWindow(QOpenGLWidget* openGLWidget) {
    const char* regexStr =
        "(\\s*([a-zA-Z]{1,6})\\s*=\\s*(\\d{1,6}(\\.\\d{1,6})?)\\s*;)+";

    Width = MIN_WIDTH;
    Height = MIN_HEIGHT;
    setMinimumSize(MIN_WIDTH, MIN_HEIGHT);

    auto layout = new QVBoxLayout;

    QRegExp rx(regexStr);
    auto validator = new QRegExpValidator(rx);

    LineEdit = new QLineEdit;
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
    std::unordered_map<std::string, double> map;
    for (const auto& line : lines) {
        auto match = re.match(line);
        if (match.hasMatch()) {
            map.insert(
                std::make_pair(
                    match.captured(1).toStdString(),
                    match.captured(2).toDouble()
                )
            );
        }
    }
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
