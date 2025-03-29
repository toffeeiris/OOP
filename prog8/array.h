#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <ostream>
#include <QDebug>

using namespace std;

template <typename number>
class TArray
{

    number *arr;
    int size, point = 0;

public:
    TArray();
    TArray(int);

    ~TArray();

    TArray(const TArray<number>&);
    TArray<number>& operator=(const TArray<number>&);

    friend istream& operator>> (istream&, TArray<number>&);
    friend ostream& operator<< (ostream&, TArray<number>&);

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


template <typename number>
TArray<number>::TArray(): arr(nullptr), size(0)
{

}

template <typename number>
TArray<number>::TArray(int n) : size(n)
{
    number* my_arr = new number[size];
    arr = my_arr;
}

template <typename number>
TArray<number>::TArray(const TArray<number>& other)
{
    size = other.size;
    point = other.point;
    if (size > 0)
    {
        arr = new number[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = other.arr[i];
        }
    }
    else
    {
        arr = nullptr;
    }
}

template <typename number>
TArray<number>& TArray<number>::operator=(const TArray<number>& other)
{
    if (this != &other)
    {
        delete[] arr;

        size = other.size;
        point = other.point;

        if (size > 0)
        {
            arr = new number[size];
            for (int i = 0; i < size; i++)
            {
                arr[i] = other.arr[i];
            }
        }
        else
        {
            arr = nullptr;
        }
    }
    return *this;
}

template <typename number>
TArray<number>::~TArray()
{
    if(arr != nullptr)
    {
        delete[] arr;
        arr = nullptr;
    }
}

template <typename number>
istream& operator>> (istream& in, TArray<number>& my_arr)
{
    bool flag = false;
    for (int i = my_arr.point; i < my_arr.size; i++)
    {
        while(!flag)
        {
            cout << "x" << (i + 1) << ": ";
            if (!(in >> my_arr.arr[i]) || (my_arr.arr[i].fabs(my_arr.arr[i])) > 100000 || in.peek() != '\n')
            {
                if ((my_arr.arr[i].fabs(my_arr.arr[i])) > 100000)
                {
                    qDebug() << "Введите число в диапазоне (-100000; 100000) или такое, чтобы его модуль был в этом диапазоне!";
                }
                else
                {
                    qDebug() << "Вводите только цифры!";
                }
                in.clear();
                flag = false;
                while (in.get() != '\n');
            }
            else flag = true;
        }
        flag = false;
    }
    return in;
}

template <typename number>
ostream& operator<< (ostream& out, TArray<number>& my_arr)
{
    if (my_arr.get_size() == 0)
    {
        qDebug() << "Массив пуст!";
    }
    else
    {
        for (int i = 0; i < my_arr.size; i++)
        {
            out << my_arr.arr[i] << "  ";
        }
        out << endl;
    }
    return out;
}

template <typename number>
void TArray<number>::clear_arr()
{
    if (arr != nullptr)
    {
        delete[] arr;
        arr = nullptr;
        size = 0;
        point = 0;
    }
}

template <typename number>
void TArray<number>::resize(int new_size)
{
    number* new_arr = new number[new_size];
    if(new_size < size)
    {
        for (int i = 0; i < new_size; i++)
        {
            new_arr[i] = arr[i];
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            new_arr[i] = arr[i];
        }

        if (size == 0)
        {
            point = 0;
        }
        else
        {
            point = size;
        }
    }

    if(arr != nullptr)
    {
        delete[] arr;
    }
    arr = new_arr;
    size = new_size;
}

template <typename number>
void TArray<number>::change_index(int index, number value)
{
    arr[index] = value;
}

template <typename number>
number TArray<number>::avarage_value()
{
    number sum = 0;
    for (int i = 0; i < size; i++)
        sum += arr[i];
    return sum/size;
}

template <typename number>
number TArray<number>::standard_deviation()
{
    number sd = 0, sum = 0;
    for (int i = 0; i < size; i++)
        sum += pow((arr[i] - avarage_value()), 2);
    sd = sqrt(sum/(size-1));
    return sd;
}

template <typename number>
void TArray<number>::sort(bool ind)
{
    if(ind == 0)
    {
        for (int i = 0; i < size - 1; i++)
        {
            for(int j = i+1; j < size; j++)
            {
                if (arr[i] > arr[j])
                {
                    number temp = arr[j];
                    arr[j] = arr[i];
                    arr[i] = temp;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < size -1; i++)
        {
            for(int j = i+1; j < size ; j++)
            {
                if (arr[i] < arr[j])
                {
                    number temp = arr[j];
                    arr[j] = arr[i];
                    arr[i] = temp;
                }
            }
        }
    }
}


#endif // ARRAY_H
