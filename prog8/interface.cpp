#include "interface.h"
#include <QFont>

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Работа №8");
    setFixedSize(340, 445);
    QFont font("MS Shell Dlg 2", 10);
    setFont(font);
    QRegularExpression dbl("^-?\[0-9]*(\.\[0-9]+)?");
    QRegularExpression deg("[0-9]+");

    name_n = new QLabel("N =", this);
    name_n->setGeometry(20, 20, 30, 30);
    n = new QLineEdit("10", this);
    n->setGeometry(55, 20, 50, 30);
    n->setValidator(new QRegularExpressionValidator(deg, this));

    range = new QLabel("Диапазон: [", this);
    range->setGeometry(120, 20, 70, 30);

    limit_1 = new QLineEdit("", this);
    limit_1->setGeometry(195, 20, 50, 30);
    limit_1->setValidator(new QRegularExpressionValidator(dbl, this));

    delimeter = new QLabel(";", this);
    delimeter->setGeometry(250, 20, 5, 30);

    limit_2 = new QLineEdit("", this);
    limit_2->setGeometry(260, 20, 50, 30);
    limit_2->setValidator(new QRegularExpressionValidator(dbl, this));

    bracket = new QLabel("]", this);
    bracket->setGeometry(315, 20, 20, 30);

    sin_mode = new QRadioButton("функция sin(x)", this);
    sin_mode->setGeometry(20, 55, 135, 30);
    int_sin_mode = new QRadioButton("функция Si(x)", this);
    int_sin_mode->setGeometry(20, 90, 135, 30);
    create = new QPushButton("Нарисовать график", this);
    create->setGeometry(150, 55, 170, 65);

    canvas = new TCanvas(this);
    canvas->move(20, 125);

    connect(create, SIGNAL(pressed()), this, SLOT(print_result()));
}

TInterface::~TInterface()
{
    delete name_n;
    delete n;
    delete range;
    delete delimeter;
    delete bracket;
    delete limit_1;
    delete limit_2;
    delete sin_mode;
    delete int_sin_mode;
    delete create;
    delete canvas;
}


void TInterface::print_result()
{
    int my_n = int(n->text().toInt());

    if (limit_1->text() == "" || limit_2->text() == "")
    {
        QMessageBox::information(this, "Ошибка", "Вы не ввели все значения диапазона!");
    }
    else if (limit_1->text().toDouble() >= limit_2->text().toDouble())
    {
        QMessageBox::information(this, "Ошибка", "Некорректный диапазон!");
    }
    else if (fabs(limit_2->text().toDouble() - limit_1->text().toDouble()) <= 5)
    {
        QMessageBox::information(this, "Ошибка", "Увеличте диапазон чтобы лучше рассмотреть график!");
    }
    else if (!(sin_mode->isChecked()) && !(int_sin_mode->isChecked()))
    {
        QMessageBox::information(this, "Ошибка", "Вы не выбрали функцию!");
    }
    else if (my_n < 7 || my_n > 20)
    {
        QMessageBox::information(this, "Ошибка", "Рекомендуется выбирать степень разложения от 7 до 20 для корректного отображения!");
    }
    else
    {
        const int f_sin = 1;
        const int f_Si = 2;

        if (sin_mode->isChecked())
            canvas->set_func(my_n, limit_1->text().toDouble(), limit_2->text().toDouble(), f_sin);
        else if (int_sin_mode->isChecked())
            canvas->set_func(my_n, limit_1->text().toDouble(), limit_2->text().toDouble(), f_Si);
    }
}




