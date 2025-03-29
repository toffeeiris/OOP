#include "array.h"
#include <QDebug>

TArray::TArray(): arr(nullptr), size(0)
{

}

TArray::TArray(int n) : size(n)
{
    number* my_arr = new number[size];
    arr = my_arr;
}

TArray::TArray(const TArray& other)
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

TArray& TArray::operator=(const TArray& other)
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

TArray::~TArray()
{
    delete[] arr;
}

istream& operator>> (istream& in, TArray& my_arr)
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

ostream& operator<< (ostream& out, TArray& my_arr)
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

void TArray::clear_arr()
{
    if (arr != nullptr)
    {
        delete[] arr;
        arr = nullptr;
        size = 0;
        point = 0;
    }
}

void TArray::resize(int new_size)
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

void TArray::change_index(int index, number value)
{
    arr[index] = value;
}

number TArray::avarage_value()
{
    number sum = 0;
    for (int i = 0; i < size; i++)
        sum += arr[i];
    return sum/size;
}

number TArray::standard_deviation()
{
    number sd = 0, sum = 0;
    for (int i = 0; i < size; i++)
        sum += pow((arr[i] - avarage_value()), 2);
    sd = sqrt(sum/(size-1));
    return sd;
}

void TArray::sort(bool ind)
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



