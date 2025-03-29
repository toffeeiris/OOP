#ifndef COMPLEX_H
#define COMPLEX_H

#include <QString>
#include <iostream>
#include <cmath>

using namespace std;

class TComplex
{
    double real, imag;
public:
    TComplex();
    TComplex(const int& r);
    TComplex(double, double);

    friend ostream& operator << (ostream&, TComplex);
    friend istream& operator >> (istream&, TComplex&);
    friend QString& operator << (QString&, TComplex&);

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
};

#endif // COMPLEX_H




