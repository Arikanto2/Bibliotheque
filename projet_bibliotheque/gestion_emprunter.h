#ifndef GESTION_EMPRUNTER_H
#define GESTION_EMPRUNTER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QAbstractItemView>
void MainWindow::on_pushButton_recherche_pret_clicked()
{
    QString recherche = ui->lineEdit_numLecteur_codeLivre_recherche_pret->text();
    model_emprunter->setFilter(QString("NUM_LECTEUR LIKE '%%1%' OR CODE_LIVRE LIKE '%%1%'").arg(recherche));
    model_emprunter->select();
    int rowCount = model_emprunter->rowCount();
    ui->spinBox_pret->setValue(rowCount);
}
void MainWindow::on_pushButton_actualiser_liste_pret_clicked()
{
    ui->lineEdit_numLecteur_codeLivre_recherche_pret->clear();
    model_emprunter->setFilter("");
    model_emprunter->select();
    int rowCount = model_emprunter->rowCount();
    ui->spinBox_pret->setValue(rowCount);
}
void MainWindow::on_emprunter_annuler_clicked()
{
    if (QMessageBox::warning(this, ("Retour"),
                             ("Voulez-vous vraiment annuler ?"),
                             (QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No)
    {
        ui->stackedWidget_gerer_lecteur->setCurrentIndex(6);
    }
    else{
        ui->edit_livre_recherche->clear();
        ui->edit_lecteur_recherche->clear();
        ui->changed_zone->setCurrentIndex(3);
        ui->stackedWidget_gerer_livre->setCurrentIndex(4);
    }
}

void MainWindow::on_Bouton_pretLivre_clicked()
{
    ui->edit_livre_recherche->clear();
    ui->edit_lecteur_recherche->clear();
    int rowCount = model_emprunter->rowCount();
    ui->spinBox_pret->setValue(rowCount);
    ui->changed_zone->setCurrentIndex(3);
    ui->stackedWidget_gerer_livre->setCurrentIndex(4);
}

void MainWindow::on_Bouton_pretLivre_3_clicked()
{
    QString livre = ui->edit_livre_recherche->text();
    QString lecteur = ui->edit_lecteur_recherche->text();
    if(livre == "" || lecteur == ""){
        QMessageBox::warning(this,"Avertissement", "Champs vides!!");
    }else{
    bool livretrouver = false;
    bool lecteurtrouver = false;
    QSqlQuery query7;
    query7.prepare("SELECT NUM_LECTEUR FROM gestion_bibliotheque.lecteur  WHERE (actif = 1) AND (NUM_LECTEUR = :num_lecteur)");
    query7.bindValue(":num_lecteur", lecteur);
    if (query7.exec()){
        if(query7.next()){
            QString num = query7.value(0).toString();
            if(!(num == "")){
                lecteurtrouver = true;
            }else{
                lecteurtrouver = false;
            }
        }
    }

    QSqlQuery query4;
    query4.prepare("SELECT NUM_LECTEUR FROM gestion_bibliotheque.emprunter WHERE NUM_LECTEUR = :num_lecteur");
    query4.bindValue(":num_lecteur", lecteur);
    if(query4.exec()){
        if(query4.next()){
            QString num = (query4.value(0)).toString();
            if(!(num == "")){
                QMessageBox::information(this,"Avertissement" ,"vous avez encore une livre a rendre!!!");
                ui->edit_livre_recherche->clear();
                ui->edit_lecteur_recherche->clear();
                model_emprunter->select();
                ui->changed_zone->setCurrentIndex(3);
                ui->stackedWidget_gerer_livre->setCurrentIndex(7);
                return;
            }
        }
    }

    QSqlQuery query1;
    query1.prepare("SELECT NUM_LECTEUR FROM gestion_bibliotheque.sanction WHERE NUM_LECTEUR = :num_lecteur");
    query1.bindValue(":num_lecteur", lecteur);
    if(!query1.exec()){
      //  QMessageBox::critical(this, "Erreur", query1.lastError().text());
    }else if(query1.next()){
        QString num = (query1.value(0)).toString();
        if(!(num == "")){
        ui->changed_zone->setCurrentIndex(1);
        QMessageBox::warning(this,"Avertissement", "Vous avez encore des sanctions a regler avant de preter une autre livre");
        return;
        }
    }

    QSqlQuery query9;
    query9.prepare("SELECT CODE_LIVRE FROM gestion_bibliotheque.livre  WHERE (actif = 1) AND (CODE_LIVRE = :code_livre)");
    query9.bindValue(":code_livre", livre);
    if (!query9.exec()) {
        QMessageBox::critical(this, "Erreur", query9.lastError().text());
    } else {
        if(query9.next()){
            QString code = (query9.value(0)).toString();
            if(!(code == "")){
                livretrouver = true;
            }else{
                livretrouver = false;
           }
        }
    }
    QSqlQuery query2;
    QString disponibilite;
    query2.prepare("SELECT DISPONIBILITE FROM gestion_bibliotheque.livre WHERE (actif = 1) AND (CODE_LIVRE =:code_livre)");
    query2.bindValue(":code_livre", livre);
    if(query2.exec()){
        if(query2.next()){
            disponibilite = (query2.value(0)).toString();
            qDebug() << disponibilite;
        }
    }
    if(!lecteurtrouver){
        QMessageBox::information(this, "LECTEUR", "Lecteur non trouver");
        model_lecteur->select();
        ui->changed_zone->setCurrentIndex(2);
        ui->stackedWidget_gerer_lecteur->setCurrentIndex(0);
        return;
    }else if(!livretrouver){
        QMessageBox::information(this, "Livre", "livre non trouve");
        ui->stackedWidget_gerer_livre->setCurrentIndex(1);
        return;
    }else if(disponibilite == "NON"){
        QMessageBox::information(this, "disponibilite livre", "livre non disponible");
        ui->stackedWidget_gerer_livre->setCurrentIndex(1);
        return;
    }else{
        QMessageBox::information(this,"avertissement","livre et lecteur trouvés");
        ui->changed_zone->setCurrentIndex(3);
        ui->stackedWidget_gerer_livre->setCurrentIndex(6);
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM gestion_bibliotheque.emprunter");
        if (query.exec()) {
            if (query.next()) {
                int maxValue = query.value(0).toInt();
                ui->spinBox_IDpret->setValue((maxValue+1));
                ui->emprunt_livre->setText(livre);
                ui->emprunt_lecteur->setText(lecteur);

                QDate date1 = ui->dateEdit_DateAjout_emprunter->date();
                QDate date2 = date1.addDays(7);
                ui->dateEdit_Datelimite_emprunter->setDate(date2);
            }
        }
    }
}
}

void MainWindow::setupTableView_emprunter()
{
    model_emprunter = new QSqlTableModel;
    model_emprunter->setTable("emprunter");
    model_emprunter->select();
    ui->tableView_Liste_emprunter->setModel(model_emprunter);
    model_emprunter->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_Liste_emprunter->setSelectionMode(QAbstractItemView::SingleSelection); // Sélection d'une seule ligne
    ui->tableView_Liste_emprunter->setSelectionBehavior(QAbstractItemView::SelectRows); // Sélectionne la ligne entière
    ui->tableView_Liste_emprunter->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int rowCount = model_emprunter->rowCount();
    ui->spinBox_pret->setValue(rowCount);

    ui->tableView_Liste_emprunter->resizeColumnToContents(0);
    ui->tableView_Liste_emprunter->resizeColumnToContents(1);
    ui->tableView_Liste_emprunter->resizeColumnToContents(2);
    ui->tableView_Liste_emprunter->resizeColumnToContents(3);
    ui->tableView_Liste_emprunter->resizeColumnToContents(4);

    model_emprunter->setHeaderData(0, Qt::Horizontal, QObject::tr("num pret"));
    model_emprunter->setHeaderData(1, Qt::Horizontal, QObject::tr("num Lecteur"));
    model_emprunter->setHeaderData(2, Qt::Horizontal, QObject::tr("code livre"));
    model_emprunter->setHeaderData(3, Qt::Horizontal, QObject::tr("Date prêt"));
    model_emprunter->setHeaderData(4, Qt::Horizontal, QObject::tr("Date limite"));
}

void MainWindow::on_Emprunter_livre_clicked()
{
    if (QMessageBox::warning(this, "Enregistrement", "Voulez-vous enregistrer ?", QMessageBox::No | QMessageBox::Yes) == QMessageBox::No) {
        QMessageBox::information(this, "Attention!", "Empreinte non réussie");
        ui->stackedWidget_gerer_livre->setCurrentIndex(6);
        return;
    }

    QString code_livre = ui->emprunt_livre->text();
    QString num_lecteur = ui->emprunt_lecteur->text();
    QDate Date_pret = ui->dateEdit_DateAjout_emprunter->date();
    QDate Date_limite = ui->dateEdit_Datelimite_emprunter->date();

    QSqlQuery princy;

    princy.prepare("INSERT INTO gestion_bibliotheque.emprunter (NUM_PRET, CODE_LIVRE, NUM_LECTEUR, DATE_PRET, DATE_LIMITE_PRET) VALUES (:num_pret, :code_livre, :num_lecteur, :Date_pret, :Date_limite)");
    princy.bindValue(":num_pret", ui->spinBox_IDpret->value());
    princy.bindValue(":code_livre", code_livre);
    princy.bindValue(":num_lecteur", num_lecteur);
    princy.bindValue(":Date_pret", Date_pret);
    princy.bindValue(":Date_limite", Date_limite);

    if (!princy.exec()) {
        QMessageBox::critical(this, "Erreur", princy.lastError().text());
        return;
    }

    // Mettre à jour le lecteur
    princy.prepare("UPDATE gestion_bibliotheque.lecteur SET NOMBRE_PRET_LECTEUR = NOMBRE_PRET_LECTEUR + 1 WHERE NUM_LECTEUR = :lecteur");
    princy.bindValue(":lecteur", num_lecteur);
    if (!princy.exec()) {
        QMessageBox::critical(this, "Erreur", princy.lastError().text());
        return;
    }

    // Mettre à jour le livre
    princy.prepare("UPDATE gestion_bibliotheque.livre SET DISPONIBILITE = 'NON', NOMBRE_PRET_LIVRE = NOMBRE_PRET_LIVRE + 1 WHERE CODE_LIVRE = :livre");
    princy.bindValue(":livre", code_livre);
    if (!princy.exec()) {
        QMessageBox::critical(this, "Erreur", princy.lastError().text());
        return;
    }

    QMessageBox::information(this, "Succès", "Données ajoutées avec succès !");
    model_emprunter->select();  // Charger les données
    ui->edit_livre_recherche->clear();
    ui->edit_lecteur_recherche->clear();
    int new_rowCount = model_emprunter->rowCount();
    ui->spinBox_pret->setValue(new_rowCount);
    ui->stackedWidget_gerer_livre->setCurrentIndex(7);
    valeur_permanente();
}

void MainWindow::on_afficher_prets_clicked()
{
    model_emprunter->select();
    ui->edit_livre_recherche->clear();
    ui->edit_lecteur_recherche->clear();
    int rowCount = model_emprunter->rowCount();
    ui->spinBox_pret->setValue(rowCount);
    ui->changed_zone->setCurrentIndex(3);
    ui->stackedWidget_gerer_livre->setCurrentIndex(7);
}

#endif // GESTION_EMPRUNTER_H
