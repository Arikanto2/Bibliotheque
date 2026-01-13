#ifndef LOGIN_H
#define LOGIN_H
#include "connexion_mysql.h"
#include <QMainWindow>

void MainWindow::on_login_btn_clicked()
{
    QString nom = ui->non_login->text();
    QString pwd = ui->Mdp_login->text();
    QSqlQuery query;
    query.prepare("SELECT * FROM GESTION_BIBLIOTHEQUE.login WHERE NOM_LOGIN =:nom  AND MDP_LOGIN=:pwd");
    query.bindValue(":nom",nom);
    query.bindValue(":pwd",pwd);
    if(query.exec()&&query.next()){
        ui->stackedWidget->setCurrentIndex(1);
        ui->changed_zone->setCurrentIndex(0);
    }else{
        QMessageBox::information(this,"avertissement","votre login n'est pas fonctionnel");
        lecteurs_voraces();
    }
}
#endif // LOGIN_H
