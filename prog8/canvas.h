#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include "fsin.h"
#include "fsi.h"

class TCanvas : public QWidget
{
    Q_OBJECT
    const int f_sin = 1;
    const int f_Si = 2;

    int deg, mode;
    double d1, d2;


public:
    explicit TCanvas(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;

public slots:
    void set_func(int, double, double, const int);
};

#endif // CANVAS_H
