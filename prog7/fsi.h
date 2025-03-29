#ifndef FSI_H
#define FSI_H

#include "function.h"

template <class number>
class TFSi : public TFunction<number>
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
                derivative[i] = number(cos(0))/i;
            else if (i % 4 == 3)
                derivative[i] = number((-1) * cos(0))/i;
        }

        return derivative;
    }
public:
    TFSi(int n) : TFunction<number>(n, count(n)) {};
    ~TFSi() {delete [] derivative;}
};



#endif // FSI_H
