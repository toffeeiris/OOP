#ifndef POLYNOM_H
#define POLYNOM_H

#include <number.h>
#include <array.h>

class TPolynom
{
    TArray coefs;
    TArray roots;
    int deg, show_type;


public:
    TPolynom();
    TPolynom(number mycoef, int my_deg);
    TPolynom(const TPolynom&);
    TPolynom& operator=(const TPolynom&);

    friend istream& operator>> (istream&, TPolynom&);
    friend ostream& operator<< (ostream&, TPolynom&);

    void set_type(int);
    number value_in_point(number);
    void count_coefs(number);
    void change_seniorCoef(number);
    void change_root(int, number);
    void change_deg(int);

    int get_deg()
    {
        return deg;
    }
};


#endif // POLYNOM_H
