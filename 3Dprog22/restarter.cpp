#include "restarter.h"
#include <QProcess>


Restarter::Restarter(QObject *parent) :
    QObject (parent)
{
}

void Restarter::makeRestart()
{
    QProcess::execute("sudo service myservice restart");
}
