#ifndef FSIN_H
#define FSIN_H

#include "function.h"

template <class number>
class TFsin : public TFunction<number>
{
    number* derivative;
    number* count(int n)
    {
        derivative = new number[n+1];
        for (int i = 0; i < n+1; i++)
        {
            if (i % 2 == 0)
                derivative[i] = sin(0);
            else if (i % 4 == 1)
                derivative[i] = cos(0);
            else if (i % 4 == 3)
                derivative[i] = (-1) * cos(0);
        }

        return derivative;
    }
public:
    TFsin(int n) : TFunction<number>(n, count(n)) {};
    ~TFsin() {delete [] derivative;}
    void draw(QPainter*, double, double, int);
};

template <class number>
void TFsin<number>::draw(QPainter* p, double start, double end, int deg)
{
    QPointF *points = new QPointF[deg];
    double step = (end - start) / (deg + 1);
    double scale = (310 - 10) / fabs(end - start);
    double center = 310 / 2;

    p->drawLine(0, center, center * 2, center);
    p->drawLine(center, 0, center, center * 2);

    p->setPen(Qt::black);
    QFont font("MS Shell Dlg 2", 10);
    p->setFont(font);
    p->drawText(QPoint(center * 2 - 10, center - 10), "x");
    p->drawText(QPoint(center - 15, 15), "y");


    for (int i = 0; i < deg; i++)
    {
        double x = start + i * step;
        double y = this->operator()(x);
        points[i] = QPointF(x * scale + center, (-1) * y * scale + center);
    }

    p->setPen(Qt::darkGreen);
    p->drawPolyline(points, deg);
    delete [] points;
}

#endif // FSIN_H

