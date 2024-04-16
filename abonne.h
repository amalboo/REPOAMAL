#ifndef ABONNE_H
#define ABONNE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>
#include <vector>
#include <map>
class Abonne
{
private:
    QString nom , prenom ;
    int cin,id;
    //char genre;
    int age,taille,dure;
    //QString date_abonnement,type,infos;

public:

    //constructeurs

    Abonne();
    Abonne(int cin,QString n ,QString p,int d,int t,int a);

    //getters
    QString getNom();
    QString getPrenom();
    int getID();
    int getAge();
    int getTaille();
    //setters
    void setNom(QString n);
    void setPrenom (QString p);
    void setID(int id);
    //fonctionnalité de base relatives a l'entité abonne
    bool supprimer(int cin);
    bool ajouter(int cin,QString nom,QString prenom,int age,int taille,int dure);
    bool recuperer_abonne(int cin, QString &nom, QString &prenom, int &age, int &taille, int &dure);
    bool modifier(int cin,QString nom,QString prenom,int age,int taille,int dure);
    QSqlQueryModel * supprimer();
    QSqlQueryModel * afficher();
    QSqlQueryModel * trier_nom();
    QSqlQueryModel * trier_prenom();
    void printTableToPdf(const QString& filePath, QAbstractItemModel* model, const QString& tableName);

    std::pair<double, int> stat_age(int height);
    std::pair<double, int> stat_ageenfant(int height);
    std::pair<double, int> stat_agejeune(int height );
    std::pair<double, int> stat_ageadulte(int height );
    std::pair<double, int> stat_age_quarentaine(int height );
    void supp();
    QVector<QString> recupererid();
    void ajouterEvenement(const QString& info);
};

#endif // ABONNE_H
