#ifndef POLYNOM_H
#define POLYNOM_H

#include <array.h>

template <typename number>

class TPolynom
{
    TArray<number> coefs;
    TArray<number> roots;
    int deg, show_type;


public:
    TPolynom();
    TPolynom(number mycoef, int my_deg);
    TPolynom(const TPolynom<number>&);
    TPolynom<number>& operator=(const TPolynom<number>&);

    template <class T>
    friend istream& operator>> (istream&, TPolynom<T>&);
    template <class T>
    friend ostream& operator<< (ostream&, TPolynom<T>&);
    template <class T>
    friend QString& operator<< (QString&, TPolynom<T>&);

    void add_root(int, number);
    void set_type(int);
    number value_in_point(number);
    void count_coefs(number);
    void change_seniorCoef(number);
    void change_root(int, number);
    void change_deg(int);
    number get_root(int);

    int get_deg()
    {
        return deg;
    }
};


template <typename number>
TPolynom<number>::TPolynom() : coefs(1), roots(0)
{
    coefs.change_index(0, 0);
}

template <typename number>
TPolynom<number>::TPolynom(number my_coef, int my_deg)
{
    deg = my_deg;
    roots.resize(deg);
    coefs.resize(deg + 1);
    coefs.change_index(deg, my_coef);
}

template <typename number>
TPolynom<number>::TPolynom(const TPolynom<number>& other)
{
    deg = other.deg;
    coefs = other.coefs;
    roots = other.roots;
}

template <typename number>
TPolynom<number>& TPolynom<number>::operator=(const TPolynom<number>& other)
{
    if (this != &other)
    {
        deg = other.deg;
        coefs = other.coefs;
        roots = other.roots;
    }
    return *this;
}

template <typename number>
void TPolynom<number>::set_type(int my_type)
{
    show_type = my_type;
}

template <typename number>
number TPolynom<number>::value_in_point (number my_value)
{
    number rez = coefs[deg];

    for (int i = 0; i < deg; i++)
        rez = rez * (my_value - roots[i]);

    return rez;
}

template <typename number>
void TPolynom<number>::count_coefs (number my_coef)

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

template <typename number>
void TPolynom<number>::change_seniorCoef(number my_coef)
{
    coefs.change_index(deg, my_coef);
    count_coefs(coefs[deg]);
}

template <typename number>
void TPolynom<number>::change_root(int index, number my_root)
{
    roots.change_index(index, my_root);
    count_coefs(coefs[deg]);
}

template <typename number>
void TPolynom<number>::change_deg(int new_deg)
{
    number my_coef = coefs[deg];
    roots.resize(new_deg);
    if (new_deg > deg)
        cin >> roots;
    coefs.resize(new_deg + 1);
    deg = new_deg;
    count_coefs(my_coef);
}

template <typename number>
istream& operator>> (istream& is, TPolynom<number>& p)
{
    is >> p.roots;
    p.count_coefs(p.coefs[p.deg]);
    return is;
}

template <typename number>
void TPolynom<number>::add_root(int index, number my_root)
{
    roots[index] = my_root;
    count_coefs(coefs[deg]);
}

template <typename number>
number TPolynom<number>::get_root(int index)
{
    return roots[index];
}

template <typename number>
ostream& operator<< (ostream& os, TPolynom<number>& p)
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

template <typename number>
QString& operator<< (QString& s, TPolynom<number>& p)
{
    int temp_deg = p.deg;

    if (p.show_type == 0)
    {
        for (int i = 0; i <= p.deg; i++)
        {
            if (temp_deg == 1)
            {
                s << p.coefs[temp_deg];
                s += "*x + ";
            }
            else if (temp_deg == 0)
            {
                s << p.coefs[temp_deg];
            }
            else
            {
                s << p.coefs[temp_deg];
                s += "*x^";
                s += QString().setNum(temp_deg);
                s += " + ";

            }
            --temp_deg;
        }
    }
    else
    {
        s << p.coefs[temp_deg];
        for (int i = 0; i < p.deg; i++)
        {
            s += " * (x - ";
            s << p.roots[i];
            s += ")";
        }
    }
    return s;
}


#endif // POLYNOM_H
