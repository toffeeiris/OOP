#include "application.h"
#include "polynom.h"
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
        if (!(cin >> n) || n < 1 || cin.peek() != '\n')
        {
            if (n <= 0)
                qDebug() << "Введите степень больше 0!";
            else
                qDebug() << "Вводите только цифры (причем целые числа)!";
            cin.clear();
            flag = false;
            while (cin.get() != '\n');
        }
        else flag = true;
    }

    flag = false;
}

void enter_CoefOrRoot(bool &flag, number &my_data, char type)
{
    while(!flag)
    {
        if (type == 'c')
            qDebug() << "Старший коэффициент: ";
        else if (type == 'r')
            qDebug() << "Значение корня: ";

        if (!(cin >> my_data) || my_data.fabs(my_data) > 100000 || cin.peek() != '\n')
        {
            if (my_data.fabs(my_data) > 100000)
            {
                qDebug() << "Введите число по модулю в диапазоне (-100000; 100000)!";
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
    flag = false;
}

int TApplication::exec()
{
    int ch, p_deg = 0;
    bool flag = false;
    TPolynom p;
    number my_coef;

    while(true)
    {
        ch = menu();
        switch(ch)
        {
        case 1:
        {
            if (p_deg == 0)
            {
                enter_CoefOrRoot(flag, my_coef, 'c');
                qDebug() << "Сначала задайте степень полинома!";
                enter_size(flag, p_deg);
                p = TPolynom(my_coef, p_deg);
                qDebug() << "Введите корни полинома: ";
                cin >> p;
            }
            else
            {
                qDebug() << "Выберите пункт 2, 3 или 5, чтобы изменить значения задающие полином!";
            }

            system("pause");
            break;
        }
        case 2:
        {
            if (p_deg == 0)
            {
                qDebug() << "Сначала создайте полином (пункт 1)!";
            }
            else
            {
                enter_CoefOrRoot(flag, my_coef, 'c');
                p.change_seniorCoef(my_coef);
                p.set_type(1);
                cout << p << endl;
            }

            system("pause");
            break;
        }
        case 3:
        {
            int my_index;
            number my_root;

            if (p_deg == 0)
            {
                qDebug() << "Сначала создайте полином (пункт 1)!";
            }
            else
            {
                while(!flag)
                {
                    qDebug() << "Индекс (нумерация с 0): ";
                    if (!(cin >> my_index) || my_index < 0 || my_index >= p_deg || cin.peek() != '\n')
                    {
                        qDebug() << "Некорректный ввод индекса!";

                        cin.clear();
                        flag = false;
                        while (cin.get() != '\n');
                    }
                    else flag = true;
                }
                flag = false;

                enter_CoefOrRoot(flag, my_root, 'r');
                p.change_root(my_index, my_root);
                p.set_type(1);
                cout << p << endl;
            }


            flag = false;
            system("pause");
            break;
        }
        case 4:
        {
            number my_value;
            if (p_deg == 0)
            {
                qDebug() << "Сначала создайте полином (пункт 1)!";
            }
            else
            {
                enter_CoefOrRoot(flag, my_value, 'r');
                cout << p.value_in_point(my_value) << endl;
            }

            system("pause");
            break;
        }
        case 5:
        {
            if (p_deg == 0)
            {
                qDebug() << "Сначала создайте полином (пункт 1)!";
            }
            else
            {
                enter_size(flag, p_deg);
                p.change_deg(p_deg);
                p.set_type(1);
                cout << p << endl;
            }

            system("pause");
            break;
        }
        case 6:
        {
            if (p_deg == 0)
            {
                qDebug() << "Сначала создайте полином (пункт 1)!";
            }
            else
            {
                p.set_type(0);
                cout << p << endl;
            }
            system("pause");
            break;
        }
        case 7:
        {
            if (p_deg == 0)
            {
                qDebug() << "Сначала создайте полином (пункт 1)!";
            }
            else
            {
                p.set_type(1);
                cout << p << endl;
            }

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
    qDebug() << "1. Создание полинома";
    qDebug() << "2. Изменить старший коэффициент полинома";
    qDebug() << "3. Изменить значение корня";
    qDebug() << "4. Вычислить полином в точке";
    qDebug() << "5. Изменить размер массива (степень полинома)";
    qDebug() << "6. Вывести полином в классической форме";
    qDebug() << "7. Вывести полином в канонической форме";
    qDebug() << "0 -> Выйти из приложения";

    while(!check)
    {
        cout << "> ";
        if (!(cin >> ch) || ch < 0 || ch > 7 || cin.peek() != '\n')
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

