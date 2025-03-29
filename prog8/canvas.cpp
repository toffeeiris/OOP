#include "canvas.h"

TCanvas::TCanvas(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(310,310);
}


void TCanvas::set_func(int my_deg, double my_d1, double my_d2, const int my_mode)
{
    deg = my_deg;
    d1 = my_d1;
    d2 = my_d2;
    mode = my_mode;
    update();
}


void TCanvas::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    p.begin(this);
    if (mode == f_sin)
    {
        TFsin<double> exp(deg);
        exp.draw(&p, d1, d2, deg);
    }
    else if (mode == f_Si)
    {
        TFSi<double> exp(deg);
        exp.draw(&p, d1, d2, deg);
    }
    p.end();
}
