#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QDoubleValidator>
#include <QRegularExpression>
#include <QRadioButton>

#include "fsi.h"
#include "fsin.h"
#include "complex.h"

class TInterface : public QWidget
{
    Q_OBJECT


    QLabel *name_n, *name_point, *delimeter_point;
    QLineEdit *n, *point_re, *point_im;

    QRadioButton *sin_mode, *int_sin_mode;
    QTextEdit *output;


public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();


public slots:
    void print_result();

};

#endif // TINTERFACE_H
