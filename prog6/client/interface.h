#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QDoubleValidator>
#include <QRegularExpression>

class TInterface : public QWidget
{
    Q_OBJECT

    int my_deg = 0, curr_deg = 0;
    int last_mode, curr_mode;

    QLabel *name_n, *name_coef, *delimeter_coef, *delimeter_x, *name_point, *delimeter_point, *mode;
    QLineEdit *n, *coef_re, *coef_im, *x_re, *x_im, *point_re, *point_im;

    QPushButton *calculate_btn, *canonic_btn, *classic_btn, *end_btn;
    QRadioButton *d_mode, *c_mode;

    QTextEdit *output;

    QScrollArea *scroll_x;
    QWidget *container_x;
    QVBoxLayout *layout_x;
    QHBoxLayout *hLayout;

public:
    TInterface(QWidget *parent = 0);
    ~TInterface();

public slots:
    void answer(QString);
    void update_p(QString);
    void add_x();
    // void print_canonic();
    // void print_classic();
    // void value_in_point();
    // void end();

private slots:
    void formRequest();

signals:
    void request(QString);

};

#endif // INTERFACE_H
