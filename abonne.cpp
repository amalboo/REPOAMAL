#include <abonne.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QPdfWriter>
#include <QDate>
//#include <QPrinter>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <utility>
#include <map>
#include <QFile>
#include <QTextStream>

Abonne::Abonne()
{
    int id;
    QString nom;
    QString prenom;
    int age;
    int taille;
    int dure;
    int cin;

}
Abonne::Abonne(int i,QString n,QString p,int t ,int d ,int a)


{
    this->cin=i;
    this->nom=n;
    this->prenom=p;
    this->age=a;
    this->taille=t;

    this->dure=d;


}

//getters
QString Abonne::getNom(){return nom;}
QString Abonne::getPrenom(){return prenom;}
int Abonne::getAge(){return age;}
int Abonne::getTaille(){return taille;}
int Abonne::getID(){return id;}
//setters
void Abonne::setNom(QString n){this->nom=n;}
void Abonne::setPrenom (QString p){this->prenom=p;}
void Abonne::setID(int id){this->id=id;}




bool Abonne::ajouter(int cin, QString nom,QString prenom,int age,int taille,int dure) {
    QSqlQuery query;

    query.prepare("INSERT INTO GS_ABONNE (cin, nom, prenom, age, taille, dure)"

                  "VALUES (:cin, :nom, :prenom, :age, :taille, :dure)");
    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":age", age);
    query.bindValue(":taille", taille);

    query.bindValue(":dure", dure);

    return query.exec();
}



QSqlQueryModel * Abonne::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT cin, nom, prenom, age, taille, dure FROM GS_ABONNE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("taille"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("dure"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("supprimer"));



        return model;
}


bool Abonne::supprimer(int cin)
{
    QSqlQuery query;


    query.prepare("SELECT * FROM GS_ABONNE WHERE cin = :cin");
    query.bindValue(":cin", cin);

    if (!query.exec())
    {
        qDebug() << "Error selecting abonne to delete: " << query.lastError().text();
        return false;
    }

    if (query.next())
    {

        query.prepare("DELETE FROM GS_ABONNE WHERE cin = :cin");
        query.bindValue(":cin", cin);

        if (!query.exec())
        {
            qDebug() << "Error deleting abonne: " << query.lastError().text();
            return false;
        }
        else
        {
            qDebug() << "abonne deleted successfully!";
            return true;
        }
    }
    else
    {
        QMessageBox::warning(nullptr,"not found","abonne not found");
        return false;
    }
}

bool Abonne::recuperer_abonne(int cin, QString &nom, QString &prenom, int &age, int &taille, int &dure)
{
    QSqlQuery query;
    query.prepare("SELECT nom, prenom, age, taille, dure FROM GS_ABONNE WHERE cin = :cin");
    query.bindValue(":cin", cin);

    if (query.exec() && query.next()) {
        nom = query.value(0).toString();
        prenom = query.value(1).toString();
        age = query.value(2).toInt();
        taille = query.value(3).toInt();
        dure = query.value(4).toInt();
        return true;
    } else {
        return false;
    }
}



bool Abonne::modifier(int res, QString nom, QString prenom, int age, int taille, int dure) {
    QSqlQuery query;

    query.prepare("UPDATE GS_ABONNE SET nom=:nom, prenom=:prenom, age=:age, taille=:taille, dure=:dure WHERE cin=:res");


    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":age", age);
    query.bindValue(":taille", taille);
    query.bindValue(":dure", dure);
    query.bindValue(":res", res);

    // Execute the query and return the result
    return query.exec();
}
QSqlQueryModel * Abonne::trier_nom()
{

QSqlQueryModel* model=new QSqlQueryModel();

  model->setQuery("SELECT cin, prenom, nom, age,taille,dure FROM GS_ABONNE ORDER BY nom ASC");

  model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("age "));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("taille"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("dure "));

  return  model;


}
QSqlQueryModel* Abonne::trier_prenom()
{

QSqlQueryModel* model=new QSqlQueryModel();

  model->setQuery("SELECT cin, prenom, nom, age,taille,dure FROM GS_ABONNE ORDER BY prenom ASC");

  model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("age "));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("taille"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("dure "));

  return  model;

}

/*void Abonne::historique(Abonne ab, QString formatteddate,int a)
{
    QString text;
    if (a == 1) {
        text="ajout";
       //ajout
    } else if (a == 3) {
        //ipdate
        text="update";
    } else if (a == 2) {
        //supprim
        text="delete";
    } else if (a == 4) {
        //recherche
        text="recherche";
    }

    QDate date = QDate::currentDate();
    QString formatteddate = date.toString("dd:MM:yyyy");

    /*QFile file("C:/Users/amalb/Desktop/pi/nautica/his.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier.";
        return;
    }

    QTextStream out(&file);
    out << formatteddate + "\n" << text << endl;

    file.close();
}*/
std::pair<double, int> Abonne::stat_age(int height)
{
    // Requête pour compter le nombre d'abonnés âgés de 18 ans
    QSqlQuery queryAgeCount;
    queryAgeCount.prepare("SELECT COUNT(*) FROM gs_abonne WHERE age = 18");
    if (!queryAgeCount.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête pour compter les abonnés âgés de 18 ans :" << queryAgeCount.lastError().text();
        return std::make_pair(0.0, 0);
    }
    queryAgeCount.next();
    int count_18 = queryAgeCount.value(0).toInt();

    // Requête pour compter le nombre total d'abonnés
    QSqlQuery queryTotalCount;
    queryTotalCount.prepare("SELECT COUNT(*) FROM gs_abonne");
    if (!queryTotalCount.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête pour compter le nombre total d'abonnés :" << queryTotalCount.lastError().text();
        return std::make_pair(0.0, 0);
    }
    queryTotalCount.next();
    int total_count = queryTotalCount.value(0).toInt();

    // Calcul du pourcentage d'abonnés âgés de 18 ans
    double pourcentage_18 = (count_18 * 100.0) / total_count;

    // Calcul de la nouvelle hauteur en fonction du pourcentage
    int newHeight = static_cast<int>(height * pourcentage_18) / 100;

    return std::make_pair(pourcentage_18, newHeight);
}


std::pair<double, int> Abonne::stat_ageenfant(int height)
{
    // Requête pour compter le nombre d'abonnés âgés de moins de 18 ans
    QSqlQuery queryEnfantCount;
    queryEnfantCount.prepare("SELECT COUNT(*) FROM gs_abonne WHERE age < 18");
    if (!queryEnfantCount.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête pour compter les abonnés âgés de moins de 18 ans :" << queryEnfantCount.lastError().text();
        return std::make_pair(0.0, 0);
    }
    queryEnfantCount.next();
    int count_enfant = queryEnfantCount.value(0).toInt();

    // Requête pour compter le nombre total d'abonnés
    QSqlQuery queryTotalCount;
    queryTotalCount.prepare("SELECT COUNT(*) FROM gs_abonne");
    if (!queryTotalCount.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête pour compter le nombre total d'abonnés :" << queryTotalCount.lastError().text();
        return std::make_pair(0.0, 0);
    }
    queryTotalCount.next();
    int total_count = queryTotalCount.value(0).toInt();

    // Calcul du pourcentage d'abonnés âgés de moins de 18 ans
    double pourcentage_enfant = (count_enfant * 100.0) / total_count;

    // Calcul de la nouvelle hauteur en fonction du pourcentage
    int newHeight =(height * pourcentage_enfant) / 100;

    return std::make_pair(pourcentage_enfant, newHeight);
}

std::pair<double, int> Abonne::stat_ageadulte(int height)
{
    // Requête pour compter le nombre d'abonnés âgés entre 30 et 40 ans
    QSqlQuery queryAdulteCount;
    queryAdulteCount.prepare("SELECT COUNT(*) FROM gs_abonne WHERE age >= 30 AND age <= 40");
    if (!queryAdulteCount.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête pour compter les abonnés âgés entre 30 et 40 ans :" << queryAdulteCount.lastError().text();
        return std::make_pair(0.0, 0);
    }
    queryAdulteCount.next();
    int count_adulte = queryAdulteCount.value(0).toInt();

    // Requête pour compter le nombre total d'abonnés
    QSqlQuery queryTotalCount;
    queryTotalCount.prepare("SELECT COUNT(*) FROM gs_abonne");
    if (!queryTotalCount.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête pour compter le nombre total d'abonnés :" << queryTotalCount.lastError().text();
        return std::make_pair(0.0, 0);
    }
    queryTotalCount.next();
    int total_count = queryTotalCount.value(0).toInt();

    // Calcul du pourcentage d'abonnés âgés entre 30 et 40 ans
    double pourcentage_adulte = (count_adulte * 100.0) / total_count;

    // Calcul de la nouvelle hauteur en fonction du pourcentage
    int newHeight = (height * pourcentage_adulte) / 100;

    return std::make_pair(pourcentage_adulte, newHeight);
}
std::pair<double, int> Abonne::stat_agejeune(int height)
{
    // Requête pour compter le nombre d'abonnés âgés entre 20 et 30 ans
    QSqlQuery queryJeuneCount;
    queryJeuneCount.prepare("SELECT COUNT(*) FROM gs_abonne WHERE age >= 20 AND age < 30");
    if (!queryJeuneCount.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête pour compter les abonnés âgés entre 20 et 30 ans :" << queryJeuneCount.lastError().text();
        return std::make_pair(0.0, 0);
    }
    queryJeuneCount.next();
    int count_jeune = queryJeuneCount.value(0).toInt();

    // Requête pour compter le nombre total d'abonnés
    QSqlQuery queryTotalCount;
    queryTotalCount.prepare("SELECT COUNT(*) FROM gs_abonne");
    if (!queryTotalCount.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête pour compter le nombre total d'abonnés :" << queryTotalCount.lastError().text();
        return std::make_pair(0.0, 0);
    }
    queryTotalCount.next();
    int total_count = queryTotalCount.value(0).toInt();

    // Calcul du pourcentage d'abonnés âgés entre 20 et 30 ans
    double pourcentage_jeune = (count_jeune * 100.0) / total_count;

    // Calcul de la nouvelle hauteur en fonction du pourcentage
    int newHeight = (height * pourcentage_jeune) / 100;

    return std::make_pair(pourcentage_jeune, newHeight);
}

std::pair<double, int> Abonne::stat_age_quarentaine(int height)
{
    // Requête pour compter le nombre d'abonnés âgés de 40 ans et plus
    QSqlQuery queryQuarentaineCount;
    queryQuarentaineCount.prepare("SELECT COUNT(*) FROM gs_abonne WHERE age >= 40");
    if (!queryQuarentaineCount.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête pour compter les abonnés âgés de 40 ans et plus :" << queryQuarentaineCount.lastError().text();
        return std::make_pair(0.0, 0);
    }
    queryQuarentaineCount.next();
    int count_quarentaine = queryQuarentaineCount.value(0).toInt();

    // Requête pour compter le nombre total d'abonnés
    QSqlQuery queryTotalCount;
    queryTotalCount.prepare("SELECT COUNT(*) FROM gs_abonne");
    if (!queryTotalCount.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête pour compter le nombre total d'abonnés :" << queryTotalCount.lastError().text();
        return std::make_pair(0.0, 0);
    }
    queryTotalCount.next();
    int total_count = queryTotalCount.value(0).toInt();

    // Calcul du pourcentage d'abonnés âgés de 40 ans et plus
    double pourcentage_quarentaine = (count_quarentaine * 100.0) / total_count;

    // Calcul de la nouvelle hauteur en fonction du pourcentage
    int newHeight = (height * pourcentage_quarentaine) / 100;

    return std::make_pair(pourcentage_quarentaine, newHeight);
}


void Abonne::printTableToPdf(const QString& filePath, QAbstractItemModel* model, const QString& tableName)
{
    QTextDocument doc;

    QString tableData = "<html><head><style>"
                        "table { border-collapse: collapse; width: 100%; }"
                        "th, td { padding: 8px; text-align: left; }"
                        "</style></head><body><table border='1'>";

    tableData += QString("<center> <H1>Liste Des %1 </H1><br><br><table border=1 cellspacing=0 cellpadding=2>\n").arg(tableName);
    tableData += "<tr bgcolor=#f0f0f0>";
    for (int col = 0; col < model->columnCount(); ++col) {
        tableData += "<th>" + model->headerData(col, Qt::Horizontal).toString() + "</th>";
    }
    tableData += "</tr>";

    for (int row = 0; row < model->rowCount(); ++row) {
        tableData += "<tr>";
        for (int col = 0; col < model->columnCount(); ++col) {
            QModelIndex index = model->index(row, col);
            tableData += "<td>" + index.data().toString() + "</td>";
        }
        tableData += "</tr>";
    }
    tableData += "</table></body></html>";

    doc.setHtml(tableData);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageMargins(5, 0, 5, 5, QPrinter::Millimeter);

    doc.setPageSize(printer.pageRect().size());
    doc.print(&printer);


    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

QVector<QString> Abonne::recupererid() {
    QVector<QString> ids;

    // Exécutez la requête SQL pour récupérer tous les IDs
    QSqlQuery query("SELECT cin FROM GS_ABONNE");

    // Vérifiez si la requête a été exécutée avec succès
    if (query.exec()) {
        // Parcourez les résultats et insérez chaque ID dans le QVector
        while (query.next()) {
            QString cin = query.value(0).toString(); // Récupérez la valeur du premier champ (indice 0)
            ids.append(cin);
        }
    } else {
        // Affichez un message d'erreur si la requête a échoué
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
    }

    // Retournez le QVector contenant les IDs récupérés
    return ids;
}

void Abonne::ajouterEvenement(const QString& info){

            QFile file("C:/Users/amalb/Desktop/pi/nautica/his.txt");
                if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                    qDebug() << "Erreur lors de l'ouverture du fichier.";
                    return;
                }

                QTextStream out(&file);
                out <<  info << "\n" << endl;

                file.close();

       }























