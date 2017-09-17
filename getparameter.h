#ifndef GETPARAMETER_H
#define GETPARAMETER_H

#include <QObject>
#include <QSettings>

class getparameter : public QObject
{
    Q_OBJECT
public:
    explicit getparameter(QObject *parent = 0);
//    QSettings getparameter::get_Qstring(QString confile);

signals:

public slots:
};

#endif // GETPARAMETER_H
