#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "abonne.h"
#include "calendar.h"
#include <QMainWindow>
#include <QSqlQueryModel>
#include <QDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;

             }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
     Abonne Abpm;
private slots:
    //void on_label_5_linkActivated(const QString &link);

    //void on_label_5_customContextMenuRequested(const QPoint &pos);
    void on_ajouter_clicked();
   // void on_pushButton_supprimer_clicked();
    //void on_label_21_linkActivated(const QString &link);

    //void on_tableView_2_clicked(const QModelIndex &index);

    //void on_pushButton_2_clicked();



    void recupererAbonne(const QString& cinText);
    void vider(const QString &text);
    void on_pushButton_2_clicked();

    void on_modfier_clicked();



    //void on_supprimer_clicked();



    //void on_recherche_id_clicked();

    //void on_recherche_nom_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_cherch_nom_textChanged(const QString &arg1);

    //void on_pdf_clicked();

    void on_commandLinkButton_clicked();

    //void on_progressBar_valueChanged(int value);

    //void on_abs_currentChanged(int index);

    //void on_openGLWidget_2_aboutToResize();

    void on_openGLWidget_2_aboutToResize();

    void on_openGLWidget_aboutToResize();

    void on_openGLWidget_3_aboutToResize();

    void on_openGLWidget_4_aboutToResize();

    void on_openGLWidget_5_aboutToResize();

    void on_pdf_clicked();

    //void on_pushButton_5_clicked();
    void supp();
    void modif();
    void affcal();




    //void on_pushButton_6_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
