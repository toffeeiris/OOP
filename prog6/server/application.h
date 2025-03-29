#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>

#include "communicator.h"
#include "polynom.h"

class TApplication : public QCoreApplication
{
    Q_OBJECT

    TCommunicator *comm;

    TPolynom<double> d_p;
    double d_coef;
    TPolynom<TComplex> c_p;
    TComplex c_coef;
    int deg = 1;

public:

    TApplication(int, char**);

signals:

public slots:

    void recieve(QByteArray);

};

#endif // APPLICATION_H
