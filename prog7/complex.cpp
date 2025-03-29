#include "complex.h"

TComplex::TComplex()
{

}

TComplex::TComplex(const int& r)
{
    real = r;
    imag = 0;
}

TComplex::TComplex(const double& r, const double& i)
{
    real = r;
    imag = i;
}

void TComplex::operator +=(TComplex c)
{
    real += c.real;
    imag += c.imag;
}


TComplex TComplex::operator-()
{
    TComplex rez;
    rez.real = real * (-1);
    rez.imag = imag * (-1);
    return rez;
}


TComplex TComplex::operator-(TComplex c)
{
    TComplex rez;
    rez.real = real - c.real;
    rez.imag = imag - c.imag;
    return rez;
}

TComplex TComplex::operator*(TComplex c)
{
    TComplex rez;
    rez.real = real * c.real - imag * c.imag;
    rez.imag = real * c.imag + imag * c.real;
    return rez;
}

TComplex TComplex::operator/(unsigned num)
{
    TComplex rez;
    rez.real = real / num;
    rez.imag = imag / num;
    return rez;
}

bool TComplex::operator> (TComplex c)
{
    double fi1 = atan(imag/real);
    double fi2 = atan(c.imag/c.real);

    if (sqrt(pow(real, 2) + pow(imag, 2)) != c.fabs(c))
        return (sqrt(pow(real, 2) + pow(imag, 2)) > c.fabs(c));
    else return (fi1 > fi2);
}

bool TComplex::operator< (TComplex c)
{
    double fi1 = atan(imag/real);
    double fi2 = atan(c.imag/c.real);

    if (sqrt(pow(real, 2) + pow(imag, 2)) != c.fabs(c))
        return (sqrt(pow(real, 2) + pow(imag, 2)) < c.fabs(c));
    else return (fi1 < fi2);
}

TComplex sqrt(TComplex c)
{
    int sign;
    TComplex rez;
    sign = (c.imag >= 0)? 1 : -1;
    rez.real = sqrt((c.fabs(c) + c.real)/2);
    rez.imag = sign * sqrt((c.fabs(c) - c.real)/2);
    return rez;
}

TComplex pow(TComplex c, int st)
{
    double arg;
    TComplex rez;
    arg = atan(c.imag/c.real);
    rez.real = pow(c.fabs(c), st) * cos(st * arg);
    rez.imag = pow(c.fabs(c), st) * sin(st * arg);
    return rez;
}

ostream& operator << (ostream& os, TComplex c)
{
    if (c.imag >= 0)
    {
        os << "(" << c.real << " + " << c.imag << "i)";
    }
    else
    {
        os << "(" << c.real << " - " << fabs(c.imag) << "i)";
    }
    return os;
}

istream& operator >> (istream& is, TComplex &c)
{
    is >> c.real >> c.imag;

    if ((fabs(c.real) + fabs(c.imag)) == 0)
    {
        c.real = fabs(c.real);
        c.imag = fabs(c.imag);
    }
    else if (fabs(c.real) == 0)
        c.real = fabs(c.real);
    else if (fabs(c.imag) == 0)
        c.imag = fabs(c.imag);

    return is;
}

double TComplex::fabs(TComplex c)
{
    double module;
    module = sqrt(pow(c.real, 2) + pow(c.imag, 2));
    return module;
}

double TComplex::get_real(TComplex c)
{
    return c.real;
}

double TComplex::get_imag(TComplex c)
{
    return c.imag;
}

QString& operator<<(QString& s, TComplex c)
{
    s += "(";
    s += QString().setNum(c.real);

    if (c.imag >= 0)
        s += " + ";
    else
        s += " - ";

    s += QString().setNum(fabs(c.imag));
    s += "i)";
    return s;
}
