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

    TPolynom p;
    TComplex coef;
    int deg = 1;

public:

    TApplication(int, char**);

signals:

public slots:

    void recieve(QByteArray);

};

#endif // APPLICATION_H
