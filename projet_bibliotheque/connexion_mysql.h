#ifndef CONNEXION_MYSQL_H
#define CONNEXION_MYSQL_H
#include "QtSql"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QDebug"

static bool connexiondb()
{
    QSqlDatabase conn = QSqlDatabase::addDatabase("QMYSQL");

    conn.setHostName("localhost");
    conn.setPort(3306);
    conn.setUserName("root");
    conn.setPassword("rft5");
    conn.setDatabaseName("gestion_bibliotheque");

    if(conn.open()){
        qDebug() << "connected!";
        return true;
    }
    else{
        qDebug() << "failded to connect!";
        return false;
    }
}
#endif
