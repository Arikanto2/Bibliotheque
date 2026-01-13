#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connexion_mysql.h"
#include "gestion_lecteur.h"
#include "gestion_login.h"
#include "gestion_livre.h"
#include "gestion_stat.h"
#include "gestion_acceuil.h"
#include "gestion_sanction.h"
#include "gestion_emprunter.h"
#include "gestion_remise.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    connexiondb();// connexion a la base de donnee
    lecteurs_voraces();
    valeur_permanente();
    ui->date_edition_sanction->setDate(QDate::currentDate());
    ui->dateEdit_DateAjout_emprunter->setDate(QDate::currentDate());
    ui->dateEdit_DateAjoutLecteur_nouveau->setDate(QDate::currentDate()); // mis a jours la date dans l'ajout lecteur
    ui->dateTimeEdit_acceuil->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_acceuil_2->setDateTime(QDateTime::currentDateTime());
    setupTableView_lecteur();                                             // connexion du tableview_lecteur avec la table a la base table lecteur
    setupTableView_livre();
    setupTableView_sanction();
    setupTableView_emprunter();
    setupTableView_remise();
    clearchamp();
    clearchamp_Livre();// reinitialiser les champs
    statistique_1();
    statistique_2();
    statistique_3();
    // Configuration du QTimer pour mettre à jour l'heure toutes les secondes
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    timer->start(1); // Met à jour toutes les secondes

    // Mise à jour initiale
    updateTime();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_quitter_clicked()
{
    if(QMessageBox::question(this,"Quitter:","Quitter l'application :<br> gestion de bibliothique?",  (QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No){
        ui->stackedWidget->setCurrentIndex(0);
    }else{
        QMessageBox::information(this, "information", "Vous avez quitter l'application , <br> Have a good day!!!");
        this->close();
    }
}

void MainWindow::updateTime() {
    // Obtenir l'heure actuelle
    QTime currentTime = QTime::currentTime();
    // Mettre à jour le widget QTimeEdit
    ui->dateTimeEdit_acceuil->setTime(currentTime);
    ui->dateTimeEdit_acceuil_2->setTime(currentTime);

}

void MainWindow::on_commandLinkButton_seDeconnect_clicked(){
    if(QMessageBox::question(this,"deconnection:","Se deconnecter ?",  (QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No){
        ui->stackedWidget->setCurrentIndex(1);
    }else{
        QMessageBox::information(this, "deconnection", "Vous avez deconnecter");
        ui->stackedWidget->setCurrentIndex(0);
        ui->non_login->clear();
        ui->Mdp_login->clear();
    }
}

void MainWindow::on_Menu_Sanctions_clicked()
{
    model_sanction->select();
    ui->changed_zone->setCurrentIndex(1);
}


void MainWindow::on_Menu_Acceuil_clicked()
{
    lecteurs_voraces();
    ui->changed_zone->setCurrentIndex(0);
}


void MainWindow::on_Menu_Lecteurs_clicked()
{
    model_lecteur->setFilter("actif = 1") ;
    model_lecteur->select();
    ui->changed_zone->setCurrentIndex(2);
    ui->stackedWidget_gerer_lecteur->setCurrentIndex(0);
}



void MainWindow::on_commandLinkButton_mdpOublie_clicked()
{
    QMessageBox::information(this,"avertissement","demander le mot de passe à votre superieur");
}


void MainWindow::on_Menu_Livres_clicked()
{
    ui->changed_zone->setCurrentIndex(3);
    ui->stackedWidget_gerer_livre->setCurrentIndex(0);
}

void MainWindow::on_Bouton_Inscription_clicked()
{
    QPixmap photoParDefaut(":/image/icone/images.png"); // Chemin de l'image par défaut
    ui->label_image_lecteur_nouveau->setPixmap(photoParDefaut.scaled(ui->label_image_lecteur_nouveau->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QSqlQuery query;
    query.prepare("SELECT MAX(NUM_LECTEUR) FROM gestion_bibliotheque.lecteur");

    if (query.exec()) {
        if (query.next()) {
            int maxValue = query.value(0).toInt();  // Récupérer la valeur maximale
            ui->spinBox_IDLecteur_nouveau->setValue((maxValue)+1);           // Affecter la valeur dans la spinBox
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
    }
    // Stockez cette image comme "photo actuelle"
    photoActuelle = photoParDefaut;
    ui->changed_zone->setCurrentIndex(2);
    ui->stackedWidget_gerer_lecteur->setCurrentIndex(1);
}


void MainWindow::on_Bouton_remise_livre_clicked()
{
    ui->IDLecteur->clear();
    ui->IDLivre->clear();
    ui->changed_zone->setCurrentIndex(3);
    ui->stackedWidget_gerer_livre->setCurrentIndex(8);
}

void MainWindow::on_pushButton_retour_stat_clicked()
{
    ui->changed_zone->setCurrentIndex(4);
}
void MainWindow::valeur_permanente(){
    QSqlQuery query, query2, query3, query4;
    query.prepare("SELECT count(*) FROM gestion_bibliotheque.lecteur WHERE actif = 1");
    query2.prepare("SELECT count(*) FROM gestion_bibliotheque.livre WHERE actif = 1");
    query3.prepare("SELECT count(*) FROM gestion_bibliotheque.emprunter");
    query4.prepare("SELECT count(*) FROM gestion_bibliotheque.sanction");
    if(query.exec()){
        query.next();
        int nbr_lecteur = query.value(0).toInt();
        ui->spinBox_nbr_lecteur->setValue(nbr_lecteur);
        qDebug() << nbr_lecteur;
    }
    if(query2.exec()){
        query2.next();
        int nbr_livre = query2.value(0).toInt();
        ui->spinBox_nbr_livre->setValue(nbr_livre);
        qDebug() << nbr_livre;
    }
    if(query3.exec()){
        query3.next();
        int nbr_emprunte = query3.value(0).toInt();
        ui->spinBox_nbr_emprunte->setValue(nbr_emprunte);
        qDebug() << nbr_emprunte;
    }
    if(query4.exec()){
        query4.next();
        int nbr_sanction = query4.value(0).toInt();
        ui->spinBox_nbr_sanction->setValue(nbr_sanction);
        qDebug() << nbr_sanction;
    }
}
void MainWindow::on_Menu_Pret_clicked()
{
    int rowCount = model_remise->rowCount();
    ui->spinBox_nombre_remise->setValue(rowCount);
    ui->changed_zone->setCurrentIndex(3);
    ui->stackedWidget_gerer_livre->setCurrentIndex(9);
}
