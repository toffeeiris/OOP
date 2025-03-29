#include "interface.h"
#include <QFont>

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Работа №4");
    setFixedSize(650, 350);
    QFont font("MS Shell Dlg 2", 10);
    setFont(font);
    QRegularExpression dbl("^-?\[0-9]*(\.\[0-9]+)?");
    QRegularExpression deg("[0-9]");

    name_n = new QLabel("N =", this);
    name_n->setGeometry(20, 20, 50, 30);
    n = new QLineEdit("0", this);
    n->setGeometry(65, 20, 50, 30);
    n->setValidator(new QRegularExpressionValidator(deg, this));

    name_coef = new QLabel("a =", this);
    name_coef->setGeometry(20, 55, 40, 30);

    coef_re = new QLineEdit("1", this);
    coef_re->setGeometry(65, 55, 50, 30);
    coef_re->setValidator(new QRegularExpressionValidator(dbl, this));

    delimeter_coef = new QLabel(" + i", this);
    delimeter_coef->setGeometry(115, 55, 30, 30);

    coef_im = new QLineEdit("0", this);
    coef_im->setGeometry(150, 55, 50, 30);
    coef_im->setValidator(new QRegularExpressionValidator(dbl, this));

    name_point = new QLabel("x =", this);
    name_point->setGeometry(20, 90, 40, 30);
    point_re = new QLineEdit("1", this);
    point_re->setGeometry(65, 90, 50, 30);
    point_re->setValidator(new QRegularExpressionValidator(dbl, this));
    delimeter_point = new QLabel(" + i", this);
    delimeter_point->setGeometry(115, 90, 30, 30);
    point_im = new QLineEdit("0", this);
    point_im->setGeometry(150, 90, 50, 30);
    point_im->setValidator(new QRegularExpressionValidator(dbl, this));

    calculate_btn = new QPushButton("Вычислить полином в точке", this);
    calculate_btn->setGeometry(430, 20, 190, 30);
    canonic_btn = new QPushButton("Канонический вид", this);
    canonic_btn->setGeometry(250, 20, 170, 30);
    classic_btn = new QPushButton("Классический вид", this);
    classic_btn->setGeometry(250, 55, 170, 30);
    end_btn = new QPushButton("Завершить программу", this);
    end_btn->setGeometry(430, 55, 190, 30);

    output = new QTextEdit(this);
    output->setReadOnly(true);
    output->setGeometry(250, 90, 370, 240);

    connect(canonic_btn, SIGNAL(pressed()), this, SLOT(update_p()));
    connect(classic_btn, SIGNAL(pressed()), this, SLOT(update_p()));
    connect(canonic_btn, SIGNAL(pressed()), this, SLOT(print_canonic()));
    connect(classic_btn, SIGNAL(pressed()), this, SLOT(print_classic()));
    connect(calculate_btn, SIGNAL(pressed()), this, SLOT(value_in_point()));
    connect(n, SIGNAL(editingFinished()), this, SLOT(add_x()));
    connect(end_btn, SIGNAL(pressed()), this, SLOT(end()));

    scroll_x = new QScrollArea(this);
    scroll_x->setGeometry(10, 130, 210, 200);
    scroll_x->setWidgetResizable(true);

    container_x = new QWidget();
    layout_x = new QVBoxLayout(container_x);
    container_x->setLayout(layout_x);
    scroll_x->setWidget(container_x);
}

TInterface::~TInterface()
{
    delete name_coef;
    delete name_n;
    delete name_point;
    delete n;
    delete coef_re;
    delete coef_im;
    delete delimeter_coef;
    delete x_re;
    delete x_im;
    delete delimeter_x;
    delete point_re;
    delete point_im;
    delete delimeter_point;
    delete calculate_btn;
    delete canonic_btn;
    delete classic_btn;
    delete end_btn;
    delete output;
    delete scroll_x;
    delete container_x;
    delete layout_x;
    delete hLayout;
}

void TInterface::update_p()
{
    my_deg = int(n->text().toInt());
    my_coef = number(coef_re->text().toDouble(), coef_im->text().toDouble());
    p = TPolynom(my_coef, my_deg);

    for (int i = 0; i < my_deg; ++i)
    {
        QLayoutItem *item = layout_x->itemAt(i);
        if (item)
        {
            hLayout = qobject_cast<QHBoxLayout*>(item->layout());
            if (hLayout)
            {
                x_re = qobject_cast<QLineEdit*>(hLayout->itemAt(1)->widget());
                x_im = qobject_cast<QLineEdit*>(hLayout->itemAt(3)->widget());

                if (x_re && x_im)
                {
                    number x = number(x_re->text().toDouble(), x_im->text().toDouble());
                    p.add_root(i, x);
                }
            }
        }
    }


}

void TInterface::add_x()
{
    my_deg = int(n->text().toInt());
    QRegularExpression dbl("^-?\[0-9]*(\.\[0-9]+)?");

    if (curr_deg < my_deg)
    {
        for (int i = curr_deg; i < my_deg; ++i)
        {
            hLayout = new QHBoxLayout();
            QLabel *num = new QLabel(QString("%1:").arg(i + 1), container_x);
            x_re = new QLineEdit("1", container_x);
            x_re->setValidator(new QRegularExpressionValidator(dbl, this));
            delimeter_x = new QLabel(" + i", container_x);
            x_im = new QLineEdit("0", container_x);
            x_im->setValidator(new QRegularExpressionValidator(dbl, this));

            hLayout->addWidget(num);
            hLayout->addWidget(x_re);
            hLayout->addWidget(delimeter_x);
            hLayout->addWidget(x_im);
            layout_x->addLayout(hLayout);
        }
    }
    else if (curr_deg > my_deg)
    {
        QWidget *new_container_x = new QWidget();
        QVBoxLayout *new_layout_x = new QVBoxLayout(new_container_x);
        new_container_x->setLayout(new_layout_x);
        scroll_x->setWidget(new_container_x);

        container_x = new_container_x;
        layout_x = new_layout_x;
        hLayout = nullptr;

        for (int i = 0; i < my_deg; ++i)
        {
            hLayout = new QHBoxLayout();
            QLabel *num = new QLabel(QString("%1:").arg(i + 1), container_x);
            number my_x = p.get_root(i);

            if (!flag_print)
                x_re = new QLineEdit("1", container_x);
            else
                x_re = new QLineEdit(QString::number(my_x.get_real(my_x)), container_x);
            x_re->setValidator(new QRegularExpressionValidator(dbl, this));
            delimeter_x = new QLabel(" + i", container_x);
            if (!flag_print)
                x_im = new QLineEdit("0", container_x);
            else
                x_im = new QLineEdit(QString::number(my_x.get_imag(my_x)), container_x);
            x_im->setValidator(new QRegularExpressionValidator(dbl, this));
            hLayout->addWidget(num);
            hLayout->addWidget(x_re);
            hLayout->addWidget(delimeter_x);
            hLayout->addWidget(x_im);
            layout_x->addLayout(hLayout);
        }
    }

    curr_deg = my_deg;

    container_x->adjustSize();
    scroll_x->show();
}

void TInterface::print_canonic()
{
    output->clear();
    flag_print = true;
    if (my_deg == 0)
    {
        QString s = "Сначала создайте полином!";
        output->setPlainText(s);
    }
    else
    {
        p.set_type(1);
        QString s;
        s << p;
        output->setPlainText(s);
    }
}

void TInterface::print_classic()
{
    output->clear();
    flag_print = true;
    if (my_deg == 0)
    {
        QString s = "Сначала создайте полином!";
        output->setPlainText(s);
    }
    else
    {
        p.set_type(0);
        QString s;
        s << p;
        output->setPlainText(s);
    }
}

void TInterface::value_in_point()
{
    output->clear();
    update_p();
    my_coef = number(point_re->text().toDouble(), point_im->text().toDouble());
    QString result;
    if (my_deg == 0)
    {
        output->setText("Сначала создайте полином!");
    }
    else
    {
        number rez = p.value_in_point(my_coef);
        output->setText(result << rez);
    }
}

void TInterface::end()
{
    exit(0);
}
