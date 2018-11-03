#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->radioButton->setChecked(true);
    ui->radioButton->setText("Обычный");
    ui->radioButton_2->setText("Инженерный");
    connect(ui->radioButton, SIGNAL(clicked()), this, SLOT(Mode()));
    connect(ui->radioButton_2, SIGNAL(clicked()), this, SLOT(Mode()));
    ui->lineEdit->setText("0");
    ui->lineEdit->setAlignment(Qt::AlignRight);
    ui->lineEdit->setFixedHeight(50);
    ui->lineEdit->setStyleSheet(
                "QLineEdit{"
                "background-color: rgb(245, 245, 245);"
                "border-radius: 5px;"
                "border: 3px solid navy;}"
                "QLineEdit:hover{"
                "background-color: rgb(232,232,232);} "
                );
    ui->lineEdit->setReadOnly(true);
    CalculatorMode = new QStackedLayout;
    Mode();
    ui->centralWidget->setLayout(CalculatorMode);
}

Calculator::~Calculator()
{
    delete ui;
    delete CalculatorMode;
    delete Common;
    delete Engineering;
}

void Calculator::Mode(){
    if(ui->radioButton->isChecked()) {
        this->setWindowTitle("Калькулятор (обычный)");
        this->setFixedSize(300, 380);
        CreateCommonMode();
        CalculatorMode->addWidget(Common);
        CalculatorMode->setCurrentWidget(Common);
    }
    if(ui->radioButton_2->isChecked()) {
        this->setWindowTitle("Калькулятор (инженерный)");
        this->setFixedSize(530, 380);
        CreateEngineeringMode();
        CalculatorMode->addWidget(Engineering);
        CalculatorMode->setCurrentWidget(Engineering);
    }
}

void Calculator::CreateCommonMode() {
    QChar numbers[3][3] = {
        {'7', '8', '9'},
        {'4', '5', '6'},
        {'1', '2', '3'}
    };
    QChar operations[4] = {'/', '*', '-', '+'};
    QGridLayout *layoutrb = new QGridLayout;
    layoutrb->addWidget(ui->radioButton, 0, 0);
    layoutrb->addWidget(ui->radioButton_2, 1, 0);
    layoutrb->setContentsMargins(5, 5, 0, 5);
    QGroupBox *radiobuttons = new QGroupBox;
    radiobuttons->setLayout(layoutrb);
    radiobuttons->setFixedSize(224, 50);
    radiobuttons->setStyleSheet(
                "QGroupBox{"
                "border-radius: 2px;"
                "border: 3px double navy;}"
                "QRadioButton:hover{"
                "background-color: rgb(252,252,252);} "
                "QRadioButton:pressed  {"
                "background-color: rgb(222,222,222); } "
                );
    QGridLayout *MainLayout = new QGridLayout;
    MainLayout->addWidget(ui->lineEdit, 0, 0, 1, 5);
    MainLayout->addWidget(radiobuttons, 1, 0, 1, 4);
    MainLayout->addWidget(createButton("C"), 1, 4);
    for (int i = 0; i < 3; ++i) {
         for (int j = 0; j < 3; ++j) {
             MainLayout->addWidget(createButton(numbers[i][j]), i + 2, j);
         }
    }
    for (int i = 0; i < 4; ++i) {
        MainLayout->addWidget(createButton(operations[i]), i + 2, 3);
    }
    MainLayout->addWidget(createButton("0", 105, 50), 5, 0, 1, 2);
    MainLayout->addWidget(createButton("."), 5, 2);
    MainLayout->addWidget(createButton("√"), 2, 4);
    MainLayout->addWidget(createButton("1/x"), 3, 4);
    MainLayout->addWidget(createButton("=", 50, 105), 4, 4, 2, 1);
    Common = new QGroupBox;
    Common->setLayout(MainLayout);
    Common->setStyleSheet(
                "QGroupBox{"
                "border: 0px;}"
                );
}

void Calculator::CreateEngineeringMode() {
    QChar numbers[3][3] = {
        {'7', '8', '9'},
        {'4', '5', '6'},
        {'1', '2', '3'}
    };
    QChar operations[4] = {'/', '*', '-', '+'};
    QGridLayout *layoutrb = new QGridLayout;
    layoutrb->addWidget(ui->radioButton, 0, 0);
    layoutrb->addWidget(ui->radioButton_2, 1, 0);
    layoutrb->setContentsMargins(5, 5, 0, 5);
    QGroupBox *radiobuttons = new QGroupBox;
    radiobuttons->setLayout(layoutrb);
    radiobuttons->setFixedSize(454, 50);
    radiobuttons->setStyleSheet(
                "QGroupBox{"
                "border-radius: 2px;"
                "border: 3px double navy;"
                "padding: 0px 0px 0px 0px;}"
                "QRadioButton:hover{"
                "background-color: rgb(252,252,252);} "
                "QRadioButton:pressed  {"
                "background-color: rgb(222,222,222); } "
                );
    QGridLayout *MainLayout = new QGridLayout;
    MainLayout->addWidget(ui->lineEdit, 0, 0, 1, 9);
    MainLayout->addWidget(radiobuttons, 1, 0, 1, 8);
    MainLayout->addWidget(createButton("C"), 1, 8);
    for (int i = 0; i < 3; ++i) {
         for (int j = 0; j < 3; ++j) {
             MainLayout->addWidget(createButton(numbers[i][j]), i + 2, j + 4);
         }
    }
    for (int i = 0; i < 4; ++i) {
        MainLayout->addWidget(createButton(operations[i]), i + 2, 7);
    }
    MainLayout->addWidget(createButton("0", 105, 50), 5, 4, 1, 2);
    MainLayout->addWidget(createButton("."), 5, 6);
    MainLayout->addWidget(createButton("√"), 2, 8);
    MainLayout->addWidget(createButton("1/x"), 3, 8);
    MainLayout->addWidget(createButton("=", 50, 105), 4, 8, 2, 1);
    QGridLayout *EngineeringButtons = new QGridLayout;
    QString symbols[4][4] = {
        {"sinh", "sin", "exp", "x²"},
        {"cosh", "cos", "ln", "x³"},
        {"tanh", "tan", "log", "x"},
        {"n!", "pi", "3√", "y√"}
    };
    for (int i = 0; i < 4; ++i) {
         for (int j = 0; j < 4; ++j) {
             EngineeringButtons->addWidget(createButton(symbols[i][j]), i, j);
         }
    }
    EngineeringButtons->setContentsMargins(0, 0, 0, 0);
    QGroupBox *EngineeringSymbols = new QGroupBox;
    EngineeringSymbols->setStyleSheet(
                "QGroupBox{"
                "border: 0px;}"
                );
    EngineeringSymbols->setContentsMargins(0, 0, 0, 0);
    EngineeringSymbols->setLayout(EngineeringButtons);
    MainLayout->addWidget(EngineeringSymbols, 2, 0, 4, 4);
    Engineering = new QGroupBox;
    Engineering->setStyleSheet(
                "QGroupBox{"
                "border: 0px;"
                "padding: -2px 0px -4px 0px;}"
                );
    Engineering->setLayout(MainLayout);
    Engineering->setContentsMargins(0, 0, 0, 0);
}

QPushButton* Calculator::createButton (const QString& operation, int x, int y) {
    QPushButton* button = new QPushButton(operation);
    button->setFixedSize(x, y);
    connect(button, SIGNAL(clicked()), this, SLOT(PushButtonClicked()));
    button->setStyleSheet(
                "QPushButton{"
                "font: 15px bold;"
                "background-color: rgb(245, 245, 245);"
                "border-radius: 3px;"
                "border: 1px solid navy;}"
                "QPushButton:hover{"
                "background-color: rgb(232,232,232);} "
                "QPushButton:pressed  {"
                "background-color: rgb(190,190,190); } "
                );
    return button;
}

void Calculator::PushButtonClicked(){
    QString operation = ((QPushButton*)sender())->text();
    QVector <QString> trigonometry = {"sinh", "sin", "exp", "cosh", "cos", "ln", "tanh", "tan", "log", "sin"};
    QVector <QString> unaryoperation = {"1/x", "x²", "x³", "x", "n!"};
    QVector <QString> binaryoperation = {"/", "+", "-", "*"};
    if (operation == "C") {
        ui->lineEdit->setText("0");
        expression.clear();
        currentnumber.clear();
        return;
    }
    if (binaryoperation.contains(operation)) {
        if (currentnumber.isEmpty() && operation == "-"){
            currentnumber += operation;
            expression += currentnumber;
            ui->lineEdit->setText(expression);
            return;
        }
        type = true;
        currentnumber.clear();
        expression += operation;
        ui->lineEdit->setText(expression);
        return;
    }
    if (operation == "=") {
        Calculate(type);
        return;
    }
    if (trigonometry.contains(operation) || operation == "√" || operation == "3√") {
        type = false;
        if (!currentnumber.isEmpty()){
            expression.clear();
            expression += operation + currentnumber;
            Calculate(type);
            return;
        }
        ui->lineEdit->setText(operation);
        currentnumber.clear();
        expression.clear();
        expression += operation;
        return;
    }
    if (operation == "y√") {
        type = false;
        expression += "√";
        ui->lineEdit->setText(expression);
        currentnumber.clear();
        return;
    }
    if (unaryoperation.contains(operation)){
        if(operation == "1/x" && currentnumber.isEmpty()) {
            ui->lineEdit->setText("error");
            return;
        }
        else if (operation == "1/x" && !currentnumber.isEmpty()){
            expression = "1/" + currentnumber;
            Calculate(true);
            return;
        }
        if(operation == "x²") {
            type = true;
            if (!currentnumber.isEmpty()){
                expression = currentnumber + "^2";
                currentnumber = "2";
                Calculate(type);
                return;
            }
            expression += "^2";
            ui->lineEdit->setText(expression);
            currentnumber = "2";
            return;
        }
        if(operation == "x³") {
            type = true;
            if (!currentnumber.isEmpty()){
                expression = currentnumber + "^3";
                currentnumber = "3";
                Calculate(type);
                return;
            }
            expression += "^3";
            ui->lineEdit->setText(expression);
            currentnumber = "3";
            return;
        }
        if(operation == "x") {
            type = true;
            expression += "^";
            ui->lineEdit->setText(expression);
            currentnumber.clear();
            return;
        }
        if(operation == "n!") {
            type = false;
            if (!currentnumber.isEmpty()){
                expression = currentnumber + "!";
                Calculate(type);
                return;
            }
            expression += "!";
            ui->lineEdit->setText(expression);
            return;
        }
        return;
    }
    if (operation.contains(QRegExp("[0-9]")) || operation == ".") {
        currentnumber += operation;
        expression += operation;
        ui->lineEdit->setText(expression);
        return;
    }
    if (operation == "pi") {
        currentnumber += "3.14159";
        expression += "3.14159";
        ui->lineEdit->setText(expression);
        return;
    }
}

double fact(int N)
{
    if(N < 0)
        return 0;
    if (N == 0)
        return 1;
    else
        return N * fact(N - 1);
}

void Calculator::Calculate(bool type){
    double result;
    if(type == true) {
        QString number1 = expression.left(expression.size() - currentnumber.size() - 1);
        QString number2 = expression.right(currentnumber.size());
        double value1 = number1.toDouble();
        double value2 = number2.toDouble();
        if (expression[expression.size() - currentnumber.size() - 1] == "+")
            result = value1 + value2;
        if (expression[expression.size() - currentnumber.size() - 1] == "*")
            result = value1 * value2;
        if (expression[expression.size() - currentnumber.size() - 1] == "/" && value2 != 0)
            result = value1 / value2;
        else if (expression[expression.size() - currentnumber.size() - 1] == "/" && value2 == 0) {
            ui->lineEdit->setText("error");
            return;
        }
        if (expression[expression.size() - currentnumber.size() - 1] == "-")
            result = value1 - value2;
        if (expression[expression.size() - currentnumber.size() - 1] == "^")
            result = pow(value1, value2);
    }
    else {
        QString operation = expression.left(expression.size() - currentnumber.size());
        QString number = expression.right(currentnumber.size());
        double value = number.toDouble();
        if (operation == "sin") {
            result = sin(value);
        }
        if (operation == "cos") {
            result = cos(value);
        }
        if (operation == "tan") {
            result = tan(value);
        }
        if (operation == "ln") {
            result = log(value);
        }
        if (operation == "sinh") {
            result = sinh(value);
        }
        if (operation == "cosh") {
            result = cosh(value);
        }
        if (operation == "tanh") {
            result = tanh(value);
        }
        if (operation == "exp") {
            result = exp(value);
        }
        if (operation == "log") {
            result = log2(value);
        }
        if (expression.contains("!")) {
            result = fact((expression.left(expression.size() - 1)).toDouble());
        }
        if (operation == "3√") {
            result = pow(value, 1.0/3.0);
        }
        else if (operation == "√" && value >= 0) {
            result = sqrt(value);
        }
        else if (operation.contains("√")) {
            QString power = operation.left(operation.size() - 1);
            if((power.toInt() % 2) == 0 && value < 0) {
                ui->lineEdit->setText("error");
                return;
            }
            result = pow(value, 1.0/(power.toDouble()));
        }
    }
    currentnumber.clear();
    expression.clear();
    currentnumber = QString("%1").arg(result, 0, 'g', 10);
    expression += currentnumber;
    ui->lineEdit->setText(currentnumber);
}
