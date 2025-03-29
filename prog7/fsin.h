#ifndef FSIN_H
#define FSIN_H

#include "function.h"

template <class number>
class TFsin : public TFunction<number>
{
    number* derivative;
    number* count(int n)
    {
        derivative = new number[n+1];
        for (int i = 0; i < n+1; i++)
        {
            if (i % 2 == 0)
                derivative[i] = sin(0);
            else if (i % 4 == 1)
                derivative[i] = cos(0);
            else if (i % 4 == 3)
                derivative[i] = (-1) * cos(0);
        }

        return derivative;
    }
public:
    TFsin(int n) : TFunction<number>(n, count(n)) {};
    ~TFsin() {delete [] derivative;}
};



#endif // FSIN_H
