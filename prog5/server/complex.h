#ifndef COMPLEX_H
#define COMPLEX_H

#include <QString>
#include <iostream>
#include <math.h>
using namespace std;


class TComplex
{
    static QChar SEPARATOR;
    double real, imag;

public:
    TComplex();
    TComplex(const int&);
    TComplex(const double&, const double&);
    TComplex(const QByteArray&);

    void operator+= (TComplex c);
    TComplex operator-();
    TComplex operator- (TComplex c);
    TComplex operator* (TComplex num);
    TComplex operator/ (unsigned num);
    friend TComplex sqrt(TComplex c);
    friend TComplex pow(TComplex c, int st);
    bool operator> (TComplex c);
    bool operator< (TComplex c);

    double get_real(TComplex c);
    double get_imag(TComplex c);

    double fabs(TComplex c);

    static void setSeparator(QChar);

    friend ostream& operator << (ostream&, TComplex);
    friend istream& operator >> (istream&, TComplex&);

    friend QString& operator<<(QString&, TComplex);
    // QString& operator<<(QString& s, double);
    friend QByteArray& operator>>(QByteArray&, TComplex&);
    operator QString ();
};

#endif // COMPLEX_H
