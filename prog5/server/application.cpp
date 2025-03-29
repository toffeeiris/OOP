#include "application.h"
#include "polynom.h"
#include "common.h"

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
    TComplex my_coef, point, value, root;

    int start = msg.indexOf(separator.toLatin1());
    int t = msg.left(start).toInt();
    switch (t)
    {
        case VALUE_REQUEST:
            msg = msg.right(msg.length()-start-1);
            msg>>point;
            value = p.value_in_point(point);
            s<<(QString)value;
            answer<<QString().setNum(VALUE_ANSWER);
            answer += s;
            break;
        case PRINT_CANONIC_REQUEST:
            p.set_type(1);
            s<<p;
            answer<<QString().setNum(PRINT_ANSWER)<<s;
            break;
        case PRINT_CLASSIC_REQUEST:
            p.set_type(0);
            s<<p;
            answer<<QString().setNum(PRINT_ANSWER)<<s;
            break;
        case UPDATE_REQUEST:
            msg = msg.right(msg.length()-start-1);
            msg >> my_coef;
            coef = my_coef;
            start = msg.indexOf(separator.toLatin1());
            my_deg = msg.left(start).toInt();
            deg = my_deg;
            p = TPolynom(coef, deg);
            break;
        case CHANGE_ROOT_REQUEST:
            msg = msg.right(msg.length()-start-1);
            msg >> root;
            start = msg.indexOf(separator.toLatin1());
            root_ind = msg.left(start).toInt();
            p.change_root(root_ind, root);
            break;
        case END_REQUEST:
            answer<<QString().setNum(END_ANSWER);
            break;
        default: return;
    }
    QByteArray ba = answer.toLocal8Bit();
    const char *c_str2 = ba.data();
    comm->send(QByteArray().append(c_str2));
}
