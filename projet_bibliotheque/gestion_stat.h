#ifndef GESTION_STAT_H
#define GESTION_STAT_H

#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QPieSeries>
#include <QPieSlice>
#include <QLineSeries>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QAbstractItemModel>
#include <QSqlTableModel>

void MainWindow::on_Menu_Statistiques_clicked()
{
    stat2();
    stat3();
    ui->changed_zone->setCurrentIndex(4);
}

void MainWindow::statistique_1(){
    int S0, S1, S2, S3, S4, S5;
    int A0, A1, A2, A3, A4, A5;
    int D0, D1, D2, D3, D4, D5;
    int E0, E1, E2, E3, E4, E5;

    QSqlQuery query, query1, query2, query3, query4, query5;
    query.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'ALGO') AND (month(DATE_REMISE) <= 3)");
    query1.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'BD') AND (month(DATE_REMISE) <= 3)");
    query2.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'IA') AND (month(DATE_REMISE) <= 3)");
    query3.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'PRO') AND (month(DATE_REMISE) <= 3)");
    query4.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'RS') AND (month(DATE_REMISE) <= 3)");
    query5.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'SE') AND (month(DATE_REMISE) <= 3)");
    if(!(query.exec() && query1.exec() && query2.exec() && query3.exec() && query4.exec() && query5.exec())){
        QMessageBox::critical(this, "Erreur", query.lastError().text());
        QMessageBox::critical(this, "Erreur", query1.lastError().text());
        QMessageBox::critical(this, "Erreur", query2.lastError().text());
        QMessageBox::critical(this, "Erreur", query3.lastError().text());
        QMessageBox::critical(this, "Erreur", query4.lastError().text());
        QMessageBox::critical(this, "Erreur", query5.lastError().text());
    }else if(!(query.next() && query1.next() && query2.next() && query3.next() && query4.next() && query5.next())){
        QMessageBox::critical(this, "Erreur", query.lastError().text());
        QMessageBox::critical(this, "Erreur", query1.lastError().text());
        QMessageBox::critical(this, "Erreur", query2.lastError().text());
        QMessageBox::critical(this, "Erreur", query3.lastError().text());
        QMessageBox::critical(this, "Erreur", query4.lastError().text());
        QMessageBox::critical(this, "Erreur", query5.lastError().text());
    }else {
        S0 = (query.value(0)).toInt();
        S1 = (query1.value(0)).toInt();
        S2 = (query2.value(0)).toInt();
        S3 = (query3.value(0)).toInt();
        S4 = (query4.value(0)).toInt();
        S5 = (query5.value(0)).toInt();

        qDebug() << "s:" << S0 << S1 << S2 << S3 << S4 << S5;
    }

    QSqlQuery a, a1, a2, a3, a4, a5;
    a.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'ALGO') AND (month(DATE_REMISE) <= 6) AND (month(DATE_REMISE) > 3)");
    a1.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'BD') AND (month(DATE_REMISE) <= 6) AND (month(DATE_REMISE) > 3)");
    a2.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'IA') AND (month(DATE_REMISE) <= 6) AND (month(DATE_REMISE) > 3)");
    a3.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'PRO') AND (month(DATE_REMISE) <= 6) AND (month(DATE_REMISE) > 3)");
    a4.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'RS') AND (month(DATE_REMISE) <= 6) AND (month(DATE_REMISE) > 3)");
    a5.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'SE') AND (month(DATE_REMISE) <= 6) AND (month(DATE_REMISE) > 3)");
    if(!(a.exec() && a1.exec() && a2.exec() && a3.exec() && a4.exec() && a5.exec())){
        QMessageBox::critical(this, "Erreur", a.lastError().text());
        QMessageBox::critical(this, "Erreur", a1.lastError().text());
        QMessageBox::critical(this, "Erreur", a2.lastError().text());
        QMessageBox::critical(this, "Erreur", a3.lastError().text());
        QMessageBox::critical(this, "Erreur", a4.lastError().text());
        QMessageBox::critical(this, "Erreur", a5.lastError().text());
    }else if(!(a.next() && a1.next() && a2.next() && a3.next() && a4.next() && a5.next())){
        QMessageBox::critical(this, "Erreur", a.lastError().text());
        QMessageBox::critical(this, "Erreur", a1.lastError().text());
        QMessageBox::critical(this, "Erreur", a2.lastError().text());
        QMessageBox::critical(this, "Erreur", a3.lastError().text());
        QMessageBox::critical(this, "Erreur", a4.lastError().text());
        QMessageBox::critical(this, "Erreur", a5.lastError().text());
    }else {
        A0 = (query.value(0)).toInt();
        A1 = (query1.value(0)).toInt();
        A2 = (query2.value(0)).toInt();
        A3 = (query3.value(0)).toInt();
        A4 = (query4.value(0)).toInt();
        A5 = (query5.value(0)).toInt();

        qDebug() << "a:" << A0 << A1 << A2 << A3 << A4 << A5;
    }

    QSqlQuery d, d1, d2, d3, d4, d5;
    d.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'ALGO') AND (month(DATE_REMISE) <= 9) AND (month(DATE_REMISE) > 6)");
    d1.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'BD') AND (month(DATE_REMISE) <= 9) AND (month(DATE_REMISE) > 6)");
    d2.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'IA') AND (month(DATE_REMISE) <= 9) AND (month(DATE_REMISE) > 6)");
    d3.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'PRO') AND (month(DATE_REMISE) <= 9) AND (month(DATE_REMISE) > 6)");
    d4.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'RS') AND (month(DATE_REMISE) <= 9) AND (month(DATE_REMISE) > 6)");
    d5.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'SE') AND (month(DATE_REMISE) <= 9) AND (month(DATE_REMISE) > 6)");
    if(!(d.exec() && d1.exec() && d2.exec() && d3.exec() && d4.exec() && d5.exec())){
        QMessageBox::critical(this, "Erreur", d.lastError().text());
        QMessageBox::critical(this, "Erreur", d1.lastError().text());
        QMessageBox::critical(this, "Erreur", d2.lastError().text());
        QMessageBox::critical(this, "Erreur", d3.lastError().text());
        QMessageBox::critical(this, "Erreur", d4.lastError().text());
        QMessageBox::critical(this, "Erreur", d5.lastError().text());
    }else if(!(d.next() && d1.next() && d2.next() && d3.next() && d4.next() && d5.next())){
        QMessageBox::critical(this, "Erreur", d.lastError().text());
        QMessageBox::critical(this, "Erreur", d1.lastError().text());
        QMessageBox::critical(this, "Erreur", d2.lastError().text());
        QMessageBox::critical(this, "Erreur", d3.lastError().text());
        QMessageBox::critical(this, "Erreur", d4.lastError().text());
        QMessageBox::critical(this, "Erreur", d5.lastError().text());
    }else {
        D0 = (d.value(0)).toInt();
        D1 = (d1.value(0)).toInt();
        D2 = (d2.value(0)).toInt();
        D3 = (d3.value(0)).toInt();
        D4 = (d4.value(0)).toInt();
        D5 = (d5.value(0)).toInt();

        qDebug() << "d:" << D0 << D1 << D2 << D3 << D4 << D5;
    }

    QSqlQuery e, e1, e2, e3, e4, e5;
    e.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'ALGO') AND (month(DATE_REMISE) <= 12) AND (month(DATE_REMISE) > 9)");
    e1.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'BD') AND (month(DATE_REMISE) <= 12) AND (month(DATE_REMISE) > 9)");
    e2.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'IA') AND (month(DATE_REMISE) <= 12) AND (month(DATE_REMISE) > 9)");
    e3.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'PRO') AND (month(DATE_REMISE) <= 12) AND (month(DATE_REMISE) > 9)");
    e4.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'RS') AND (month(DATE_REMISE) <= 12) AND (month(DATE_REMISE) > 9)");
    e5.prepare("SELECT count(*) FROM gestion_bibliotheque.remise INNER JOIN livre lv ON remise.CODE_LIVRE = lv.CODE_LIVRE WHERE (lv.CATEGORIE_LIVRE = 'SE') AND (month(DATE_REMISE) <= 12) AND (month(DATE_REMISE) > 9)");
    if(!(e.exec() && e1.exec() && e2.exec() && e3.exec() && e4.exec() && e5.exec())){
        QMessageBox::critical(this, "Erreur", e.lastError().text());
        QMessageBox::critical(this, "Erreur", e1.lastError().text());
        QMessageBox::critical(this, "Erreur", e2.lastError().text());
        QMessageBox::critical(this, "Erreur", e3.lastError().text());
        QMessageBox::critical(this, "Erreur", e4.lastError().text());
        QMessageBox::critical(this, "Erreur", e5.lastError().text());
    }else if(!(e.next() && e1.next() && e2.next() && e3.next() && e4.next() && e5.next())){
        QMessageBox::critical(this, "Erreur", e.lastError().text());
        QMessageBox::critical(this, "Erreur", e1.lastError().text());
        QMessageBox::critical(this, "Erreur", e2.lastError().text());
        QMessageBox::critical(this, "Erreur", e3.lastError().text());
        QMessageBox::critical(this, "Erreur", e4.lastError().text());
        QMessageBox::critical(this, "Erreur", e5.lastError().text());
    }else {
        E0 = (e.value(0)).toInt();
        E1 = (e1.value(0)).toInt();
        E2 = (e2.value(0)).toInt();
        E3 = (e3.value(0)).toInt();
        E4 = (e4.value(0)).toInt();
        E5 = (e5.value(0)).toInt();

        qDebug() << "e:" << E0 << E1 << E2 << E3 << E4 << E5;
    }

    QBarSet *set0 = new QBarSet("<h5>Algorithme<h5>");
    QBarSet *set1 = new QBarSet("<h5>Base de donnee<h5>");
    QBarSet *set2 = new QBarSet("<h5>IA<h5>");
    QBarSet *set3 = new QBarSet("<h5>Programmation<h5>");
    QBarSet *set4 = new QBarSet("<h5>Reseaux<h5>");
    QBarSet *set5 = new QBarSet("<h5>System d'exploitation<h5>");

    *set0 << S0 << A0 << D0 << E0;
    *set1 << S1 << A1 << D1 << E1;
    *set2 << S2 << A2 << D2 << E2;
    *set3 << S3 << A3 << D3 << E3;
    *set4 << S4 << A4 << D4 << E4;
    *set5 << S5 << A5 << D5 << E5;


    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    series->append(set5);


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("<h3>Categories Livres les plus emprunter pendant toutes l'année<h3>");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Jan-Mar" << "Avr-Jun" << "Jul-Spt" << "Oct-Dec" ;
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->addAxis(axis, Qt::AlignBottom); // Ajoute l'axe des catégories (X) en bas du graphique
    series->attachAxis(axis);

    QChartView *chartViewBareSeries = new QChartView(chart);
    chartViewBareSeries->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layout = new QVBoxLayout(ui->frame_stat1);
    layout->addWidget(chartViewBareSeries);
    ui->frame_stat1->setLayout(layout);
    chartViewBareSeries->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void MainWindow::stat2(){
    QSqlQuery query, query1, query2, query3, query4;
    query.prepare("SELECT count(*) FROM gestion_bibliotheque.lecteur WHERE actif = 1 AND NIVEAU_LECTEUR = 'licence 1'");
    query1.prepare("SELECT count(*) FROM gestion_bibliotheque.lecteur WHERE actif = 1 AND NIVEAU_LECTEUR = 'licence 2'");
    query2.prepare("SELECT count(*) FROM gestion_bibliotheque.lecteur WHERE actif = 1 AND NIVEAU_LECTEUR = 'licence 3'");
    query3.prepare("SELECT count(*) FROM gestion_bibliotheque.lecteur WHERE actif = 1 AND NIVEAU_LECTEUR = 'Master 1'");
    query4.prepare("SELECT count(*) FROM gestion_bibliotheque.lecteur WHERE actif = 1 AND NIVEAU_LECTEUR = 'Master 2'");
    if(!(query.exec() && query1.exec() && query2.exec() && query3.exec() && query4.exec())){
        QMessageBox::critical(this, "Erreur", query.lastError().text());
        QMessageBox::critical(this, "Erreur", query1.lastError().text());
        QMessageBox::critical(this, "Erreur", query2.lastError().text());
        QMessageBox::critical(this, "Erreur", query3.lastError().text());
        QMessageBox::critical(this, "Erreur", query4.lastError().text());
    }else if(!(query.next() && query1.next() && query2.next() && query3.next() && query4.next())){
        QMessageBox::critical(this, "Erreur", query.lastError().text());
        QMessageBox::critical(this, "Erreur", query1.lastError().text());
        QMessageBox::critical(this, "Erreur", query2.lastError().text());
        QMessageBox::critical(this, "Erreur", query3.lastError().text());
        QMessageBox::critical(this, "Erreur", query4.lastError().text());
    }else {
        L1 = (query.value(0)).toInt();
        L2 = (query1.value(0)).toInt();
        L3 = (query2.value(0)).toInt();
        M1 = (query3.value(0)).toInt();
        M2 = (query4.value(0)).toInt();

        qDebug() << L1 << L2 << L3 << M1 << M2;
    }
}

void MainWindow::statistique_2(){
    stat2();
    QPieSeries *series = new QPieSeries();
    series->append("L1", L1);
    series->append("L2", L2);
    series->append("L3", L3);
    series->append("M1", M1);
    series->append("M2", M2);
    QPieSlice *slice = series->slices().at(1);
    slice->setExploded(); // Explode this chart
    slice->setLabelVisible(); // Make label visible
    slice->setBrush(Qt::blue);
    QPieSlice *slice_L1 = series->slices().at(0);  // Première tranche
    slice_L1->setColor(Qt::darkRed);                   // Définir la couleur en rouge

    QPieSlice *slice_L2 = series->slices().at(1);  // Deuxième tranche
    slice_L2->setBrush(QBrush(Qt::darkCyan));         // Définir la couleur en vert

    QPieSlice *slice_L3 = series->slices().at(2);  // Troisième tranche
    slice_L3->setColor(Qt::darkGreen);                  // Définir la couleur en bleu

    QPieSlice *slice_M1 = series->slices().at(3);  // Première tranche
    slice_M1->setColor(Qt::darkMagenta);                   // Définir la couleur en rouge

    QPieSlice *slice_M2 = series->slices().at(4);  // Deuxième tranche
    slice_M2->setBrush(QBrush(Qt::darkBlue));         // Définir la couleur en vert


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("<h2>Nombres lecteurs par niveau<h2>");

    QChartView *chartViewPieSeries = new QChartView(chart);
    chartViewPieSeries->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layout = new QVBoxLayout(ui->widget_stat2);
    layout->addWidget(chartViewPieSeries);
    ui->widget_stat2->setLayout(layout);
    chartViewPieSeries->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
void MainWindow::stat3(){
    QSqlQuery query, query1, query2, query3, query4;
    query.prepare("SELECT count(*) FROM gestion_bibliotheque.remise WHERE day(DATE_REMISE) < 7");
    query1.prepare("SELECT count(*) FROM gestion_bibliotheque.remise WHERE (day(DATE_REMISE) >= 7) AND (day(DATE_REMISE) < 14)");
    query2.prepare("SELECT count(*) FROM gestion_bibliotheque.remise WHERE (day(DATE_REMISE) >= 14) AND (day(DATE_REMISE) < 21)");
    query3.prepare("SELECT count(*) FROM gestion_bibliotheque.remise WHERE (day(DATE_REMISE) >= 21) AND (day(DATE_REMISE) < 28)");
    query4.prepare("SELECT count(*) FROM gestion_bibliotheque.remise WHERE (day(DATE_REMISE) >= 28) AND (day(DATE_REMISE) < 32)");
    if(!(query.exec() && query1.exec() && query2.exec() && query3.exec() && query4.exec())){
        QMessageBox::critical(this, "Erreur", query.lastError().text());
        QMessageBox::critical(this, "Erreur", query1.lastError().text());
        QMessageBox::critical(this, "Erreur", query2.lastError().text());
        QMessageBox::critical(this, "Erreur", query3.lastError().text());
        QMessageBox::critical(this, "Erreur", query4.lastError().text());
    }else if(!(query.next() && query1.next() && query2.next() && query3.next() && query4.next())){
        QMessageBox::critical(this, "Erreur", query.lastError().text());
        QMessageBox::critical(this, "Erreur", query1.lastError().text());
        QMessageBox::critical(this, "Erreur", query2.lastError().text());
        QMessageBox::critical(this, "Erreur", query3.lastError().text());
        QMessageBox::critical(this, "Erreur", query4.lastError().text());
    }else {
        S1 = (query.value(0)).toInt();
        S2 = (query1.value(0)).toInt();
        S3 = (query2.value(0)).toInt();
        S4 = (query3.value(0)).toInt();
        S5 = (query4.value(0)).toInt();

        qDebug() << S1 << S2 << S3 << S4 << S5;
    }
}

void MainWindow::statistique_3(){
    stat3();
    QLineSeries *seriesLine = new QLineSeries();
    seriesLine->append(1, S5);
    seriesLine->append(7, S1);
    seriesLine->append(14, S2);
    seriesLine->append(21, S3);
    seriesLine->append(28, S4);
    seriesLine->append(31, S5);

    QChart *chartLine = new QChart();
    chartLine->addSeries(seriesLine);
    chartLine->createDefaultAxes();
    chartLine->setTitle("<h3>Nombres des livres preter et remiser dans ce mois<h3>");

    QChartView *chartViewLine = new QChartView(chartLine);
    chartViewLine->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layout = new QVBoxLayout(ui->widget_stat1);
    layout->addWidget(chartViewLine);
    ui->widget_stat1->setLayout(layout);
    chartViewLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void MainWindow::on_pushButton_liste_lecteur_clicked()
{
    ui->changed_zone->setCurrentIndex(5);
    ui->tableView_pdf->setModel(model_lecteur);
    model_lecteur->setFilter("actif = 1");
    model_lecteur->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_pdf->setSelectionMode(QAbstractItemView::SingleSelection); // Sélection d'une seule ligne
    ui->tableView_pdf->setSelectionBehavior(QAbstractItemView::SelectRows); // Sélectionne la ligne entière
    ui->tableView_pdf->setEditTriggers(QAbstractItemView::NoEditTriggers); // Désactiver l'édition

    ui->tableView_pdf->hideColumn(12);
    ui->tableView_pdf->hideColumn(13);

    int rowCount = model_lecteur->rowCount();
    ui->spin_box_pdf->setValue(rowCount);

    ui->tableView_pdf->resizeColumnToContents(0);
    ui->tableView_pdf->resizeColumnToContents(1);
    ui->tableView_pdf->resizeColumnToContents(2);
    ui->tableView_pdf->resizeColumnToContents(3);
    ui->tableView_pdf->resizeColumnToContents(4);
    ui->tableView_pdf->resizeColumnToContents(5);
    ui->tableView_pdf->resizeColumnToContents(6);
    ui->tableView_pdf->resizeColumnToContents(8);
    ui->tableView_pdf->resizeColumnToContents(9);
    ui->tableView_pdf->resizeColumnToContents(10);
    ui->tableView_pdf->resizeColumnToContents(11);

    model_lecteur->setHeaderData(0, Qt::Horizontal, QObject::tr("num"));
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


void MainWindow::on_pushButton_liste_livre_clicked()
{
    ui->changed_zone->setCurrentIndex(5);
    ui->tableView_pdf->setModel(model_livre);
    model_livre->setFilter("actif = 1");
    model_livre->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_pdf->setSelectionMode(QAbstractItemView::SingleSelection); // Sélection d'une seule ligne
    ui->tableView_pdf->setSelectionBehavior(QAbstractItemView::SelectRows); // Sélectionne la ligne entière
    ui->tableView_pdf->setEditTriggers(QAbstractItemView::NoEditTriggers); // Désactiver l'édition

    ui->tableView_pdf->hideColumn(7);

    int rowCount = model_livre->rowCount();
    ui->spin_box_pdf->setValue(rowCount);

    ui->tableView_pdf->resizeColumnToContents(0);
    ui->tableView_pdf->resizeColumnToContents(1);
    ui->tableView_pdf->resizeColumnToContents(2);
    ui->tableView_pdf->resizeColumnToContents(3);
    ui->tableView_pdf->resizeColumnToContents(4);
    ui->tableView_pdf->resizeColumnToContents(5);
    ui->tableView_pdf->resizeColumnToContents(6);

    model_livre->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
    model_livre->setHeaderData(1, Qt::Horizontal, QObject::tr("Désignation"));
    model_livre->setHeaderData(2, Qt::Horizontal, QObject::tr("Auteur"));
    model_livre->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_edition"));
    model_livre->setHeaderData(4, Qt::Horizontal, QObject::tr("Disponibilité"));
    model_livre->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre de prêt"));
    model_livre->setHeaderData(6, Qt::Horizontal, QObject::tr("Categorie"));
}


void MainWindow::on_pushButton_liste_pret_clicked()
{
    ui->changed_zone->setCurrentIndex(5);
    ui->tableView_pdf->setModel(model_emprunter);
    model_emprunter->setFilter("");
    model_emprunter->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_pdf->setSelectionMode(QAbstractItemView::SingleSelection); // Sélection d'une seule ligne
    ui->tableView_pdf->setSelectionBehavior(QAbstractItemView::SelectRows); // Sélectionne la ligne entière
    ui->tableView_pdf->setEditTriggers(QAbstractItemView::NoEditTriggers); // Désactiver l'édition

    int rowCount = model_emprunter->rowCount();
    ui->spin_box_pdf->setValue(rowCount);

    ui->tableView_pdf->resizeColumnToContents(0);
    ui->tableView_pdf->resizeColumnToContents(1);
    ui->tableView_pdf->resizeColumnToContents(2);
    ui->tableView_pdf->resizeColumnToContents(3);
    ui->tableView_pdf->resizeColumnToContents(4);

    model_emprunter->setHeaderData(0, Qt::Horizontal, QObject::tr("num pret"));
    model_emprunter->setHeaderData(1, Qt::Horizontal, QObject::tr("num Lecteur"));
    model_emprunter->setHeaderData(2, Qt::Horizontal, QObject::tr("code livre"));
    model_emprunter->setHeaderData(3, Qt::Horizontal, QObject::tr("Date prêt"));
    model_emprunter->setHeaderData(4, Qt::Horizontal, QObject::tr("Date limite"));
}
void MainWindow::on_pushButton_liste_livre_remis_clicked()
{
    ui->changed_zone->setCurrentIndex(5);
    ui->tableView_pdf->setModel(model_remise);
    model_remise->setFilter("");
    model_remise->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_Liste_remise->setSelectionMode(QAbstractItemView::SingleSelection); // Sélection d'une seule ligne
    ui->tableView_Liste_remise->setSelectionBehavior(QAbstractItemView::SelectRows); // Sélectionne la ligne entière
    ui->tableView_Liste_remise->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int rowCount = model_remise->rowCount();
    ui->spin_box_pdf->setValue(rowCount);

    ui->tableView_pdf->setColumnWidth(0,100);
    ui->tableView_pdf->setColumnWidth(1,100);
    ui->tableView_pdf->setColumnWidth(2,100);
    ui->tableView_pdf->setColumnWidth(3,100);
    ui->tableView_pdf->setColumnWidth(4,100);

    model_remise->setHeaderData(0, Qt::Horizontal, QObject::tr("num remise"));
    model_remise->setHeaderData(1, Qt::Horizontal, QObject::tr("num lecteur"));
    model_remise->setHeaderData(2, Qt::Horizontal, QObject::tr("code livre"));
    model_remise->setHeaderData(3, Qt::Horizontal, QObject::tr("date pret"));
    model_remise->setHeaderData(4, Qt::Horizontal, QObject::tr("date remise"));
}

void MainWindow::on_pushButton_liste_sanction_clicked()
{
    ui->changed_zone->setCurrentIndex(5);
    ui->tableView_pdf->setModel(model_sanction);
    model_sanction->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_pdf->setSelectionMode(QAbstractItemView::SingleSelection); // Sélection d'une seule ligne
    ui->tableView_pdf->setSelectionBehavior(QAbstractItemView::SelectRows); // Sélectionne la ligne entière
    ui->tableView_pdf->setEditTriggers(QAbstractItemView::NoEditTriggers); // Désactiver l'édition

    int rowCount = model_sanction->rowCount();
    ui->spin_box_pdf->setValue(rowCount);

    model_sanction->setHeaderData(0, Qt::Horizontal, QObject::tr("num lecteur"));
    model_sanction->setHeaderData(1, Qt::Horizontal, QObject::tr("Code livre"));
    model_sanction->setHeaderData(2, Qt::Horizontal, QObject::tr("Description sanction"));

}
void MainWindow::on_pushButton_mise_en_pdf_clicked()
{
    // Créer un fichier PDF
    QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer en PDF"), "", "*.pdf");
    if (fileName.isEmpty()){
        return;
    }
    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    // Préparer un QTextDocument pour contenir les données du tableau
    QTextDocument doc;
    QString html;
    html += "<h1>TABLEAU DES DONNEES:</h1>";
    html += "<table border='1' cellspacing='0' cellpadding='4'>";
    html += "<thead><tr>";

    // Récupérer les en-têtes de colonnes
    QAbstractItemModel *model = ui->tableView_pdf->model();
    if (!model) {
        qDebug() << "Modèle non valide";
        return;
    }
    for (int col = 0; col < model->columnCount(); ++col) {
        if(col==12 || col ==13){
            continue;
        }
        html += "<th>" + model->headerData(col, Qt::Horizontal).toString() + "</th>";
    }
    html += "</tr></thead>";

    // Récupérer les données du modèle
    html += "<tbody>";
    for (int row = 0; row < model->rowCount(); ++row) {
        html += "<tr>";
        for (int col = 0; col < model->columnCount(); ++col) {
            if(col==12 || col ==13){
                continue;
            }
            html += "<td>" + model->data(model->index(row, col)).toString() + "</td>";
        }
        html += "</tr>";
    }
    html += "</tbody>";
    html += "</table>";

    // Ajouter le HTML au QTextDocument
    doc.setHtml(html);
    // Dessiner le document sur l'imprimante (qui est en fait le fichier PDF)
    doc.print(&printer);
    QMessageBox::information(this,"validation", "conversion en pdf reussite!");
}
#endif
