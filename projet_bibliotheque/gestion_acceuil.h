#ifndef GESTION_ACCEUIL_H
#define GESTION_ACCEUIL_H

#include <QMainWindow>
#include <QSqlQuery>

void MainWindow::lecteurs_voraces(){
    QSqlQuery query;

    // Préparer et exécuter la requête
    query.prepare("SELECT NUM_LECTEUR , NOM_LECTEUR, PRENOM_LECTEUR,NIVEAU_LECTEUR, NOMBRE_PRET_LECTEUR  ,IMG_LECTEUR FROM gestion_bibliotheque.lecteur WHERE actif = '1' ORDER BY NOMBRE_PRET_LECTEUR DESC LIMIT 3");

    if (query.exec()) {
        QStringList noms;
        QStringList prenoms;
        QStringList niveaus;
        QList<int> nums;
        QList<int> nbr_prets;
        QList<QImage> images;

        // Récupérer et afficher les résultats
        while (query.next()) {
            int num = query.value("NUM_LECTEUR").toInt();
            QString nom = query.value("NOM_LECTEUR").toString();
            QString prenom = query.value("PRENOM_LECTEUR").toString();
            QString niveau = query.value("NIVEAU_LECTEUR").toString();
            int nbr_pret = query.value("NOMBRE_PRET_LECTEUR").toInt();
            QByteArray imgData = query.value("IMG_LECTEUR").toByteArray();

            QImage image;
            image.loadFromData(imgData);

            noms << nom;
            nums << num;
            prenoms << prenom;
            niveaus << niveau;
            nbr_prets << nbr_pret;
            images << image;

            qDebug() << "num" << num << "nom:" << nom << "prenom" << prenom << "niveau" << niveau << "nbr pret" << nbr_pret;
        }
        if(noms.size() >= 3 && nums.size() >= 3 && prenoms.size() >= 3 && nbr_prets.size() >= 3 && images.size() >= 3) {
            QSize labelSize1 = ui->pic_profile1->size();
            QSize labelSize2 = ui->pic_profile2->size();
            QSize labelSize3 = ui->pic_profile3->size();


            QImage scaledImage1 = images[0].scaled(labelSize1, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QImage scaledImage2 = images[1].scaled(labelSize2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QImage scaledImage3 = images[2].scaled(labelSize3, Qt::KeepAspectRatio, Qt::SmoothTransformation);

            ui->pic_profile1->setPixmap(QPixmap::fromImage(scaledImage1));
            ui->pic_profile2->setPixmap(QPixmap::fromImage(scaledImage2));
            ui->pic_profile3->setPixmap(QPixmap::fromImage(scaledImage3));

            QString nom1 = noms[0];
            QString nom2 = noms[1];
            QString nom3 = noms[2];

            QString prenom1 = prenoms[0];
            QString prenom2 = prenoms[1];
            QString prenom3 = prenoms[2];

            QString niveau1 = niveaus[0];
            QString niveau2 = niveaus[1];
            QString niveau3 = niveaus[2];

            int num1 = nums[0];
            int num2 = nums[1];
            int num3 = nums[2];

            int nbr_pret1 = nbr_prets[0];
            int nbr_pret2 = nbr_prets[1];
            int nbr_pret3 = nbr_prets[2];

            ui->ID1->setValue(num1);
            ui->ID2->setValue(num2);
            ui->ID3->setValue(num3);

            ui->Nom1->setText(nom1);
            ui->Nom2->setText(nom2);
            ui->Nom3->setText(nom3);

            ui->Prenom1->setText(prenom1);
            ui->Prenom2->setText(prenom2);
            ui->Prenom3->setText(prenom3);

            ui->niveau1->setText(niveau1);
            ui->niveau2->setText(niveau2);
            ui->niveau3->setText(niveau3);

            ui->Livre1->setValue(nbr_pret1);
            ui->Livre2->setValue(nbr_pret2);
            ui->Livre3->setValue(nbr_pret3);

         /*   qDebug() << "nom1" << nom1 << prenom1 << niveau1 << num1 << nbr_pret1;
            qDebug() << "nom2" << nom2 << prenom2 << niveau2 << num2 << nbr_pret2;
            qDebug() << "nom3" << nom3 << prenom3 << niveau3 << num3 << nbr_pret3; */

        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
    }

}


#endif // GESTION_ACCEUIL_H
