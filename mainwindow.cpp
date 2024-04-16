#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QMainWindow>
#include <QSqlQueryModel>
#include "abonne.h"
#include <QDebug>
#include <QPdfWriter>
#include <QFileDialog>
#include <QFile>
#include <QDialog>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QUrl>
#include <QWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QGroupBox>
#include <QTextBrowser>
#include <map>
#include <QStandardItem>
#include <QFile>
#include <QTextStream>
#include <QCalendarWidget>
#include <QColor>
#include <QTextCharFormat>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)

{
    Abonne Abpm;
    ui->setupUi(this);
    QSqlQueryModel *model = Abpm.afficher(); // Obtenir le modèle de la fonction afficher()

        ui->tableView_2->setModel(model); // Affecter le modèle au TableViewew

        // Ajouter un bouton de suppression à chaque ligne

    connect(ui->cin, &QLineEdit::textChanged, this, &MainWindow::recupererAbonne);

    connect(ui->l_id, &QLineEdit::textChanged, this, &MainWindow::vider);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::on_openGLWidget_aboutToResize);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::on_openGLWidget_2_aboutToResize);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::on_openGLWidget_3_aboutToResize);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::on_openGLWidget_4_aboutToResize);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::on_openGLWidget_5_aboutToResize);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::affcal);


}

MainWindow::~MainWindow()
{
    delete ui;
}


/*void MainWindow::on_supprimer_clicked()
{
    Abonne Abpm;
    int id = ui->supp_cin->text().toInt();
    bool test = Abpm.supprimer(id);
    Abpm.historique(2,Abpm.getNom());

    if(!test)
    {
        ui->supp_cin->clear();
    }
    else
    {
        QMessageBox::information(nullptr, tr("OK"),
                                 tr("suppression effectué.\n"
                                    "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
         ui->supp_cin->clear();
    }



}*/
void MainWindow::vider(const QString &text){

        if(text.isEmpty()) {
            // Vider les autres champs
            ui->le_nom->clear();
            ui->le_prenom->clear();
            ui->l_age->clear();
            ui->la_taille->clear();
            ui->la_dure->clear();

        }

}
void MainWindow::on_ajouter_clicked()
{
    // Récupérer des informations saisies dans les champs
    QString cin_str = ui->l_id->text();
    QString nom = ui->le_nom->text();
    QString prenom = ui->le_prenom->text();
    QString age_str = ui->l_age->text();
    QString taille_str = ui->la_taille->text();
    QString dure_str = ui->la_dure->text();

    if (nom.isEmpty() || prenom.isEmpty() || age_str.isEmpty() || taille_str.isEmpty() || dure_str.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur de saisie"), tr("Tous les champs sont obligatoires"));
    } else {
        bool ok;
        int cin = cin_str.toInt(&ok);
        int age = age_str.toInt(&ok);
        int taille = taille_str.toInt(&ok);
        int dure = dure_str.toInt(&ok);

        if (!ok) {
            QMessageBox::critical(this, tr("Erreur de saisie"), tr("Les champs numériques doivent contenir des valeurs valides"));
            return;
        }

        Abonne a(cin, nom, prenom, age, taille, dure);
        bool test = a.ajouter(cin, nom, prenom, age, taille, dure);
        // Obtenez la date actuelle
            QDate date = QDate::currentDate();
            //QBrush brush(Qt::red);
            //ui->calendarWidget->setStyleSheet(date, brush);




            QString formatteddate = date.toString("yyyy-MM-dd");

            // Ajoutez un événement à l'historique avec les détails
            // Supposons que "abonne" est une instance de la classe Abonne dans votre MainWindow
            QString details = formatteddate + " " +"ajout" + " " + a.getNom()+ " " + a.getPrenom()+ " " + ui->l_age->text()+ "ANS ET SON CIN " +ui->l_id->text();
            a.ajouterEvenement(details);
        if (test) {
            ui->tableView_2->setModel(Abpm.afficher());
            QMessageBox::information(nullptr, tr("OK"),
                                     tr("Ajout effectué.\n"
                                        "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            ui->l_id->clear();
            ui->le_nom->clear();
            ui->le_prenom->clear();
            ui->l_age->clear();
            ui->la_taille->clear();
            ui->la_dure->clear();
            //a.historique(1,a.getNom());
        } else {
            QMessageBox::critical(nullptr, tr("Erreur"),
                                  tr("Ajout non effectué.\n"
                                     "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            ui->l_id->clear();
            ui->le_nom->clear();
            ui->le_prenom->clear();
            ui->l_age->clear();
            ui->la_taille->clear();
            ui->la_dure->clear();
        }
    }


}

// Définir la fonction de récupération des données
void MainWindow::recupererAbonne(const QString& cinText) {
   // ui->Bs->setCurrentText(cinText);
    int cin = cinText.toInt();

    // Récupérer les données de l'abonné correspondant à l'identifiant cin
    Abonne abonne;
    QString nom, prenom;
    int age, taille, dure;
    if (abonne.recuperer_abonne(cin, nom, prenom, age, taille, dure)) {

        ui->nouv_nom->setText(nom);
        ui->nouv_prenom->setText(prenom);
        ui->nouv_age->setText(QString::number(age));
        ui->nouv_taille->setText(QString::number(taille));
        ui->nouv_dure->setText(QString::number(dure));
    } else {
        // Réinitialiser les champs si aucun abonné correspondant n'est trouvé
        ui->nouv_nom->clear();
        ui->nouv_prenom->clear();
        ui->nouv_age->clear();
        ui->nouv_taille->clear();
        ui->nouv_dure->clear();
    }
}







void MainWindow::on_pushButton_2_clicked()
{
    QSqlQueryModel *model = Abpm.afficher(); // Obtenir le modèle de la fonction afficher()

        ui->tableView_2->setModel(model);
        model->insertColumn(model->columnCount());
        model->insertColumn(model->columnCount());
        for (int row = 0; row < model->rowCount(); ++row)
        {

            QPushButton *deleteButton = new QPushButton("Delete");
            QPushButton *updateButton = new QPushButton("Update");
            connect(deleteButton, &QPushButton::clicked, this, &MainWindow::supp);
            connect(updateButton, &QPushButton::clicked, this, &MainWindow::modif);
            int cin = model->data(model->index(row, 0)).toInt();
            deleteButton->setObjectName(QString::number(cin));
            updateButton->setObjectName(QString::number(cin));
            ui->tableView_2->setIndexWidget(model->index(row, model->columnCount()-1), deleteButton);
            ui->tableView_2->setIndexWidget(model->index(row, model->columnCount()-2), updateButton);
        }
        }


void MainWindow::on_modfier_clicked()
{

        // Récupérer les valeurs des champs dans l'interface utilisateur
        int cin = ui->cin->text().toInt();
        QString nom = ui->nouv_nom->text();
        QString prenom = ui->nouv_prenom->text();
        int age = ui->nouv_age->text().toInt();
        int taille = ui->nouv_taille->text().toInt();
        int dure = ui->nouv_dure->text().toInt();
        Abonne abonne;
        if (abonne.modifier(cin, nom, prenom, age, taille, dure)) {
            // Obtenez la date actuelle
                QDate date = QDate::currentDate();
                QString formatteddate = date.toString("dd:MM:yyyy");

                // Ajoutez un événement à l'historique avec les détails
                // Supposons que "abonne" est une instance de la classe Abonne dans votre MainWindow
                QString details = formatteddate + " " +"update" + " " + ui->nouv_nom->text()+ " " + ui->nouv_prenom->text()+ " " + ui->nouv_age->text()+ "ANS ET SON CIN" + ui->cin->text();
                abonne.ajouterEvenement(details);
            QMessageBox::information(this, "Modification réussie", "Les informations de l'abonné ont été modifiées avec succès.");
            ui->nouv_nom->clear();
            ui->nouv_prenom->clear();
            ui->nouv_age->clear();
            ui->nouv_taille->clear();
            ui->nouv_dure->clear();
            //abonne.historique(3,abonne.getNom());

        } else {
            QMessageBox::warning(this, "Erreur de modification", "Impossible de modifier les informations de l'abonné.");
        }
    }








void MainWindow::on_pushButton_3_clicked()
{
    Abonne a;
    QSqlQueryModel* model = a.trier_nom();

    ui->tableView_2->setModel(model);
}

void MainWindow::on_pushButton_4_clicked()
{
    Abonne a;
    QSqlQueryModel* model = a.trier_prenom();

    ui->tableView_2->setModel(model);
}

void MainWindow::on_cherch_nom_textChanged(const QString &arg1)
{
    Abonne a;
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM GS_ABONNE WHERE cin  LIKE'"+arg1+"%' or nom  LIKE'"+arg1+"%' or prenom LIKE'"+arg1+"%'");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->tableView_2->setModel(model);
     //a.historique(4,arg1);

     }

}

/*void MainWindow::on_pdf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), "", tr("PDF Files (*.pdf)"));
            if (fileName.isEmpty()) {
                QMessageBox::critical(this, tr("Error"), tr("No file name specified."));
                return;
            }

            Abonne a;
            if (! a.pdf(ui->tableView_2, fileName)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not create PDF file."));
                return;

}
}*/

void MainWindow::on_commandLinkButton_clicked()
{
    QFile file("C:/Users/amalb/Desktop/pi/nautica/his.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::information(0, "info", file.errorString());
            return;
        }

        QTextStream lecture(&file);
        ui->textBrowser->setText(lecture.readAll());
        file.close();

        QMessageBox::information(nullptr, QObject::tr("Text History is open"),
                                 QObject::tr("Text History is successfully displayed.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
}





void MainWindow::on_openGLWidget_2_aboutToResize()
{
    Abonne a;

    auto result = a.stat_age(361);
    double moyenne_age = result.first;
    int newHeight = result.second;


    ui->bac->setText(QString::number(moyenne_age) +"%");

    ui->openGLWidget_2->resize(81,newHeight);
}

void MainWindow::on_openGLWidget_aboutToResize()
{
    Abonne a;

    auto result = a.stat_ageenfant(361);
    double moyenne_age = result.first;
    int newHeight = result.second;


    ui->enf->setText(QString::number(moyenne_age) +"%");

    ui->openGLWidget->resize(81,newHeight);
}

void MainWindow::on_openGLWidget_3_aboutToResize()
{
    Abonne a;

    auto result = a.stat_ageadulte(361);
    double moyenne_age = result.first;
    int newHeight = result.second;


    ui->adulte->setText(QString::number(moyenne_age) +"%");

    ui->openGLWidget_3->resize(81,newHeight);
}

void MainWindow::on_openGLWidget_4_aboutToResize()
{
    Abonne a;

    auto result = a.stat_agejeune(361);
    double moyenne_age = result.first;
    int newHeight = result.second;


    ui->bac_2->setText(QString::number(moyenne_age) +"%");

    ui->openGLWidget_4->resize(81,newHeight);
}
void MainWindow::on_openGLWidget_5_aboutToResize()
{
    Abonne a;

    auto result = a.stat_age_quarentaine(361);
    double moyenne_age = result.first;
    int newHeight = result.second;


    ui->age->setText(QString::number(moyenne_age) +"%");

    ui->openGLWidget_5->resize(81,newHeight);
}


void MainWindow::on_pdf_clicked()
{
    Abonne a;
    QString tableName = "Liste des Abonnés";

    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save as PDF", QDir::currentPath() + "C:/Users/amalb/Desktop/pi/nautica/pdf" +
                                                    "/" + tableName + ".pdf", "PDF Files (*.pdf)");

    if (fileName.isEmpty())
        return;

    QAbstractItemModel *model = ui->tableView_2->model();
    a.printTableToPdf(fileName, model, tableName);
}


void MainWindow ::supp()
{
    Abonne A,Abpm;
    QString nom, prenom;
    int age,taille,dure;

    QPushButton *senderButton= qobject_cast<QPushButton*>(sender());

        int id =senderButton->objectName().toInt();
            QMessageBox::StandardButton confirmation = QMessageBox::question(this, "Confirmation",
                                                                             "Êtes-vous sûr de vouloir supprimer cet Abonné ?",
                                                                             QMessageBox::Yes | QMessageBox::No);
   if (confirmation == QMessageBox::Yes)
    {
        A.recuperer_abonne(id, nom,prenom,age,taille,dure);
        bool test = Abpm.supprimer(id);

        QString Age = QString::number(age);
        QString cin = QString::number(id);
        //Abpm.historique(2,Abpm.getNom());
        // Obtenez la date actuelle
            QDate date = QDate::currentDate();
            //QBrush brush(Qt::red); // Choisissez la couleur de votre choix
            //calendarWidget->setDateTextFormat(date, brush);
            QString formatteddate = date.toString("dd:MM:yyyy");

            // Ajoutez un événement à l'historique avec les détails
            // Supposons que "abonne" est une instance de la classe Abonne dans votre MainWindow
            QString details = formatteddate + " " +"supression" + " " +nom+ " " +prenom+" " + Age+ "ANS ET SON CIN" + cin;
            Abpm.ajouterEvenement(details);


    }
}
void MainWindow::modif()
{
    ui->abs->setCurrentIndex(2);
    Abonne a;

    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());


        QString id = senderButton->objectName();
        recupererAbonne(id);




    }

void MainWindow::affcal(){

    {
        // Récupération du modèle associé au QTableView
        QAbstractItemModel *model = ui->historiqueTable->model();
        if (!model) {
            qDebug() << "No model set for the QTableView.";
            return;
        }

        // Parcours de chaque ligne du modèle
        for (int row = 0; row < model->rowCount(); ++row) {
            // Récupération de l'index pour l'élément de la deuxième colonne
            QModelIndex index = model->index(row, 1);
            if (index.isValid()) {
                // Récupération du texte de la cellule
                QString text = index.data(Qt::DisplayRole).toString();
                if (text == "ajout") {
                    // Récupération de la date dans la première colonne
                    QModelIndex dateIndex = model->index(row, 0);
                    if (dateIndex.isValid()) {
                        QString dateString = dateIndex.data(Qt::DisplayRole).toString();
                        QDate event = QDate::fromString(dateString, "yyyy-MM-dd");
                        qDebug() << event;
                        QTextCharFormat format;
                        format.setBackground(QColor("#FFFF00"));
                        ui->calendarWidget->setDateTextFormat(event, format);
                    }
                }
            }
        }
    }

}









void MainWindow::on_pushButton_6_clicked()
{
    // Ouverture du fichier en lecture seule
   QFile file("C:/Users/amalb/Desktop/pi/nautica/his.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    // Création d'un modèle de données Qt
    QStandardItemModel* model = new QStandardItemModel(this);

    // Définition des en-têtes de colonne
    model->setHorizontalHeaderLabels({"Date", "Type d'evenement", "Données"});

    // Création d'un QTextStream pour lire le fichier ligne par ligne
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine(); // Lecture de la ligne suivante

        // Traitement de la ligne et ajout au modèle
        QList<QStandardItem*> rowItems;
        QStringList parts = line.split(" ", QString::SkipEmptyParts); // Diviser la ligne en parties en utilisant les espaces comme séparateurs

        // Vérifier s'il y a au moins 2 espaces dans la ligne (pour les deux premières parties)
        if (parts.size() >= 2)
        {
            // Fusionner les deux premières parties dans la première colonne
            QString date = parts.takeFirst();
            QString type = parts.takeFirst();
            QString data = parts.join(" "); // Rejoindre les parties restantes pour obtenir les données
            rowItems << new QStandardItem(date);
            rowItems << new QStandardItem(type);
            rowItems << new QStandardItem(data);}




        else
        {
            // Si moins de 2 parties, ajouter des cellules vides
            for (int i = 0; i < 3; ++i) {
                rowItems << new QStandardItem("");
            }
        }

        model->appendRow(rowItems);



    }

    // Fermeture du fichier après lecture
    file.close();

    ui->historiqueTable->setModel(model);}



