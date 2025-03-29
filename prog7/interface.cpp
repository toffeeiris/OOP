#include "interface.h"
#include <QFont>

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Работа №7");
    setFixedSize(560, 180);
    QFont font("MS Shell Dlg 2", 10);
    setFont(font);
    QRegularExpression dbl("^-?\[0-9]*(\.\[0-9]+)?");
    QRegularExpression deg("[0-9]+");

    name_n = new QLabel("N =", this);
    name_n->setGeometry(20, 20, 50, 30);
    n = new QLineEdit("0", this);
    n->setGeometry(65, 20, 50, 30);
    n->setValidator(new QRegularExpressionValidator(deg, this));

    name_point = new QLabel("x =", this);
    name_point->setGeometry(20, 55, 40, 30);

    point_re = new QLineEdit("1", this);
    point_re->setGeometry(65, 55, 50, 30);
    point_re->setValidator(new QRegularExpressionValidator(dbl, this));

    delimeter_point = new QLabel(" + i", this);
    delimeter_point->setGeometry(115, 55, 30, 30);

    point_im = new QLineEdit("0", this);
    point_im->setGeometry(150, 55, 50, 30);
    point_im->setValidator(new QRegularExpressionValidator(dbl, this));

    sin_mode = new QRadioButton("функция sin(x)", this);
    sin_mode->setGeometry(20, 95, 150, 30);
    int_sin_mode = new QRadioButton("функция Si(x)", this);
    int_sin_mode->setGeometry(20, 130, 150, 30);


    output = new QTextEdit(this);
    output->setReadOnly(true);
    output->setGeometry(220, 20, 320, 140);

    connect(n, SIGNAL(editingFinished()), this, SLOT(print_result()));
    connect(point_re, SIGNAL(editingFinished()), this, SLOT(print_result()));
    connect(point_im, SIGNAL(editingFinished()), this, SLOT(print_result()));
    connect(sin_mode, SIGNAL(pressed()), this, SLOT(print_result()));
    connect(int_sin_mode, SIGNAL(pressed()), this, SLOT(print_result()));

}

TInterface::~TInterface()
{
    delete name_n;
    delete name_point;
    delete delimeter_point;
    delete n;
    delete point_re;
    delete point_im;
    delete sin_mode;
    delete int_sin_mode;
    delete output;
}


void TInterface::print_result()
{
    output->clear();
    int my_n = int(n->text().toInt());
    TComplex my_point = TComplex(point_re->text().toDouble(), point_im->text().toDouble());
    QString s;
    if (sin_mode->isChecked())
    {
        TFsin<TComplex> exp1(my_n);
        s << exp1(my_point);
        output->setPlainText(s);
    }
    else if (int_sin_mode->isChecked())
    {
        TFSi<TComplex> exp2(my_n);
        s << exp2(my_point);
        output->setPlainText(s);
    }
}




