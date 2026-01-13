#ifndef GESTION_REMISE_H
#define GESTION_REMISE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QAbstractItemView>

void MainWindow::on_pushButton_recherche_remise_clicked()
{
    QString num_lecteur = ui->lineEdit_numLecteur_recherche_remise->text();
    QDate date1 = ui->dateEdit_date1_recherche_remise->date();
    QDate date2 = ui->dateEdit_date2_recherche_remise->date();
    if (num_lecteur.isEmpty()) {
        // Si num_lecteur est vide, ne filtre que sur les dates
        QString filter = QString("DATE_EMPRUNTE BETWEEN '%1' AND '%2'")
                             .arg(date1.toString("yyyy-MM-dd"))
                             .arg(date2.toString("yyyy-MM-dd"));
        model_remise->setFilter(filter);
    } else {
        // Sinon, filtrer sur num_lecteur et les dates
        QString filter = QString("NUM_LECTEUR = '%1' AND DATE_EMPRUNTE BETWEEN '%2' AND '%3'")
                             .arg(num_lecteur)
                             .arg(date1.toString("yyyy-MM-dd"))
                             .arg(date2.toString("yyyy-MM-dd"));
        model_remise->setFilter(filter);
    }

    model_remise->select();
    int rowCount = model_remise->rowCount();
    ui->spinBox_nombre_remise->setValue(rowCount);
}
void MainWindow::on_pushButton_actualiser_tableremise_clicked()
{
    ui->lineEdit_numLecteur_recherche_remise->clear();
    model_remise->setFilter("");
    model_remise->select();
    int rowCount = model_remise->rowCount();
    ui->spinBox_nombre_remise->setValue(rowCount);
}
void MainWindow::on_Bouton_valide_remise_clicked()
{
    int IDLecteur = (ui->IDLecteur->text()).toInt();
    QString IDLivre = ui->IDLivre->text();
    if((ui->IDLecteur->text()).isEmpty() || IDLivre.isEmpty()){
        QMessageBox::warning(this, "Avertissement", "Les champs ne devraient pas être vide!!!");
    }else{
    QDate currentDate = ui->dateTimeEdit_acceuil->date();
    QDate date_limite_pret;
    QDate date_pret;
    bool correspond = false;
    int num_remise ;
    QSqlQuery requete, requete1, requete2, requete3, requete4, requete5;
    requete3.prepare("SELECT max(NUM_REMISE) FROM gestion_bibliotheque.remise");
    if(requete3.exec()){
        if(requete3.next()){
            num_remise = ((requete3.value(0)).toInt()) + 1 ;
        }
    }
    requete.prepare("SELECT NUM_LECTEUR, CODE_LIVRE, DATE_PRET, DATE_LIMITE_PRET FROM gestion_bibliotheque.emprunter WHERE NUM_LECTEUR = :IDLecteur AND CODE_LIVRE = :IDLivre");
    requete.bindValue(":IDLecteur", IDLecteur);
    requete.bindValue(":IDLivre", IDLivre);
    if(!requete.exec()){
        QMessageBox::critical(this, "Erreur", requete.lastError().text());
    }else if(!requete.next()){
        correspond = false;
        QMessageBox::warning(this, "Avertissement", "Emprunte inexistant!!!");
    }else {
        date_limite_pret = requete.value(3).toDate();
        date_pret = requete.value(2).toDate();
        qDebug() << date_pret << date_limite_pret << currentDate;
        correspond = true;
        requete5.prepare("SELECT DATEDIFF(:currentDate, :date_limite_pret)");
        requete5.bindValue(":currentDate", currentDate);
        requete5.bindValue(":date_limite_pret", date_limite_pret);
        if(!requete5.exec()){
            QMessageBox::critical(this, "Erreur", requete.lastError().text());
        }else if(!requete5.next()){
            QMessageBox::critical(this, "Erreur", requete.lastError().text());
        }else{
            int jour = requete5.value(0).toInt();
            qDebug() << "jour:" << jour;
            if(jour > 7){
                QMessageBox::information(this, "Sanction", "Sanction pour le lecteur pour non respect du date limite:<br> Amende de 5000Ar!");
                ui->changed_zone->setCurrentIndex(3);
                ui->stackedWidget_gerer_livre->setCurrentIndex(5);
                Donner_sanction();
                requete1.prepare("UPDATE gestion_bibliotheque.livre SET DISPONIBILITE = 'OUI' where CODE_LIVRE = :IDLivre ;");
                requete2.prepare("INSERT INTO gestion_bibliotheque.remise (NUM_REMISE, NUM_LECTEUR, CODE_LIVRE, DATE_EMPRUNTE, DATE_REMISE) VALUES (:num_remise, :IDLecteur, :IDLivre, :date_emprunte, :currentDate)");
                requete4.prepare("DELETE FROM gestion_bibliotheque.emprunter WHERE (NUM_LECTEUR =:num_lecteur ) and (CODE_LIVRE =:code_livre)");
                requete1.bindValue(":IDLivre", IDLivre);
                requete2.bindValue(":IDLivre", IDLivre);
                requete2.bindValue(":IDLecteur", IDLecteur);
                requete2.bindValue(":num_remise", num_remise);
                requete2.bindValue(":date_emprunte", date_pret);
                requete2.bindValue(":currentDate", currentDate);
                requete4.bindValue(":num_lecteur", IDLecteur);
                requete4.bindValue(":code_livre", IDLivre);
                if(!(requete1.exec() && requete2.exec() && requete4.exec())){
                    QMessageBox::critical(this, "Erreur", requete1.lastError().text());
                    QMessageBox::critical(this, "Erreur", requete2.lastError().text());
                    QMessageBox::critical(this, "Erreur", requete4.lastError().text());
                }
                else{
                    model_remise->select();
                    model_livre->select();
                    model_emprunter->select();
                    QMessageBox::information(this, tr("VALIDATION"), "Livre remis");
                    int rowCount = model_remise->rowCount();
                    ui->spinBox_nombre_remise->setValue(rowCount);
                    int rowCount1 = model_emprunter->rowCount();
                    ui->spinBox_pret->setValue(rowCount1);
                    valeur_permanente();
                    return;
            }
            }else{
                    if(correspond == false){
                        QMessageBox::warning(this, "Avertissement", "IDLecteur ne correspond pas a l'IDLivre preter ou pret inexistant!");
                    }else {
                    requete1.prepare("UPDATE gestion_bibliotheque.livre SET DISPONIBILITE = 'OUI' where CODE_LIVRE = :IDLivre ;");
                    requete2.prepare("INSERT INTO gestion_bibliotheque.remise (NUM_REMISE, NUM_LECTEUR, CODE_LIVRE, DATE_EMPRUNTE , DATE_REMISE) VALUES (:num_remise, :IDLecteur, :IDLivre, :date_pret, :currentDate)");
                    requete4.prepare("DELETE FROM gestion_bibliotheque.emprunter WHERE (NUM_LECTEUR =:num_lecteur ) and (CODE_LIVRE =:code_livre)");
                    requete1.bindValue(":IDLivre", IDLivre);
                    requete2.bindValue(":IDLivre", IDLivre);
                    requete2.bindValue(":IDLecteur", IDLecteur);
                    requete2.bindValue(":num_remise", num_remise);
                    requete2.bindValue(":date_pret", date_pret);
                    requete2.bindValue(":currentDate", currentDate);
                    requete4.bindValue(":num_lecteur", IDLecteur);
                    requete4.bindValue(":code_livre", IDLivre);
                    if(!(requete1.exec() && requete2.exec() && requete4.exec())){
                        QMessageBox::critical(this, "Erreur", requete1.lastError().text());
                        QMessageBox::critical(this, "Erreur", requete2.lastError().text());
                        QMessageBox::critical(this, "Erreur", requete4.lastError().text());
                    }
                    else{

                        model_remise->select();
                        model_livre->select();
                        model_emprunter->select();
                        QMessageBox::information(this, tr("VALIDATION"), "Livre remis");
                        int rowCount = model_remise->rowCount();
                        ui->spinBox_nombre_remise->setValue(rowCount);
                        int rowCount1 = model_emprunter->rowCount();
                        ui->spinBox_pret->setValue(rowCount1);
                        valeur_permanente();
                        if(QMessageBox::question(this,"Sanction", "Voulez-vous donner une sanction a l'utilisateur?", (QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No){
                            ui->changed_zone->setCurrentIndex(3);
                            ui->stackedWidget_gerer_livre->setCurrentIndex(9);
                        }else{
                            ui->changed_zone->setCurrentIndex(3);
                            ui->stackedWidget_gerer_livre->setCurrentIndex(5);
                            Donner_sanction();
                            QMessageBox::information(this, tr("Sanction"), "Choisit la sanction");
                            }
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::on_afficher_livre_remis_clicked()
{
    int rowCount = model_remise->rowCount();
    ui->spinBox_nombre_remise->setValue(rowCount);
    ui->changed_zone->setCurrentIndex(3);
    ui->stackedWidget_gerer_livre->setCurrentIndex(9);
}

void MainWindow::setupTableView_remise()
{
    model_remise = new QSqlTableModel;
    model_remise->setTable("remise");
    model_remise->select();
    ui->tableView_Liste_remise->setModel(model_remise);
    model_remise->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_Liste_remise->setSelectionMode(QAbstractItemView::SingleSelection); // Sélection d'une seule ligne
    ui->tableView_Liste_remise->setSelectionBehavior(QAbstractItemView::SelectRows); // Sélectionne la ligne entière
    ui->tableView_Liste_remise->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int rowCount = model_remise->rowCount();
    ui->spinBox_nombre_remise->setValue(rowCount);

    ui->tableView_Liste_remise->setColumnWidth(0,90);
    ui->tableView_Liste_remise->setColumnWidth(1,90);
    ui->tableView_Liste_remise->setColumnWidth(2,90);
    ui->tableView_Liste_remise->setColumnWidth(3,100);
    ui->tableView_Liste_remise->setColumnWidth(4,100);

    model_remise->setHeaderData(0, Qt::Horizontal, QObject::tr("num remise"));
    model_remise->setHeaderData(1, Qt::Horizontal, QObject::tr("num lecteur"));
    model_remise->setHeaderData(2, Qt::Horizontal, QObject::tr("code livre"));
    model_remise->setHeaderData(3, Qt::Horizontal, QObject::tr("date pret"));
    model_remise->setHeaderData(4, Qt::Horizontal, QObject::tr("date remise"));
}
#endif // GESTION_REMISE_H
