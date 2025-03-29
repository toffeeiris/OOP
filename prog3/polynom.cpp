#include "polynom.h"
#include <QDebug>

TPolynom::TPolynom() : coefs(1), roots(0)
{
    coefs.change_index(0, 0);
}

TPolynom::TPolynom(number my_coef, int my_deg)
{
    deg = my_deg;
    roots.resize(deg);
    coefs.resize(deg + 1);
    coefs.change_index(deg, my_coef);
}

TPolynom::TPolynom(const TPolynom& other)
{
    deg = other.deg;
    coefs = other.coefs;
    roots = other.roots;
}

TPolynom& TPolynom::operator=(const TPolynom& other)
{
    if (this != &other)
    {
        deg = other.deg;
        coefs = other.coefs;
        roots = other.roots;
    }
    return *this;
}

void TPolynom::set_type(int my_type)
{
    show_type = my_type;
}

number TPolynom::value_in_point (number my_value)
{
    number rez = coefs[deg];

    for (int i = 0; i < deg; i++)
        rez = rez * (my_value - roots[i]);

    return rez;
}

void TPolynom::count_coefs (number my_coef)

{
    for (int i = 0; i < deg; i++)
        coefs[i] = 0;

    coefs[deg] = my_coef;
    coefs[1] = 1;
    coefs[0] = -roots[0];
    for (int i = 2; i <= deg; i++)
    {
        coefs[i] = coefs[i-1];
        for (int j = i-1; j > 0; j--)
            coefs[j] = coefs[j-1] - coefs[j] * roots[i-1];
        coefs[0] = -coefs[0] * roots[i-1];
    }

    for (int i = 0; i <= deg; i++)
        coefs[i] = coefs[i] * my_coef;
}

void TPolynom::change_seniorCoef(number my_coef)
{
    coefs.change_index(deg, my_coef);
    count_coefs(coefs[deg]);
}

void TPolynom::change_root(int index, number my_root)
{
    roots.change_index(index, my_root);
    count_coefs(coefs[deg]);
}

void TPolynom::change_deg(int new_deg)
{
    number my_coef = coefs[deg];
    roots.resize(new_deg);
    if (new_deg > deg)
        cin >> roots;
    coefs.resize(new_deg + 1);
    deg = new_deg;
    count_coefs(my_coef);
}

istream& operator>> (istream& is, TPolynom& p)
{
    is >> p.roots;

    p.count_coefs(p.coefs[p.deg]);
    return is;
}

ostream& operator<< (ostream& os, TPolynom& p)
{
    int temp_deg = p.deg;
    if (p.show_type == 0)
    {
        for (int i = 0; i <= p.deg; i++)
        {
            if (temp_deg == 1)
                os << p.coefs[temp_deg] << "*x + ";
            else if (temp_deg == 0)
                os << p.coefs[temp_deg];
            else
                os << p.coefs[temp_deg] << "*x^" << temp_deg << " + ";

            --temp_deg;
        }
    }
    else
    {
        os << p.coefs[temp_deg];
        for (int i = 0; i < p.deg; i++)
        {
            os << " * (x - " << p.roots[i] << ")";
        }
    }
    return os;
}


