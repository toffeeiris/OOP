#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QRegularExpression>
#include <QRadioButton>
#include <QPushButton>
#include <QMessageBox>

#include "canvas.h"

class TInterface : public QWidget
{
    Q_OBJECT


    QLabel *name_n, *range, *delimeter, *bracket;
    QLineEdit *n, *limit_1, *limit_2;

    QRadioButton *sin_mode, *int_sin_mode;
    QPushButton *create;
    TCanvas *canvas;


public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();


public slots:
    void print_result();

};

#endif // TINTERFACE_H
