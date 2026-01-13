#ifndef GESTION_SANCTION_H
#define GESTION_SANCTION_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QAbstractItemView>

/******************************************************************/
void MainWindow::on_pushButton_ajouter_Sanction_lecteur_clicked()
{
    ui->lineEdit_code_livre_nouveau_sanction->clear();
    ui->num_du_lecteur->clear();
    ui->Non_du_lecteur->clear();
    ui->Prenom_du_lecteur->clear();
    ui->Niveau_du_lecteur->clear();
    ui->date_edition_sanction->setDate(QDate::currentDate());
    ui->changed_zone->setCurrentIndex(3);
    ui->stackedWidget_gerer_livre->setCurrentIndex(5);
}

void MainWindow::setupTableView_sanction(){ // connexion a la table_sanction
    model_sanction = new QSqlTableModel;
    model_sanction->setTable("sanction");
    model_sanction->select();
    ui->tableView_liste_sanction->setModel(model_sanction);
    model_sanction->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_liste_sanction->setSelectionMode(QAbstractItemView::SingleSelection); // Sélection d'une seule ligne
    ui->tableView_liste_sanction->setSelectionBehavior(QAbstractItemView::SelectRows); // Sélectionne la ligne entière
    ui->tableView_liste_sanction->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int rowCount = model_sanction->rowCount();
    ui->spinBox_nombre_sanction->setValue(rowCount);

    model_sanction->setHeaderData(0, Qt::Horizontal, QObject::tr("num lecteur"));
    model_sanction->setHeaderData(1, Qt::Horizontal, QObject::tr("Code livre"));
    model_sanction->setHeaderData(2, Qt::Horizontal, QObject::tr("date du sanction"));
    model_sanction->setHeaderData(3, Qt::Horizontal, QObject::tr("Description sanction"));

    ui->tableView_liste_sanction->setColumnWidth(0,100);
    ui->tableView_liste_sanction->setColumnWidth(1,100);
    ui->tableView_liste_sanction->setColumnWidth(2, 120);
    ui->tableView_liste_sanction->setColumnWidth(3,600);
}

void MainWindow::Donner_sanction() { // envoyer les valeurs dans les formulaire dans la page sanction
    QString code_livre = ui->IDLivre->text();
    int num_lecteur = (ui->IDLecteur->text()).toInt();
    QString nom_lecteur, prenom_lecteur, niveau_lecteur;
    QSqlQuery query;
    query.prepare("SELECT NOM_LECTEUR, PRENOM_LECTEUR, NIVEAU_LECTEUR FROM gestion_bibliotheque.lecteur WHERE NUM_LECTEUR =:num_lecteur");
    query.bindValue(":num_lecteur", num_lecteur);
    if(query.exec()){
        if(query.next()){
        nom_lecteur = query.value(0).toString();
        prenom_lecteur = query.value(1).toString();
        niveau_lecteur = query.value(2).toString();
        }
    } else {
    qDebug() << "Erreur lors de l'exécution de la requête : " << query.lastError().text();
    }
    ui->lineEdit_code_livre_nouveau_sanction->setText(code_livre);
    ui->num_du_lecteur->setValue(num_lecteur);
    ui->Non_du_lecteur->setText(nom_lecteur);
    ui->Prenom_du_lecteur->setText(prenom_lecteur);
    ui->Niveau_du_lecteur->setText(niveau_lecteur);
    ui->date_edition_sanction->setDate(QDate::currentDate());
}

void MainWindow::on_Bouton_Retour_Sanction_clicked()
{
    if (QMessageBox::warning(this, ("Retour"),
                             ("Voulez-vous vraiment annuler ?"),
                             (QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No)
    {
        ui->stackedWidget_gerer_lecteur->setCurrentIndex(5);
    }
    else{
        clearchamp();
        ui->changed_zone->setCurrentIndex(2);
        ui->stackedWidget_gerer_lecteur->setCurrentIndex(0);
    }

}

void MainWindow::on_Bouton_Retour_Sanction_2_clicked()
{
    if (QMessageBox::warning(this, ("Retour"),
                             ("Voulez-vous vraiment annuler ?"),
                             (QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No)
    {
        ui->stackedWidget_gerer_lecteur->setCurrentIndex(5);
    }
    else{
        clearchamp();
        ui->changed_zone->setCurrentIndex(2);
        ui->stackedWidget_gerer_lecteur->setCurrentIndex(0);
    }

}


void MainWindow::on_Bouton_Sauvegarder_Sanction_clicked()
{
    QString num_lecteur =ui->num_du_lecteur->text();
    QString code_livre =ui->lineEdit_code_livre_nouveau_sanction->text();
    QDate date_sanction = ui->date_edition_sanction->date();
    QString description =ui->comboBox_liste_description_sanction->currentText();
    if(num_lecteur.isEmpty() || code_livre.isEmpty()){
        QMessageBox::warning(this, "Avertissement", "num_du_lecteur et code_livre ne devraient pas être vide!");
    }else{
    QSqlQuery query, query2, query3;
    query2.prepare("SELECT NUM_lECTEUR FROM gestion_bibliotheque.sanction WHERE NUM_LECTEUR =:num_lecteur");
    query2.bindValue(":num_lecteur", (num_lecteur).toInt());
    query3.prepare("SELECT CODE_LIVRE FROM gestion_bibliotheque.sanction WHERE CODE_LIVRE =:code_livre");
    query3.bindValue(":code_livre", code_livre);
    if(query2.exec() && query3.exec()){
        if(query2.next()){
            QString num = query2.value(0).toString();
            if(!num.isEmpty()){
                QMessageBox::warning(this, "Avertissement", "Le lecteur a déjà une sanction!");
                ui->changed_zone->setCurrentIndex(1);
                return;
            }
        }
        if(query3.next()){
            QString code = query3.value(0).toString();
            if(!code.isEmpty()){
                QMessageBox::warning(this, "Avertissement", "Un lecteur a déjà une sanction sur cette livre!!");
                ui->changed_zone->setCurrentIndex(1);
                return;
            }
        }
    }
    query.prepare("INSERT INTO gestion_bibliotheque.sanction (NUM_LECTEUR,CODE_LIVRE, DATE_SANCTION, DESCRIPTION_SANCTION)"
                  "VALUES(:num_lecteur,:code_livre,:date_sanction ,:description)");
    query.bindValue(":num_lecteur", (num_lecteur).toInt());
    query.bindValue(":code_livre", code_livre);
    query.bindValue(":date_sanction", date_sanction);
    query.bindValue(":description", description);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Erreur", query.lastError().text());

    }else
    {
        QMessageBox::information(this, "Succès", "Données ajoutées avec succès !");
        // clearchamp();
        model_sanction->select();  // Charger les données
    }
    int new_rowCount = model_sanction->rowCount();
    ui->spinBox_nombre_sanction->setValue(new_rowCount);
    ui->changed_zone->setCurrentIndex(1);
    valeur_permanente();
    }
}
void MainWindow::on_Bouton_Sauvegarder_modification_Sanction_clicked()
{
    QString num_lecteur =ui->num_du_lecteur_modification_sanction->text();
    QString code_livre =ui->lineEdit_code_livre_modification_sanction->text();
    QDate date_sanction = ui->date_edition_modification_sanction->date();
    QString description =ui->comboBox_liste_description_modification_sanction->currentText();
    if(num_lecteur.isEmpty() || code_livre.isEmpty()){
        QMessageBox::warning(this, "Avertissement", "num_du_lecteur et code_livre ne devraient pas être vide!");
    }else{
    QSqlQuery query;
    query.prepare("UPDATE gestion_bibliotheque.sanction SET DATE_SANCTION=:date_sanction, DESCRIPTION_SANCTION =:description WHERE NUM_LECTEUR =:num_lecteur AND CODE_LIVRE =:code_livre");
    query.bindValue(":num_lecteur", num_lecteur);
    query.bindValue(":code_livre", code_livre);
    query.bindValue(":date_sanction", date_sanction);
    query.bindValue(":description", description);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Erreur", query.lastError().text());

    }else
    {
        QMessageBox::information(this, "Succès", "Données modifier avec succès !");
        // clearchamp();
        model_sanction->select();  // Charger les données
    }
    int new_rowCount = model_sanction->rowCount();
    ui->spinBox_nombre_sanction->setValue(new_rowCount);
    ui->changed_zone->setCurrentIndex(1);
    valeur_permanente();
    }
}

void MainWindow::on_Bouton_Supprimer_Sanction_clicked()
{
    QModelIndex currentIndex = ui->tableView_liste_sanction->selectionModel()->currentIndex();
    if (!currentIndex.isValid())
    {
        qDebug() << "Aucune ligne sélectionnée.";
        QMessageBox::information(this,"Erreur", "Aucun ligne selectionner");
        ui->changed_zone->setCurrentIndex(1);
    }
    else
    {
        qDebug() << "Cellule sélectionnée : " << currentIndex.row() << ", " << currentIndex.column();
        if (QMessageBox::warning(this, ("Suppression"),("Voulez-vous supprimer?"),(QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No)
        {
            QMessageBox::information(this, ("Attention!"), ("suppression no reussit"));
            ui->changed_zone->setCurrentIndex(1);
        }
        else
        {
            QModelIndex currentIndex = ui->tableView_liste_sanction->selectionModel()->currentIndex();
            int row = currentIndex.row();

            // Récupérez la valeur de la ligne
            QString num_lecteur = model_sanction->data(model_sanction->index(row, 0)).toString();

            // Suppression du ligne selectionner dans la base
            QSqlQuery query;
            query.prepare("DELETE FROM gestion_bibliotheque.sanction  WHERE NUM_LECTEUR = :num_lecteur  ");
            query.bindValue(":num_lecteur", num_lecteur);

            if (!query.exec())
            {
                QMessageBox::critical(this, "Erreur", query.lastError().text());
            }
            else
            {
                QMessageBox::information(this, "Succès", "Données supprimer avec succès !");
                model_sanction->select(); // Rafraîchir les données du modèle
            }
        }

    }
    model_sanction->select();
    int new_rowCount = model_sanction->rowCount();
    ui->spinBox_nombre_sanction->setValue(new_rowCount);
    valeur_permanente();
}
void MainWindow::on_Bouton_Modifier_Sanction_clicked()
{
    QModelIndex currentIndex = ui->tableView_liste_sanction->selectionModel()->currentIndex();
    if (!currentIndex.isValid())
    {
        qDebug() << "Aucune ligne sélectionnée.";
        QMessageBox::information(this,"Erreur", "Aucun ligne selectionner");
        ui->changed_zone->setCurrentIndex(1);
    }
    else{
        QModelIndex currentIndex = ui->tableView_liste_sanction->selectionModel()->currentIndex();
        int row = currentIndex.row();

        // Récupérez la valeur de la ligne
        int num_lecteur = model_sanction->data(model_sanction->index(row, 0)).toInt();
        QString code_livre = model_sanction->data(model_sanction->index(row, 1)).toString();
        QDate date_ajout_sanction = model_sanction->data(model_sanction->index(row, 2)).toDate();
        QString description_sanction = model_sanction->data(model_sanction->index(row, 3)).toString();

        QString nom_lecteur, prenom_lecteur, niveau_lecteur;
        QSqlQuery query;
        query.prepare("SELECT NOM_LECTEUR, PRENOM_LECTEUR, NIVEAU_LECTEUR FROM gestion_bibliotheque.lecteur WHERE NUM_LECTEUR =:num_lecteur");
        query.bindValue(":num_lecteur", num_lecteur);
        if(query.exec()){
            if(query.next()){
                nom_lecteur = query.value(0).toString();
                prenom_lecteur = query.value(1).toString();
                niveau_lecteur = query.value(2).toString();
            }
        } else {
            qDebug() << "Erreur lors de l'exécution de la requête : " << query.lastError().text();
        }
        ui->lineEdit_code_livre_modification_sanction->setText(code_livre);
        ui->num_du_lecteur_modification_sanction->setValue(num_lecteur);
        ui->Non_du_lecteur_modification_sanction->setText(nom_lecteur);
        ui->Prenom_du_lecteur_modification_sanction->setText(prenom_lecteur);
        ui->Niveau_du_lecteur_modification_sanction->setText(niveau_lecteur);
        ui->date_edition_modification_sanction->setDate(date_ajout_sanction);
        ui->comboBox_liste_description_modification_sanction->setEditText(description_sanction);

        ui->changed_zone->setCurrentIndex(3);
        ui->stackedWidget_gerer_livre->setCurrentIndex(10);
    }
}

void MainWindow::on_Bouton_recherche_sanction_clicked()
{
    QString recherche = ui->lineEdit_sanction_recherche->text();
    model_sanction->setFilter(QString("NUM_LECTEUR LIKE '%%1%' OR CODE_LIVRE LIKE '%%1%'").arg(recherche));
    model_sanction->select();
    int rowCount = model_sanction->rowCount();
    ui->spinBox_nombre_sanction->setValue(rowCount);
}


void MainWindow::on_Bouton_Actualiser_Sanction_clicked()
{
    //clearchamps();
    ui->lineEdit_sanction_recherche->clear();
    model_sanction->setFilter("");
    model_sanction->select();
    int new_rowCount = model_sanction->rowCount();
    ui->spinBox_nombre_sanction->setValue(new_rowCount);
}


#endif
