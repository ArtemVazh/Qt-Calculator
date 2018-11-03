#ifndef CALCULATOR_H
#define CALCULATOR_H


#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QStackedLayout>
#include <cstdlib>

namespace Ui {
class Calculator;

}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();
private slots:
    void PushButtonClicked();
    void Mode();
private:
    bool type; //1 - binary, 0 - unary
    QString expression;
    QString currentnumber;
    QGroupBox *Common;
    QGroupBox *Engineering;
    QStackedLayout *CalculatorMode;
    QPushButton* createButton (const QString& str, int x = 50, int y = 50);
    void Calculate(bool type);
    void CreateCommonMode();
    void CreateEngineeringMode();
    Ui::Calculator *ui;
};

#endif // CALCULATOR_H
