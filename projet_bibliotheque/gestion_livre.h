#ifndef GESTION_LIVRE_H
#define GESTION_LIVRE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QAbstractItemView>

void MainWindow::clearchamp_Livre(){ //reinitialiser les champs
    ui->code_livre_2->clear();
    ui->designation_livre_2->clear();
    ui->auteur_2->clear();
    ui->date_edition_livre->setDate(QDate(2000, 1 ,1));

    ui->modifier_code_livre_2->clear();
    ui->modifier_designation_livre_2->clear();
    ui->modifier_date_edition_2->setDate(QDate(2000, 1 ,1));
    ui->modifier_auteur_2->clear();
    ui->modifier_pret_2->clear();
}


void MainWindow::setupTableView_livre(){
    model_livre = new QSqlTableModel;
    model_livre->setTable("livre");
    model_livre->setFilter("actif = 1");
    model_livre->select();
    ui->tableView_Liste_Livre_2->setModel(model_livre);
    model_livre->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_Liste_Livre_2->setSelectionMode(QAbstractItemView::SingleSelection); // Sélection d'une seule ligne
    ui->tableView_Liste_Livre_2->setSelectionBehavior(QAbstractItemView::SelectRows); // Sélectionne la ligne entière
    ui->tableView_Liste_Livre_2->setEditTriggers(QAbstractItemView::NoEditTriggers); // Désactiver l'édition

    ui->tableView_Liste_Livre_2->hideColumn(7);

    int rowCount = model_livre->rowCount();
    ui->spinBox_Nombre_Livre_2->setValue(rowCount);

    ui->tableView_Liste_Livre_2->resizeColumnToContents(0);
    ui->tableView_Liste_Livre_2->resizeColumnToContents(1);
    ui->tableView_Liste_Livre_2->resizeColumnToContents(2);
    ui->tableView_Liste_Livre_2->resizeColumnToContents(3);
    ui->tableView_Liste_Livre_2->resizeColumnToContents(4);
    ui->tableView_Liste_Livre_2->resizeColumnToContents(5);
    ui->tableView_Liste_Livre_2->resizeColumnToContents(6);

    model_livre->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model_livre->setHeaderData(1, Qt::Horizontal, QObject::tr("Désignation"));
    model_livre->setHeaderData(2, Qt::Horizontal, QObject::tr("Auteur"));
    model_livre->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_edition"));
    model_livre->setHeaderData(4, Qt::Horizontal, QObject::tr("Disponibilité"));
    model_livre->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre de prêt"));
    model_livre->setHeaderData(6, Qt::Horizontal, QObject::tr("Categorie"));

}

void MainWindow::on_tableView_Liste_Livre_2_clicked(const QModelIndex &index2) // recuperer l'indexe de la ligne selectionner
{
    selectedRow2 = index2.row();
    loadSelectedRowData2_livre(selectedRow2);
}

void MainWindow::loadSelectedRowData2_livre(int row2) { // envoyer les valeurs da la tableview dans la page modification
    QString code_livre = model_livre->data(model_livre->index(row2,0)).toString();
    QString designation = model_livre->data(model_livre->index(row2, 1)).toString();
    QString auteur = model_livre->data(model_livre->index(row2, 2)).toString();
    QDate date_edition = model_livre->data(model_livre->index(row2, 3)).toDate();
    QString disponibilite = model_livre->data(model_livre->index(row2, 4)).toString();
    QString nb_pret = model_livre->data(model_livre->index(row2, 5)).toString();
    QString categorie = model_livre->data(model_livre->index(row2, 6)).toString();

    ui->modifier_code_livre_2->setText(code_livre);
    ui->modifier_designation_livre_2->setText(designation);
    ui->modifier_date_edition_2->setDate(date_edition);
    ui->modifier_categorie_2->setCurrentText(categorie);
    ui->modifier_auteur_2->setText(auteur);
    ui->modifier_disponibilite_2->setCurrentText(disponibilite);
    ui->modifier_pret_2->setText(nb_pret);
}

void MainWindow::on_pushButton_ajouter_livre_clicked()
{
    clearchamp_Livre();

    int rowCount = model_livre->rowCount();
    ui->spinBox_Nombre_Livre_2->setValue(rowCount);
    ui->stackedWidget_gerer_livre->setCurrentIndex(2);
}

void MainWindow::on_pushButton_modifier_livre_clicked()
{
    QModelIndex currentIndex = ui->tableView_Liste_Livre_2->selectionModel()->currentIndex();
    if (!currentIndex.isValid()) {
        qDebug() << "Aucune ligne sélectionnée.";
        QMessageBox::information(this,"Erreur", "Aucun ligne selectionner");
        ui->stackedWidget_gerer_livre->setCurrentIndex(1);
    }
    else
    {
        qDebug() << "Cellule sélectionnée : " << currentIndex.row() << ", " << currentIndex.column();
        ui->stackedWidget_gerer_livre->setCurrentIndex(3);
    }
}

void MainWindow::on_pushButton_afficher_tous_livre_clicked()
{
    clearchamp();
    ui->lineEdit_Recherche_Livre->clear();
    model_livre->setFilter("actif = 1");
    model_livre->select();
    int new_rowCount = model_livre->rowCount();
    ui->spinBox_Nombre_Livre_2->setValue(new_rowCount);
    ui->stackedWidget_gerer_livre->setCurrentIndex(1);
}

void MainWindow::on_annuler_3_clicked()
{
    if (QMessageBox::warning(this, ("Annulation de inscription"),
                             ("Voulez-vous annuler l'inscription?"),
                             (QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No)
    {
        ui->stackedWidget_gerer_livre->setCurrentIndex(2);
    }
    else{
        clearchamp();
        model_livre->setFilter("actif = 1");
        model_livre->select();
        ui->changed_zone->setCurrentIndex(3);
        ui->stackedWidget_gerer_livre->setCurrentIndex(1);
    }
}
void MainWindow::on_annuler_4_clicked()
{
    if (QMessageBox::warning(this, ("Annulation des modifications"),
                             ("Voulez-vous annuler les modifications?"),
                             (QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No)
    {
        ui->stackedWidget_gerer_livre->setCurrentIndex(3);
    }
    else{
        clearchamp();
        model_livre->setFilter("actif = 1");
        model_livre->select();
        //ui->stackedWidget_gerer_livre->setCurrentIndex(1);
        ui->changed_zone->setCurrentIndex(3);
        ui->stackedWidget_gerer_livre->setCurrentIndex(1);
    }
}

void MainWindow::on_pushButton_Recherche_Livre_clicked()
{
    QString recherche = ui->lineEdit_Recherche_Livre->text();
    model_livre->setFilter(QString("actif = 1 AND (CODE_LIVRE LIKE '%%1%' OR DESIGNATION_LIVRE LIKE '%%1%')").arg(recherche));
    model_livre->select();
    int rowCount = model_livre->rowCount();
    ui->spinBox_Nombre_Livre_2->setValue(rowCount);
}

void MainWindow::on_pushButton_Actualiser_Liste_Livre_clicked()
{
    clearchamp();
    ui->lineEdit_Recherche_Livre->clear();
    model_livre->setFilter("actif = 1");
    model_livre->select();
    int new_rowCount = model_livre->rowCount();
    ui->spinBox_Nombre_Livre_2->setValue(new_rowCount);
}

void MainWindow::on_pushButton_supprimer_livre_clicked()
{
    QModelIndex currentIndex = ui->tableView_Liste_Livre_2->selectionModel()->currentIndex();
    int row = currentIndex.row();
    QString code_livre = model_livre->data(model_livre->index(row, 0)).toString();
    if (!currentIndex.isValid()) {
        qDebug() << "Aucune ligne sélectionnée.";
        QMessageBox::information(this,"Erreur", "Aucun ligne selectionner");
        ui->stackedWidget_gerer_livre->setCurrentIndex(2);
    }
    else
    {
        qDebug() << "Cellule sélectionnée : " << currentIndex.row() << ", " << currentIndex.column();
        QSqlQuery query;
        query.prepare("SELECT CODE_LIVRE FROM gestion_bibliotheque.emprunter WHERE CODE_LIVRE = :code_livre");
        query.bindValue(":code_livre", code_livre);

        if(!query.exec()){
            QMessageBox::critical(this, "Erreur", query.lastError().text());
        }else if(query.next()){
            ui->changed_zone->setCurrentIndex(3);
            ui->stackedWidget_gerer_livre->setCurrentIndex(7);
            QMessageBox::warning(this,"Avertissement", "Cette livre est en pret!!!");
        }else {
        if (QMessageBox::warning(this, ("Suppression"),
                                 ("Voulez-vous supprimer?"),
                                 (QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No)
        {
            QMessageBox::information(this, ("Attention!"), ("suppression no reussit"));
            ui->stackedWidget_gerer_livre->setCurrentIndex(1);
        }
        else{

            // Mise à jour des données dans la base de données
            QSqlQuery query;
            query.prepare("UPDATE livre SET actif = 0 WHERE CODE_LIVRE = :code_livre  ");
            query.bindValue(":code_livre", code_livre);

            if (!query.exec()) {
                QMessageBox::critical(this, "Erreur", query.lastError().text());
            } else {
                QMessageBox::information(this, "Succès", "Données supprimer avec succès !");
                model_livre->setFilter("actif = 1");
                model_livre->select();
                int rowCount = model_livre->rowCount();
                ui->spinBox_Nombre_Livre_2->setValue(rowCount);
                }
            }
        }
    }
    model_livre->setFilter("actif = 1");
    model_livre->select();
    int new_rowCount = model_livre->rowCount();
    ui->spinBox_Nombre_Livre_2->setValue(new_rowCount);
    valeur_permanente();
}


void MainWindow::on_pushButton_ajouter_nouveau_livre_clicked()
{
    if(ui->code_livre_2->text().isEmpty() || ui->designation_livre_2->text().isEmpty() || ui->auteur_2->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Les champs ne peuvent pas être vide !");
    } else {
        if (QMessageBox::warning(this, ("Enregistrement"),
                                 ("Voulez-vous enregistrer?"),
                                 (QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No)
        {
            QMessageBox::information(this, ("Attention!"), ("inscription non reussite"));
            ui->stackedWidget_gerer_livre->setCurrentIndex(2);
        }
        else{
            QSqlQuery query, query2;
            QString code_livre = ui->code_livre_2->text();
            QString designation_livre = ui->designation_livre_2->text();
            QString auteur = ui->auteur_2->text();
            QString Disponibilite = ui->disponibilite_2->currentText();
            QString categorie = ui->categorie_2->currentText();
            QDate date = ui->date_edition_livre->date();
            int nombre_pret = 0;

            query2.prepare("SELECT CODE_LIVRE FROM gestion_bibliotheque.livre WHERE CODE_LIVRE =:code_livre");
            query2.bindValue(":code_livre", code_livre);
            if(query2.exec()){
                if(query2.next()){
                    QString code = query2.value(0).toString();
                    if(!code.isEmpty()){
                        QMessageBox::warning(this, "Avertissement", "Code livre déjà existant avant et le livre peut être déjà supprimer!<br>Veuillez entrer une nouvelle code du livre.");
                        ui->code_livre_2->clear();
                        return;
                    }
                }
            }

            query.prepare("INSERT INTO GESTION_BIBLIOTHEQUE.livre (CODE_LIVRE, DESIGNATION_LIVRE, AUTEUR_LIVRE, DATE_EDITION_LIVRE , DISPONIBILITE, NOMBRE_PRET_LIVRE, CATEGORIE_LIVRE) "
                          "VALUES (:code_livre ,:designation_livre, :auteur,:date, :Disponibilite, :nombre_pret, :categorie)");
            query.bindValue(":code_livre", code_livre);
            query.bindValue(":designation_livre", designation_livre);
            query.bindValue(":auteur", auteur);
            query.bindValue(":Disponibilite", Disponibilite);
            query.bindValue(":categorie", categorie);
            query.bindValue(":date", date);
            query.bindValue(":nombre_pret", nombre_pret);

            if (!query.exec()) {
                QMessageBox::critical(this, "Erreur", query.lastError().text());

            } else {
                QMessageBox::information(this, "Succès", "Données ajoutées avec succès !");
                //clearchamp_Livre();
                model_livre->setFilter("actif = 1");
                model_livre->select();  // Charger les données
            }
            int new_rowCount = model_livre->rowCount();
            ui->spinBox_Nombre_Livre_2->setValue(new_rowCount);
            ui->stackedWidget_gerer_livre->setCurrentIndex(1);
            valeur_permanente();
        }
    }
}

void MainWindow::on_modifier_2_clicked(){
    if(ui->modifier_code_livre_2->text().isEmpty() || ui->modifier_auteur_2->text().isEmpty() || ui->modifier_designation_livre_2->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Les champs ne peuvent pas être vide !");
    }
    else {
        if (QMessageBox::warning(this, ("Enregistrement"),("Voulez-vous enregistrer?"),(QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No)
        {
            QMessageBox::information(this, ("Attention!"), ("modification non reussite"));
            ui->stackedWidget_gerer_livre->setCurrentIndex(2);
        }else {

            QSqlQuery query;
            QString code_livre = ui->modifier_code_livre_2->text();
            QString designation_livre = ui->modifier_designation_livre_2->text();
            QString auteur = ui->modifier_auteur_2->text();
            QString Disponibilite = ui->modifier_disponibilite_2->currentText();
            QString categorie = ui->modifier_categorie_2->currentText();
            QDate date = ui->modifier_date_edition_2->date();
            int nombre_pret = ui->modifier_pret_2->text().toInt();;

            query.prepare("UPDATE gestion_bibliotheque.livre SET CODE_LIVRE =:code_livre, DESIGNATION_LIVRE =:designation_livre , AUTEUR_LIVRE=:auteur, DATE_EDITION_LIVRE=:date , DISPONIBILITE=:Disponibilite, NOMBRE_PRET_LIVRE=:nombre_pret, CATEGORIE_LIVRE=:categorie, actif = 1 WHERE CODE_LIVRE =:code_livre");

            query.bindValue(":code_livre", code_livre);
            query.bindValue(":designation_livre", designation_livre);
            query.bindValue(":auteur", auteur);
            query.bindValue(":Disponibilite", Disponibilite);
            query.bindValue(":categorie", categorie);
            query.bindValue(":date", date);
            query.bindValue(":nombre_pret", nombre_pret);


            if (!query.exec()) {
                QMessageBox::critical(this, "Erreur", query.lastError().text());

            } else {
                QMessageBox::information(this, "Succès", "Données modifier avec succès !");
                clearchamp_Livre();
                model_livre->setFilter("actif = 1");
                model_livre->select();  // Charger les données
            }
            int new_rowCount = model_livre->rowCount();
            ui->spinBox_Nombre_Livre_2->setValue(new_rowCount);
            ui->stackedWidget_gerer_livre->setCurrentIndex(1);
         }
    }
}

void MainWindow::on_pushButton_algorithme_clicked()
{
    QString recherche = "ALGO";
    model_livre->setFilter(QString("ACTIF = 1 AND (CATEGORIE_LIVRE LIKE '%%1%')").arg(recherche));
    model_livre->select();
    int rowCount = model_livre->rowCount();
    ui->spinBox_Nombre_Livre_2->setValue(rowCount);
    ui->stackedWidget_gerer_livre->setCurrentIndex(1);
}


void MainWindow::on_pushButton_programmation_clicked()
{
    QString recherche = "PRO";
    model_livre->setFilter(QString("actif = 1 AND (CATEGORIE_LIVRE LIKE '%%1%')").arg(recherche));
    model_livre->select();
    int rowCount = model_livre->rowCount();
    ui->spinBox_Nombre_Livre_2->setValue(rowCount);
    ui->stackedWidget_gerer_livre->setCurrentIndex(1);
}


void MainWindow::on_pushButton_system_exploitation_clicked()
{
    QString recherche = "SE";
    model_livre->setFilter(QString("actif = 1 AND (CATEGORIE_LIVRE LIKE '%%1%'").arg(recherche));
    model_livre->select();
    int rowCount = model_livre->rowCount();
    ui->spinBox_Nombre_Livre_2->setValue(rowCount);
    ui->stackedWidget_gerer_livre->setCurrentIndex(1);
}


void MainWindow::on_pushButton_bases_des_donnees_clicked()
{
    QString recherche = "BD";
    model_livre->setFilter(QString("actif = 1 AND (CATEGORIE_LIVRE LIKE '%%1%')").arg(recherche));
    model_livre->select();
    int rowCount = model_livre->rowCount();
    ui->spinBox_Nombre_Livre_2->setValue(rowCount);
    ui->stackedWidget_gerer_livre->setCurrentIndex(1);
}


void MainWindow::on_pushButton_reseaux_clicked()
{
    QString recherche = "RS";
    model_livre->setFilter(QString("actif = 1 AND (CATEGORIE_LIVRE LIKE '%%1%')").arg(recherche));
    model_livre->select();
    int rowCount = model_livre->rowCount();
    ui->spinBox_Nombre_Livre_2->setValue(rowCount);
    ui->stackedWidget_gerer_livre->setCurrentIndex(1);
}


void MainWindow::on_pushButton_IA_clicked()
{
    QString recherche = "IA";
    model_livre->setFilter(QString("actif = 1 AND (CATEGORIE_LIVRE LIKE '%%1%')").arg(recherche));
    model_livre->select();
    int rowCount = model_livre->rowCount();
    ui->spinBox_Nombre_Livre_2->setValue(rowCount);
    ui->stackedWidget_gerer_livre->setCurrentIndex(1);
}

void MainWindow::on_commandLinkButton_categories_livres_clicked()
{
    ui->changed_zone->setCurrentIndex(3);
    ui->stackedWidget_gerer_livre->setCurrentIndex(0);
}

#endif // GESTION_LIVRE_H
