#ifndef GESTION_LECTEUR_H
#define GESTION_LECTEUR_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QAbstractItemView>
#include <QDate>
#include <QPixmap>
#include <QFile>
#include <QByteArray>
#include <QFileInfo>
#include <QBuffer>
#include <QFileDialog>

void MainWindow::clearchamp(){ //reinitialiser les champs
    ui->lineEdit_NomLecteur_nouveau->clear();
    ui->lineEdit_PrenomLecteur_nouveau->clear();
    ui->lineEdit_AdresseLecteur_nouveau->clear();
    ui->lineEdit_TelephoneLecteur_nouveau->clear();
    ui->lineEdit_EmailLecteur_nouveau->clear();
    ui->comboBox_SexeLecteur_nouveau->setCurrentIndex(0);
    ui->comboBox_NiveauLecteur_nouveau->setCurrentIndex(0);
    ui->comboBox_ParcourLecteur_nouveau->setCurrentIndex(0);
    ui->dateEdit_DateNaissLecteur_nouveau->setDate(QDate(2000, 1 ,1));
    ui->spinBox_IDLecteur_nouveau->clear();

}

void MainWindow::setupTableView_lecteur(){ // connexion a la table_lecteur
    model_lecteur = new QSqlTableModel;
    model_lecteur->setTable("lecteur");
    model_lecteur->setFilter("actif = 1");
    model_lecteur->select();
    model_lecteur->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_Liste_Lecteur->setModel(model_lecteur);
    ui->tableView_Liste_Lecteur->setSelectionMode(QAbstractItemView::SingleSelection); // Sélection d'une seule ligne
    ui->tableView_Liste_Lecteur->setSelectionBehavior(QAbstractItemView::SelectRows); // Sélectionne la ligne entière
    ui->tableView_Liste_Lecteur->setEditTriggers(QAbstractItemView::NoEditTriggers); // Désactiver l'édition

    ui->tableView_Liste_Lecteur->hideColumn(12);
    ui->tableView_Liste_Lecteur->hideColumn(13);

    int rowCount = model_lecteur->rowCount();
    ui->spinBox_Nombre_Lecteur->setValue(rowCount);

    ui->tableView_Liste_Lecteur->setColumnWidth(0,40);
    ui->tableView_Liste_Lecteur->setColumnWidth(1,200);
    ui->tableView_Liste_Lecteur->setColumnWidth(2,200);
    ui->tableView_Liste_Lecteur->setColumnWidth(3,100);
    ui->tableView_Liste_Lecteur->setColumnWidth(4,100);
    ui->tableView_Liste_Lecteur->setColumnWidth(5,100);
    ui->tableView_Liste_Lecteur->setColumnWidth(6,100);
    ui->tableView_Liste_Lecteur->setColumnWidth(7,220);
    ui->tableView_Liste_Lecteur->setColumnWidth(8,100);
    ui->tableView_Liste_Lecteur->setColumnWidth(10,100);
    ui->tableView_Liste_Lecteur->setColumnWidth(11,60);

    model_lecteur->setHeaderData(0, Qt::Horizontal, QObject::tr("Num"));
    model_lecteur->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model_lecteur->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model_lecteur->setHeaderData(4, Qt::Horizontal, QObject::tr("naissance"));
    model_lecteur->setHeaderData(8, Qt::Horizontal, QObject::tr("Adresse"));
    model_lecteur->setHeaderData(9, Qt::Horizontal, QObject::tr("Tel"));
    model_lecteur->setHeaderData(5, Qt::Horizontal, QObject::tr("Niveau"));
    model_lecteur->setHeaderData(6, Qt::Horizontal, QObject::tr("Domaine"));
    model_lecteur->setHeaderData(10, Qt::Horizontal, QObject::tr("Date d'ajout"));
    model_lecteur->setHeaderData(7, Qt::Horizontal, QObject::tr("Email"));
    model_lecteur->setHeaderData(3, Qt::Horizontal, QObject::tr("sexe"));
    model_lecteur->setHeaderData(11, Qt::Horizontal, QObject::tr("nbr-prete"));
    model_lecteur->setHeaderData(12, Qt::Horizontal, QObject::tr("image en binaire"));

}
void MainWindow::on_tableView_Liste_Lecteur_clicked(const QModelIndex &index) // recuperer l'indexe de la ligne selectionner
{
    selectedRow = index.row();
    loadSelectedRowData_lecteur(selectedRow);
}

void MainWindow::loadSelectedRowData_lecteur(int row)// envoyer les valeurs da la tableview dans la page modification
{
    int ID_lecteur = model_lecteur->data(model_lecteur->index(row,0)).toInt();
    QString nom = model_lecteur->data(model_lecteur->index(row, 1)).toString();
    QString prenom = model_lecteur->data(model_lecteur->index(row, 2)).toString();
    QString sexe = model_lecteur->data(model_lecteur->index(row, 3)).toString();
    QDate datenaissance = model_lecteur->data(model_lecteur->index(row, 4)).toDate();
    QString adresse = model_lecteur->data(model_lecteur->index(row, 8)).toString();
    QString tel = model_lecteur->data(model_lecteur->index(row, 9)).toString();
    QString niveau = model_lecteur->data(model_lecteur->index(row, 5)).toString();
    QString domaine = model_lecteur->data(model_lecteur->index(row, 6)).toString();
    QString email = model_lecteur->data(model_lecteur->index(row, 7)).toString();
    QDate dateajout = model_lecteur->data(model_lecteur->index(row, 10)).toDate();
    QByteArray imageData = model_lecteur->data(model_lecteur->index(row,12)).toByteArray();
    if(!imageData.isEmpty()){
        QPixmap pixmap;
        if (pixmap.loadFromData(imageData)) {
            // Afficher l'image redimensionnée dans le QLabel
            ui->label_image_lecteur_modifier->setPixmap(pixmap.scaled(ui->label_image_lecteur_modifier->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            ui->spinBox_IDLecteur_modification->setValue(ID_lecteur);
            ui->lineEdit_NomLecteur_modification->setText(nom);
            ui->lineEdit_PrenomLecteur_modification->setText(prenom);
            ui->comboBox_SexeLecteur_modification->setCurrentText(sexe);
            ui->comboBox_NiveauLecteur_modification->setCurrentText(niveau);
            ui->comboBox_ParcourLecteur_modification->setCurrentText(domaine);
            ui->dateEdit_DateNaissLecteur_modification->setDate(datenaissance);
            ui->lineEdit_AdresseLecteur_modification->setText(adresse);
            ui->lineEdit_TelephoneLecteur_modification->setText(tel);
            ui->lineEdit_EmailLecteur_modification->setText(email);
            ui->dateEdit_DateAjoutLecteur_modification->setDate(dateajout);
        }
    }
}

void MainWindow::on_pushButton_ajouter_lecteur_clicked() // vers la page ajouter lecteur avec la nouvelle num_lecteur
{
    clearchamp();
    ui->stackedWidget_gerer_lecteur->setCurrentIndex(1);
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

    QPixmap photoParDefaut(":/image/icone/images.png"); // Chemin de l'image par défaut
    ui->label_image_lecteur_nouveau->setPixmap(photoParDefaut.scaled(ui->label_image_lecteur_nouveau->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Stockez cette image comme "photo actuelle"
    photoActuelle = photoParDefaut;
}


void MainWindow::on_pushButton_modifier_lecteur_clicked() // vers la page modification avec verification si il y a ligne selectionner
{
    QModelIndex currentIndex = ui->tableView_Liste_Lecteur->selectionModel()->currentIndex();
    if (!currentIndex.isValid()) {
        qDebug() << "Aucune ligne sélectionnée.";
        QMessageBox::information(this,"Erreur", "Aucun ligne selectionner");
        ui->stackedWidget_gerer_lecteur->setCurrentIndex(0);
    }
    else
    {
        qDebug() << "Cellule sélectionnée : " << currentIndex.row() << ", " << currentIndex.column();
        ui->stackedWidget_gerer_lecteur->setCurrentIndex(2);
    }
}

void MainWindow::on_pushButton_annuler_nouveau_membre_clicked() // annulation d'enregistrement du mouveau lecteur
{

    if (QMessageBox::warning(this, ("Annulation de inscription"),
                             ("Voulez-vous annuler l'inscription?"),
                             (QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No)
    {
        ui->stackedWidget_gerer_lecteur->setCurrentIndex(1);
    }
    else{
        clearchamp();
        model_lecteur->select();
        ui->stackedWidget_gerer_lecteur->setCurrentIndex(0);
    }
}

void MainWindow::on_pushButton_annuler_modification_membre_clicked() // annulation d'enregistrement du modification sur le lecteur
{
    if (QMessageBox::warning(this, ("Annulation des modifications"),
                             ("Voulez-vous annuler les modifications?"),
                             (QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No)
    {
        ui->stackedWidget_gerer_lecteur->setCurrentIndex(2);
    }
    else{
        clearchamp();
        model_lecteur->setFilter("actif = 1");
        model_lecteur->select();
        ui->stackedWidget_gerer_lecteur->setCurrentIndex(0);
    }
}

void MainWindow::on_pushButton_Actualiser_Liste_Lecteur_clicked() // mis a jour de la tableview par boutton actualiser
{
    clearchamp();
    ui->lineEdit_Recherche_Lecteur->clear();
    model_lecteur->setFilter("actif = 1");
    model_lecteur->select();
    int new_rowCount = model_lecteur->rowCount();
    ui->spinBox_Nombre_Lecteur->setValue(new_rowCount);
}


void MainWindow::on_pushButton_Recherche_Lecteur_clicked() // demarage du recherche par boutton recherche lecteur
{
    QString recherche = ui->lineEdit_Recherche_Lecteur->text();
    model_lecteur->setFilter(QString("actif = 1 AND (NUM_LECTEUR LIKE '%%1%' OR NOM_LECTEUR LIKE '%%1%')").arg(recherche));
    model_lecteur->select();
    int rowCount = model_lecteur->rowCount();
    ui->spinBox_Nombre_Lecteur->setValue(rowCount);
}


void MainWindow::on_pushButton_enregistrer_nouveau_membre_clicked() // enregistrement du nouveau lecteur dans la base de donnee et mis a jour du table lecteur apres
{
    if(ui->lineEdit_NomLecteur_nouveau->text().isEmpty() || ui->lineEdit_AdresseLecteur_nouveau->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Les champ ne peuvent pas être vide !");
    }
    else {
        if (QMessageBox::warning(this, ("Enregistrement"),("Voulez-vous enregistrer?"),(QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No)
        {
            QMessageBox::information(this, ("Attention!"), ("inscription non reussite"));
            ui->stackedWidget_gerer_lecteur->setCurrentIndex(1);
        }else {
            QByteArray byteArray;
            QBuffer buffer(&byteArray);
            buffer.open(QIODevice::WriteOnly);
            photoActuelle.save(&buffer, "PNG");
            photoActuelle.save(&buffer, "JPG");
            photoActuelle.save(&buffer, "JPEG");
            photoActuelle.save(&buffer, "BMP");

            int num_lecteur = ((ui->spinBox_IDLecteur_nouveau->text()).toInt());
            QString nom_lecteur = ui->lineEdit_NomLecteur_nouveau->text();
            QString prenom_lecteur = ui->lineEdit_PrenomLecteur_nouveau->text();
            QString sexe_lecteur = ui->comboBox_SexeLecteur_nouveau->currentText();
            QString niveau_lecteur = ui->comboBox_NiveauLecteur_nouveau->currentText();
            QString parcour_lecteur = ui->comboBox_ParcourLecteur_nouveau->currentText();
            QDate date_naissance_lecteur = ui->dateEdit_DateNaissLecteur_nouveau->date();
            QString adresse_lecteur = ui->lineEdit_AdresseLecteur_nouveau->text();
            QString telephone_lecteur = ui->lineEdit_TelephoneLecteur_nouveau->text();
            QString email_lecteur = ui->lineEdit_EmailLecteur_nouveau->text();
            QDate date_ajout_lecteur = ui->dateEdit_DateAjoutLecteur_nouveau->date();
            QSqlQuery query;
            query.prepare("INSERT INTO gestion_bibliotheque.lecteur (NUM_LECTEUR, NOM_LECTEUR, PRENOM_LECTEUR, SEXE_LECTEUR , DATE_NAISS_LECTEUR, NIVEAU_LECTEUR, DOMAINE_LECTEUR, EMAIL_LECTEUR, ADRESSE_LECTEUR, TEL_LECTEUR, DATE_AJOUT_LECTEUR, NOMBRE_PRET_LECTEUR, IMG_LECTEUR, actif) "
                          "VALUES (:num_lecteur ,:nom_lecteur, :prenom_lecteur,:sexe_lecteur, :date_naissance_lecteur, :niveau_lecteur, :parcour_lecteur, :email_lecteur, :adresse_lecteur  , :telephone_lecteur,   :date_ajout_lecteur, :nbr_pret, :img_lecteur, 1)");
            query.bindValue(":num_lecteur", num_lecteur);
            query.bindValue(":nom_lecteur", nom_lecteur);
            query.bindValue(":prenom_lecteur", prenom_lecteur);
            query.bindValue(":sexe_lecteur", sexe_lecteur);
            query.bindValue(":date_naissance_lecteur", date_naissance_lecteur);
            query.bindValue(":adresse_lecteur", adresse_lecteur);
            query.bindValue(":telephone_lecteur", telephone_lecteur);
            query.bindValue(":email_lecteur", email_lecteur);
            query.bindValue(":parcour_lecteur", parcour_lecteur);
            query.bindValue(":date_ajout_lecteur", date_ajout_lecteur);
            query.bindValue(":nbr_pret", 0);
            query.bindValue(":niveau_lecteur", niveau_lecteur);
            query.bindValue(":img_lecteur", byteArray);

            if (!query.exec())
            {
                QMessageBox::critical(this, "Erreur", query.lastError().text());
            }else
            {
                QMessageBox::information(this, "Succès", "Données ajoutées avec succès !");
                clearchamp();
                model_lecteur->setFilter("actif = 1");
                model_lecteur->select();  // Charger les données
            }
            int new_rowCount = model_lecteur->rowCount();
            ui->spinBox_Nombre_Lecteur->setValue(new_rowCount);
            ui->stackedWidget_gerer_lecteur->setCurrentIndex(0);
            valeur_permanente();
        }
    }
}
void MainWindow::on_pushButton_enregistrer_modificatin_membre_clicked() // enregistrement de la modification dans la base de donnee et mis a jour du table lecteur apres
{
    if(ui->lineEdit_NomLecteur_modification->text().isEmpty() || ui->lineEdit_AdresseLecteur_modification->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Les champ ne peuvent pas être vide !");
    }
    else {
        if (QMessageBox::warning(this, ("Enregistrement"),("Voulez-vous enregistrer?"),(QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No)
        {
            QMessageBox::information(this, ("Attention!"), ("modification non reussite"));
            ui->stackedWidget_gerer_lecteur->setCurrentIndex(2);
        }else {
            QPixmap photo;
            if (NewPhotoModif == false){
                photo = photoActuelle;
            }else{
                photo = photoModifier;
            }

            QByteArray byteArray;
            QBuffer buffer(&byteArray);
            buffer.open(QIODevice::WriteOnly);
            photo.save(&buffer, "PNG"); // ou "JPG"
            photo.save(&buffer, "JPG");
            photo.save(&buffer, "JPEG");
            photo.save(&buffer, "BMP");

            int num_lecteur = (ui->spinBox_IDLecteur_modification->text()).toInt();
            QString nom_lecteur = ui->lineEdit_NomLecteur_modification->text();
            QString prenom_lecteur = ui->lineEdit_PrenomLecteur_modification->text();
            QString sexe_lecteur = ui->comboBox_SexeLecteur_modification->currentText();
            QString niveau_lecteur = ui->comboBox_NiveauLecteur_modification->currentText();
            QString parcour_lecteur = ui->comboBox_ParcourLecteur_modification->currentText();
            QDate date_naissance_lecteur = ui->dateEdit_DateNaissLecteur_modification->date();
            QString adresse_lecteur = ui->lineEdit_AdresseLecteur_modification->text();
            QString telephone_lecteur = ui->lineEdit_TelephoneLecteur_modification->text();
            QString email_lecteur = ui->lineEdit_EmailLecteur_modification->text();
            QDate date_ajout_lecteur = ui->dateEdit_DateAjoutLecteur_modification->date();

            QSqlQuery query;
            query.prepare("UPDATE gestion_bibliotheque.lecteur SET  NOM_LECTEUR =:nom_lecteur, PRENOM_LECTEUR = :prenom_lecteur, SEXE_LECTEUR = :sexe_lecteur , DATE_NAISS_LECTEUR = :date_naissance_lecteur, NIVEAU_LECTEUR = :niveau_lecteur, DOMAINE_LECTEUR = :parcour_lecteur, EMAIL_LECTEUR = :email_lecteur, ADRESSE_LECTEUR = :adresse_lecteur, TEL_LECTEUR = :telephone_lecteur, DATE_AJOUT_LECTEUR  = :date_ajout_lecteur, IMG_LECTEUR = :img_lecteur, actif = 1 WHERE NUM_LECTEUR = :num_lecteur");
            query.bindValue(":num_lecteur", num_lecteur);
            query.bindValue(":nom_lecteur", nom_lecteur);
            query.bindValue(":prenom_lecteur", prenom_lecteur);
            query.bindValue(":sexe_lecteur", sexe_lecteur);
            query.bindValue(":date_naissance_lecteur", date_naissance_lecteur);
            query.bindValue(":adresse_lecteur", adresse_lecteur);
            query.bindValue(":telephone_lecteur", telephone_lecteur);
            query.bindValue(":email_lecteur", email_lecteur);
            query.bindValue(":parcour_lecteur", parcour_lecteur);
            query.bindValue(":date_ajout_lecteur", date_ajout_lecteur);
            query.bindValue(":niveau_lecteur", niveau_lecteur);
            query.bindValue(":img_lecteur", byteArray);

            if (!query.exec()) {
                QMessageBox::critical(this, "Erreur", query.lastError().text());

            } else {
                QMessageBox::information(this, "Succès", "Données modifier avec succès !");
                clearchamp();
                model_lecteur->setFilter("actif = 1");
                model_lecteur->select();  // Charger les données
                ui->stackedWidget_gerer_lecteur->setCurrentIndex(0);
            }
        }
    }
}


void MainWindow::on_pushButton_supprimer_lecteur_clicked() // enregistrement du suppression du ligne selectionne da la base et mis a jour du table lecteur
{
    QModelIndex currentIndex = ui->tableView_Liste_Lecteur->selectionModel()->currentIndex();
    int row = currentIndex.row();

    QString num_lecteur = model_lecteur->data(model_lecteur->index(row, 0)).toString();
    if (!currentIndex.isValid())
    {
        qDebug() << "Aucune ligne sélectionnée.";
        QMessageBox::information(this,"Erreur", "Aucun ligne selectionner");
        ui->stackedWidget_gerer_lecteur->setCurrentIndex(0);
    }
    else
    {
        qDebug() << "Cellule sélectionnée : " << currentIndex.row() << ", " << currentIndex.column();
        QSqlQuery query;
        query.prepare("SELECT NUM_LECTEUR FROM gestion_bibliotheque.emprunter WHERE NUM_LECTEUR = :num_lecteur");
        query.bindValue(":num_lecteur", num_lecteur);

        if(!query.exec()){
            QMessageBox::critical(this, "Erreur", query.lastError().text());
        }else if(query.next()){
            ui->changed_zone->setCurrentIndex(3);
            ui->stackedWidget_gerer_livre->setCurrentIndex(7);
            QMessageBox::warning(this,"Avertissement", "Cette personne a encore une livre a rendre!!!");
        }else{

        QSqlQuery query1;
        query1.prepare("SELECT NUM_LECTEUR FROM gestion_bibliotheque.sanction WHERE NUM_LECTEUR = :num_lecteur");
        query1.bindValue(":num_lecteur", num_lecteur);

        if(!query1.exec()){
            QMessageBox::critical(this, "Erreur", query1.lastError().text());
        }else if(query1.next()){
            ui->changed_zone->setCurrentIndex(1);
            QMessageBox::warning(this,"Avertissement", "Cette personne a encore des sanctions a regler!!");
        }else {
        if (QMessageBox::warning(this, ("Suppression"),("Voulez-vous supprimer?"),(QMessageBox::No|QMessageBox::Yes)) == QMessageBox::No)
        {
            QMessageBox::information(this, ("Attention!"), ("suppression no reussit"));
            ui->stackedWidget_gerer_lecteur->setCurrentIndex(0);
        }
        else
        {

            // Suppression du ligne selectionner dans la base
            QSqlQuery query;
            query.prepare("UPDATE lecteur SET actif = 0 WHERE NUM_LECTEUR = :num_lecteur  ");
            query.bindValue(":num_lecteur", num_lecteur);

            if (!query.exec())
            {
                QMessageBox::critical(this, "Erreur", query.lastError().text());
            }
            else
            {
                QMessageBox::information(this, "Succès", "Données supprimer avec succès !");
                model_lecteur->setFilter("actif = 1");
                model_lecteur->select(); // Rafraîchir les données du modèle
            }
        }

    }
    model_lecteur->setFilter("actif = 1");
    model_lecteur->select();
    int new_rowCount = model_lecteur->rowCount();
    ui->spinBox_Nombre_Lecteur->setValue(new_rowCount);
    valeur_permanente();

        }
    }
}

void MainWindow::on_pushButton_image_lecteur_nouveau_clicked() // mettre une image sur le formulaire du nouveau lecteur
{
    QString fichierImage = QFileDialog::getOpenFileName(nullptr, "Choisir une image", "", "Images (*.png *.jpg *.jpeg *.bmp)");

    if (!fichierImage.isEmpty())
    {
        // Charger l'image sélectionnée dans un QPixmap
        QPixmap image(fichierImage);
        // Afficher l'image dans le QLabel
        ui->label_image_lecteur_nouveau->setPixmap(image.scaled(ui->label_image_lecteur_nouveau->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        photoActuelle = image;
    }
}


void MainWindow::on_pushButton_image_Lecteur_modifier_clicked() // modifier l'image du lecteur dans la page modification
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choisir une photo"), "", tr("Images (*.png *.jpg *.jpeg *.bmp)"));

    if (!fileName.isEmpty()) {
        QPixmap image(fileName);
        ui->label_image_lecteur_modifier->setPixmap(image.scaled(ui->label_image_lecteur_modifier->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        photoModifier = image;

        NewPhotoModif = true;
    }
}


#endif
