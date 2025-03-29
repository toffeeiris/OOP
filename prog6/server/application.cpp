#include "application.h"
#include "polynom.h"
#include "complex.h"
#include "common.h"

QByteArray& operator>>(QByteArray& arr, double& c)
{
    int start = arr.indexOf(separator.toLatin1());
    if (start > 0)
    {
        c = arr.left(start).toDouble();
        arr = arr.right(arr.length()-start-1);
    }
    return arr;
}

QString& operator<<(QString& s, double c)
{
    if (fabs(c) != c)
    {
        s += "(-";
        s += QString().setNum(fabs(c));
        s += ")";
    }
    else
        s += QString().setNum(c);
    return s;
}

TApplication::TApplication(int argc, char *argv[])
            : QCoreApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                         QHostAddress("127.0.0.1"), 10001};
    comm = new TCommunicator(pars, this);

    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(recieve(QByteArray)));
}

void TApplication::recieve(QByteArray msg)
{
    QString answer, s;
    int my_deg, root_ind;
    int start = msg.indexOf(separator.toLatin1());
    int t,  mode = msg.left(start).toInt();
    msg = msg.right(msg.length() - start - 1);
    if (mode == D_MODE)
    {
        double my_coef, point, value, root;
        start = msg.indexOf(separator.toLatin1());
        t = msg.left(start).toInt();
        switch (t)
        {
        case VALUE_REQUEST:
            msg = msg.right(msg.length()-start-1);
            msg>>point;
            value = d_p.value_in_point(point);
            s<<(QString().setNum(value));
            answer<<QString().setNum(VALUE_ANSWER);
            answer += s;
            break;
        case PRINT_CANONIC_REQUEST:
            d_p.set_type(1);
            s<<d_p;
            answer<<QString().setNum(PRINT_ANSWER)<<s;
            break;
        case PRINT_CLASSIC_REQUEST:
            d_p.set_type(0);
            s<<d_p;
            answer<<QString().setNum(PRINT_ANSWER)<<s;
            break;
        case UPDATE_REQUEST:
            msg = msg.right(msg.length()-start-1);
            msg >> my_coef;
            d_coef = my_coef;
            start = msg.indexOf(separator.toLatin1());
            my_deg = msg.left(start).toInt();
            deg = my_deg;
            d_p = TPolynom<double>(d_coef, deg);
            break;
        case CHANGE_ROOT_REQUEST:
            msg = msg.right(msg.length()-start-1);
            msg >> root;
            start = msg.indexOf(separator.toLatin1());
            root_ind = msg.left(start).toInt();
            d_p.change_root(root_ind, root);
            break;
        case END_REQUEST:
            answer<<QString().setNum(END_ANSWER);
            break;
        default: return;
        }
    }
    else if (mode == C_MODE)
    {
        TComplex my_coef, point, value, root;
        start = msg.indexOf(separator.toLatin1());
        t = msg.left(start).toInt();
        switch (t)
        {
        case VALUE_REQUEST:
            msg = msg.right(msg.length()-start-1);
            msg>>point;
            value = c_p.value_in_point(point);
            s<<(QString)value;
            answer<<QString().setNum(VALUE_ANSWER);
            answer += s;
            break;
        case PRINT_CANONIC_REQUEST:
            c_p.set_type(1);
            s<<c_p;
            answer<<QString().setNum(PRINT_ANSWER)<<s;
            break;
        case PRINT_CLASSIC_REQUEST:
            c_p.set_type(0);
            s<<c_p;
            answer<<QString().setNum(PRINT_ANSWER)<<s;
            break;
        case UPDATE_REQUEST:
            msg = msg.right(msg.length()-start-1);
            msg >> my_coef;
            c_coef = my_coef;
            start = msg.indexOf(separator.toLatin1());
            my_deg = msg.left(start).toInt();
            deg = my_deg;
            c_p = TPolynom<TComplex>(c_coef, deg);
            break;
        case CHANGE_ROOT_REQUEST:
            msg = msg.right(msg.length()-start-1);
            msg >> root;
            start = msg.indexOf(separator.toLatin1());
            root_ind = msg.left(start).toInt();
            c_p.change_root(root_ind, root);
            break;
        case END_REQUEST:
            answer<<QString().setNum(END_ANSWER);
            break;
        default: return;
        }
    }



    QByteArray ba = answer.toLocal8Bit();
    const char *c_str2 = ba.data();
    comm->send(QByteArray().append(c_str2));
}
