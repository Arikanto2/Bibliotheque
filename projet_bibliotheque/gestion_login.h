#ifndef GESTION_LOGIN_H
#define GESTION_LOGIN_H
#include "connexion_mysql.h"
#include <QMainWindow>

void MainWindow::on_login_btn_clicked()
{
    QString nom = ui->non_login->text();
    QString pwd = ui->Mdp_login->text();
    QSqlQuery query;
    query.prepare("SELECT * FROM gestion_bibliotheque.login WHERE NOM_LOGIN =:nom  AND MDP_LOGIN=:pwd");
    query.bindValue(":nom",nom);
    query.bindValue(":pwd",pwd);
    if(query.exec()&&query.next()){
        ui->stackedWidget->setCurrentIndex(1);
        ui->changed_zone->setCurrentIndex(0);
        lecteurs_voraces();
        valeur_permanente();
        stat2();
        stat3();
    }else{
        QMessageBox::information(this,"avertissement","votre login n'est pas fonctionnel");
    }
}
#endif // GESTION_LOGIN_H
