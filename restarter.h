#ifndef RESTARTER_H
#define RESTARTER_H

#include <QObject>


class Restarter : public QObject
{
    Q_OBJECT

public:
    explicit Restarter(QObject *parent = nullptr);
    Q_INVOKABLE void makeRestart();

signals:

public slots:
};

#endif // RESTARTER_H
