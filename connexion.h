#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
class Connexion
{
    QSqlDatabase db;
public:
    Connexion();
    bool createconnect();
};

#endif // CONNEXION_H
