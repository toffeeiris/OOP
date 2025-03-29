#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <ostream>

#include "number.h"

using namespace std;

class TArray
{

    number *arr;
    int size, point = 0;

public:
    TArray();
    TArray(int);

    ~TArray();

    TArray(const TArray&);
    TArray& operator=(const TArray&);

    friend istream& operator>> (istream&, TArray&);
    friend ostream& operator<< (ostream&, TArray&);

    void resize(int new_size);
    number avarage_value();
    number standard_deviation();
    void sort(bool);
    void change_index(int, number);
    void clear_arr();

    int get_size()
    {
        return size;
    }

    number& operator[](int index)
    {
        return arr[index];
    }
};

#endif // ARRAY_H
