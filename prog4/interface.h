#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QDoubleValidator>
#include <QRegularExpression>

#include "polynom.h"

class TInterface : public QWidget
{
    Q_OBJECT
    int my_deg = 0, curr_deg = 0;
    bool flag_print = false;
    number my_coef;
    TPolynom p;

    QLabel *name_n, *name_coef, *delimeter_coef, *delimeter_x, *name_point, *delimeter_point;
    QLineEdit *n, *coef_re, *coef_im, *x_re, *x_im, *point_re, *point_im;

    QPushButton *calculate_btn, *canonic_btn, *classic_btn, *end_btn;

    QTextEdit *output;

    QScrollArea *scroll_x;
    QWidget *container_x;
    QVBoxLayout *layout_x;
    QHBoxLayout *hLayout;


public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();


public slots:
    void add_x();
    void update_p();
    void print_canonic();
    void print_classic();
    void value_in_point();
    void end();

};
#endif // TINTERFACE_H
