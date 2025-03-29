#include "application.h"
#include "array.h"
#include <iostream>
#include <QDebug>

using namespace std;

TApplication::TApplication()
{

}

void enter_size(bool &flag, int &n)
{
    while(!flag)
    {
        cout << "N = ";
        if (!(cin >> n) || n < 0 || cin.peek() != '\n')
        {
            if (n < 0)
            {
                qDebug() << "Введите число больше 0!";
            }
            else
            {
                qDebug() << "Вводите только цифры (причем целые числа)!";
            }
            cin.clear();
            flag = false;
            while (cin.get() != '\n');
        }
        else flag = true;
    }

    flag = false;
}

int TApplication::exec()
{
    int ch, n = 0, t = 0;
    bool flag = false;
    TArray current(0);

    while(true)
    {
        ch = menu();
        switch(ch)
        {
        case 1:
        {
            if (n == 0)
            {
                qDebug() << "Сначала задайте размер массива!";
                enter_size(flag, n);
                if(n == 0)
                {
                    cout << current;
                }
                else
                {
                    current.resize(n);
                    cin >> current;
                }
            }
            else
            {
                qDebug() << "Выберите пункт 4, чтобы изменить массив";
            }

            system("pause");
            break;
        }
        case 2:
        {
            if (n == 0)
            {
                qDebug() << "Сначала запоните массив элементами!";
            }
            else if (n == 1)
            {
                qDebug() << "Нет смысла вычислять!";
            }
            else
            {
                cout << "x = " << current.avarage_value() << endl << "S = +/- " << current.standard_deviation() << endl;
            }
            system("pause");
            break;
        }
        case 3:
        {
            if (current.get_size() == 0)
            {
                cout << current;
            }
            else if (current.get_size() == 1)
            {
                qDebug() << "Нет смысла сортировать!";
            }
            else
            {
                while(!flag)
                {
                    cout << "(1 or 2): ";
                    if (!(cin >> t) || (t != 1 && t != 2) || cin.peek() != '\n')
                    {
                        qDebug() << "Некорректный ввод!";

                        cin.clear();
                        flag = false;
                        while (cin.get() != '\n');
                    }
                    else flag = true;
                }

                if (t == 1)
                {
                    current.sort(0);
                }
                else
                {
                    current.sort(1);
                }

                cout << current;
            }

            flag = false;
            system("pause");
            break;
        }
        case 4:
        {
            enter_size(flag, n);
            if (n == 0)
            {
                qDebug() << "Вы отчистили массив!";
                current.clear_arr();

            }
            else if (current.get_size() == n)
            {
                qDebug() << "Массив сохранил прежнюю длину!";
            }
            else if (current.get_size() > n)
            {
                qDebug() << "Массив обрезан!";
                current.resize(n);
                cout << current;
            }
            else
            {
                current.resize(n);
                cin >> current;
            }

            system("pause");
            break;
        }
        case 5:
        {
            int my_index;
            number my_value;
            if (current.get_size() == 0)
            {
                cout << current;
            }
            else
            {
                while(!flag)
                {
                    qDebug() << "Индекс (нумерация с 0): ";
                    if (!(cin >> my_index) || my_index < 0 || my_index >= current.get_size() || cin.peek() != '\n')
                    {
                        qDebug() << "Некорректный ввод индекса!";

                        cin.clear();
                        flag = false;
                        while (cin.get() != '\n');
                    }
                    else flag = true;
                }

                flag = false;

                while(!flag)
                {
                    qDebug() << "Значение: ";
                    if (!(cin >> my_value) || my_value.fabs(my_value) > 100000 || cin.peek() != '\n')
                    {
                        if (my_value.fabs(my_value) > 100000)
                        {
                            qDebug() << "Введите число в диапазоне (-100000; 100000)!";
                        }
                        else
                        {
                            qDebug() << "Вводите только цифры!";
                        }
                        cin.clear();
                        flag = false;
                        while (cin.get() != '\n');
                    }
                    else flag = true;
                }

                current.change_index(my_index, my_value);
            }


            flag = false;
            system("pause");
            break;
        }
        case 6:
        {
            cout << current;
            system("pause");
            break;
        }
        case 0:
            return 0;
        default:
            break;
        }
    }
    return 0;
}

int TApplication::menu()
{
    system("cls");
    setlocale(LC_ALL, "");
    int ch;
    bool check = false;
    qDebug() << "1. Ввести значения элементов массива";
    qDebug() << "2. Рассчитать среднее значение и СКО";
    qDebug() << "3. Сортировка по (1)возрастанию/(2)убыванию";
    qDebug() << "4. Изменить размер массива";
    qDebug() << "5. Изменить n-ое значение элемента массива";
    qDebug() << "6. Вывести массив";
    qDebug() << "0 -> Выйти из приложения";

    while(!check)
    {
        cout << "> ";
        if (!(cin >> ch) || ch < 0 || ch > 6 || cin.peek() != '\n')
        {
            qDebug() << "Некорректный ввод!";

            cin.clear();
            check = false;
            while (cin.get() != '\n');
        }
        else check = true;
    }

    return ch;
}

