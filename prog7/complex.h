#ifndef COMPLEX_H
#define COMPLEX_H

#include <QString>
#include <iostream>
#include <math.h>
using namespace std;


class TComplex
{
    double real, imag;

public:
    TComplex();
    TComplex(const int&);
    TComplex(const double&, const double&);

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

    friend ostream& operator << (ostream&, TComplex);
    friend istream& operator >> (istream&, TComplex&);

    friend QString& operator<<(QString&, TComplex);
};

#endif // COMPLEX_H
