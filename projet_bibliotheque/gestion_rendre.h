#ifndef GESTION_RENDRE_H
#define GESTION_RENDRE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>

void MainWindow::on_Bouton_Inscription_4_clicked()
{
    int IDLecteur = (ui->IDLecteur->text()).toInt();
    QString IDLivre = ui->IDLivre->text();
    QSqlQuery requete;

    requete.prepare("SELECT NUM_LECTEUR , CODE_LIVRE FROM gestion_bibliotheque.sanction");

    if(requete.exec()){
        int num_lecteur = requete.value("NUM_LECTEUR").toInt();
        QString code_livre = requete.value("CODE_LIVRE").toString();

        while(requete.next()){
            if(num_lecteur == IDLecteur && code_livre == IDLivre){
                QMessageBox::warning(this, tr("AVERTISSEMENT"), "Sanction");
                requete.prepare("update gestion_bibliotheque.livre SET DISPONIBILITE = 'OUI' where CODE_LIVRE =: IDLivre ;");
                requete.prepare("INSERT INTO gestion_bibliotheque.remise (CODE_LIVRE, NUM_LECTEUR, DATE_REMISE) VALUES ( :IDLivre, :IDLecteur, currentDate");
                requete.bindValue(":IDLivre", IDLivre);
                requete.bindValue(":IDLecteur", IDLecteur);

            } else{
                QMessageBox::information(this, tr("VALIDATION"), "Livre remis");
                requete.prepare("update gestion_bibliotheque.livre SET DISPONIBILITE = 'OUI' where CODE_LIVRE =: IDLivre ;");
                requete.prepare("INSERT INTO gestion_bibliotheque.remise (CODE_LIVRE, NUM_LECTEUR, DATE_REMISE) VALUES ( :IDLivre, :IDLecteur, currentDate");
                requete.bindValue(":IDLivre", IDLivre);
                requete.bindValue(":IDLecteur", IDLecteur);
            }
        }
    }
}

#endif // GESTION_RENDRE_H
