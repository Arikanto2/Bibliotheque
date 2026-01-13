#ifndef EMPREINTER_H
#define EMPREINTER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDate>
#include <QPixmap>
#include <QFile>
#include <QByteArray>
#include <QFileInfo>
#include <QBuffer>
#include <QFileDialog>

void MainWindow::on_Bouton_pretLivre_clicked()
{
    ui->changed_zone->setCurrentIndex(4);
    ui->stackedWidget_gerer_livre->setCurrentIndex(4);
}

void MainWindow::on_pushButton_valider_clicked()
{
    QString lecteur = ui->edit_lecteur->text();
    QString livre = ui->edit_livre->text();
    bool livretrouver = false;
    bool lecteurtrouver = false;
    QSqlQuery query;
    query.prepare("SELECT * FROM gestion_bibliotheque.livre  WHERE CODE_LIVRE = :code_livre  ");
    query.bindValue(":code_livre", livre);
    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", query.lastError().text());
    } else {
        if(query.next()){
            livretrouver = true;
        }
        else{
            livretrouver = false;
        }
    }
    query.prepare("SELECT * FROM gestion_bibliotheque.lecteur  WHERE NUM_LECTEUR = :num_lecteur  ");
    query.bindValue(":num_lecteur", lecteur);
    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", query.lastError().text());
    } else {
        if(query.next()){
            lecteurtrouver = true;
        }
        else{
            lecteurtrouver = false;
        }
    }
    if(livretrouver && lecteurtrouver){
        QMessageBox::information(this,"avertissement","livre et lecteur trouvés");
        ui->changed_zone->setCurrentIndex(4);
        ui->stackedWidget_gerer_livre->setCurrentIndex(4);
        query.prepare("SELECT COUNT(*) FROM gestion_bibliotheque.empreinter");
        if (query.exec()) {
            if (query.next()) {
                int maxValue = query.value(0).toInt();
                ui->spinBox_IDpret->setValue((maxValue+1));
                ui->empreint_lecteur->setText(lecteur);
                ui->empreint_livre->setText(livre);
            }
        } else {
            qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        }
    }
    else{
        QMessageBox::information(this,"avertissement","livre ou lecteur non trouvés");
    }
}

void MainWindow::setupTableView_empreinter()
{
    model_empreinter = new QSqlTableModel;
    model_empreinter->setTable("empreinter");
    model_empreinter->select();
    ui->tableView_Liste_empreinter->setModel(model_empreinter);

    int rowCount = model_empreinter->rowCount();
    ui->spinBox_pret->setValue(rowCount);

    ui->tableView_Liste_empreinter->resizeColumnToContents(0);
    ui->tableView_Liste_empreinter->resizeColumnToContents(1);
    ui->tableView_Liste_empreinter->resizeColumnToContents(2);
    ui->tableView_Liste_empreinter->resizeColumnToContents(3);

    model_empreinter->setHeaderData(1, Qt::Horizontal, QObject::tr("NUM Lecteur"));
    model_empreinter->setHeaderData(2, Qt::Horizontal, QObject::tr("code livre"));
    model_empreinter->setHeaderData(3, Qt::Horizontal, QObject::tr("Date prêt"));
    model_empreinter->setHeaderData(4, Qt::Horizontal, QObject::tr("Date limite"));
}

void MainWindow::on_Empreinter_livre_clicked()
{
    if (QMessageBox::warning(this, "Enregistrement", "Voulez-vous enregistrer ?", QMessageBox::No | QMessageBox::Yes) == QMessageBox::No) {
        QMessageBox::information(this, "Attention!", "Inscription non réussie");
        ui->stackedWidget_gerer_livre->setCurrentIndex(5);
        return;
    }

    QString lecteur = ui->edit_lecteur->text();
    QString livre = ui->edit_livre->text();
    QString code_livre = ui->empreint_livre->text();
    QString num_lecteur = ui->empreint_lecteur->text();
    QDate Date_pret = ui->dateEdit_DateAjout_empreinter->date();
    QDate Date_limite = ui->dateEdit_Datelimite_empreinter->date();

    if (code_livre.isEmpty() || num_lecteur.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    QSqlQuery princy;

    princy.prepare("INSERT INTO gestion_bibliotheque.empreinter (NUM_PRET, CODE_LIVRE, NUM_LECTEUR, DATE_PRET, DATE_LIMITE_PRET) VALUES (:num_pret, :code_livre, :num_lecteur, :Date_pret, :Date_limite)");
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
    princy.bindValue(":lecteur", lecteur);
    if (!princy.exec()) {
        QMessageBox::critical(this, "Erreur", princy.lastError().text());
        return;
    }

    // Mettre à jour le livre
    princy.prepare("UPDATE gestion_bibliotheque.livre SET DISPONIBILITE = 'NON', NOMBRE_PRET_LIVRE = NOMBRE_PRET_LIVRE + 1 WHERE CODE_LIVRE = :livre");
    princy.bindValue(":livre", livre);
    if (!princy.exec()) {
        QMessageBox::critical(this, "Erreur", princy.lastError().text());
        return;
    }

    QMessageBox::information(this, "Succès", "Données ajoutées avec succès !");
    model_empreinter->select();  // Charger les données

    int new_rowCount = model_empreinter->rowCount();
    ui->spinBox_pret->setValue(new_rowCount);
    ui->changed_zone->setCurrentIndex(4);
    ui->stackedWidget_gerer_livre->setCurrentIndex(6);
}

void MainWindow::on_on_afficher_prets_clicked_clicked()
{
    ui->changed_zone->setCurrentIndex(4);
    ui->stackedWidget_gerer_livre->setCurrentIndex(6);
}

#endif // EMPREINTER_H
