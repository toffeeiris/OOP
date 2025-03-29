#ifndef FUNCTION_H
#define FUNCTION_H


#include "polynom.h"
template <class number>
class TFunction : private TPolynom<number>
{
    int get_fact(int);

    public:
        TFunction(int, number*);
        using TPolynom<number>::operator();
        using TPolynom<number>::coefs;
};

template <class number>
TFunction<number>::TFunction(int my_deg, number* coefs) : TPolynom<number>:: TPolynom(my_deg,  coefs)
{
    for (int i = 0; i <= my_deg; i++)
        this->coefs[i] = this->coefs[i]/get_fact(i);
}

template <class number>
int TFunction<number>::get_fact(int num)
{
    if (num == 0 || num == 1)
        return 1;
    else
    {
        int num_fact = 1;
        for(int i = 2; i <= num; i++)
            num_fact *= i;

        return num_fact;
    }
}

#endif // FUNCTION_H
