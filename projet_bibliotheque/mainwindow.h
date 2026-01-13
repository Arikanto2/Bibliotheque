#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <QTimer>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_login_btn_clicked();

    void on_Menu_Sanctions_clicked();

    void on_Menu_Acceuil_clicked();

    void on_Menu_Lecteurs_clicked();

    void on_pushButton_modifier_lecteur_clicked();

    void on_pushButton_ajouter_lecteur_clicked();

    void on_pushButton_annuler_nouveau_membre_clicked();

    void on_pushButton_annuler_modification_membre_clicked();

    void on_pushButton_Actualiser_Liste_Lecteur_clicked();

    void on_pushButton_Recherche_Lecteur_clicked();

    void on_pushButton_enregistrer_nouveau_membre_clicked();

    void on_pushButton_enregistrer_modificatin_membre_clicked();

    void on_tableView_Liste_Lecteur_clicked(const QModelIndex &index);

    void on_tableView_Liste_Livre_2_clicked(const QModelIndex &index);

    void on_pushButton_supprimer_lecteur_clicked();

    void on_pushButton_image_lecteur_nouveau_clicked();

    void on_pushButton_image_Lecteur_modifier_clicked();

    void on_commandLinkButton_mdpOublie_clicked();

    void on_Menu_Livres_clicked();

    void on_pushButton_ajouter_livre_clicked();

    void on_pushButton_modifier_livre_clicked();

    void on_pushButton_supprimer_livre_clicked();

    void on_pushButton_algorithme_clicked();

    void on_pushButton_programmation_clicked();

    void on_pushButton_system_exploitation_clicked();

    void on_pushButton_bases_des_donnees_clicked();

    void on_pushButton_reseaux_clicked();

    void on_pushButton_IA_clicked();

    void on_pushButton_afficher_tous_livre_clicked();

    void setupTableView_livre();

    void on_Bouton_Inscription_clicked();

    void on_Bouton_pretLivre_clicked();

    void on_Menu_Statistiques_clicked();

    void on_annuler_3_clicked();

    void on_annuler_4_clicked();

    void on_pushButton_Recherche_Livre_clicked();

    void on_pushButton_Actualiser_Liste_Livre_clicked();

    void on_commandLinkButton_seDeconnect_clicked();

    void on_pushButton_quitter_clicked();

    void on_modifier_2_clicked();

    void on_commandLinkButton_categories_livres_clicked();

    void updateTime();

    void on_pushButton_ajouter_Sanction_lecteur_clicked();

    void on_Bouton_Retour_Sanction_clicked();

    void on_Bouton_Sauvegarder_Sanction_clicked();

    void on_Bouton_Supprimer_Sanction_clicked();

    void on_Bouton_recherche_sanction_clicked();

    void on_Bouton_Actualiser_Sanction_clicked();

    void on_pushButton_ajouter_nouveau_livre_clicked();

    void on_afficher_prets_clicked();

    void on_Emprunter_livre_clicked();

    void on_emprunter_annuler_clicked();

    void on_Bouton_pretLivre_3_clicked();

    void on_Bouton_valide_remise_clicked();

    void on_Bouton_remise_livre_clicked();

    void on_afficher_livre_remis_clicked();

    void on_pushButton_liste_lecteur_clicked();

    void on_pushButton_liste_livre_clicked();

    void on_pushButton_liste_pret_clicked();

    void on_pushButton_liste_sanction_clicked();


    void on_pushButton_retour_stat_clicked();

    void on_pushButton_mise_en_pdf_clicked();

    void on_pushButton_liste_livre_remis_clicked();

    void on_Bouton_Modifier_Sanction_clicked();

    void on_pushButton_recherche_pret_clicked();

    void on_Bouton_Retour_Sanction_2_clicked();

    void on_Bouton_Sauvegarder_modification_Sanction_clicked();

    void on_pushButton_recherche_remise_clicked();

    void on_pushButton_actualiser_tableremise_clicked();

    void on_pushButton_actualiser_liste_pret_clicked();

    void on_Menu_Pret_clicked();

private:

    Ui::MainWindow *ui;

    QTimer *timer;

    void setupTableView_lecteur();

    void setupTableView_sanction();

    void setupTableView_emprunter();

    void setupTableView_remise();

    QSqlTableModel *model_lecteur;

    QSqlTableModel *model_lecteur2;

    QSqlTableModel *model_livre;

    QSqlTableModel *model_sanction;

    QSqlTableModel *model_emprunter;

    QSqlTableModel *model_remise;

    void loadSelectedRowData_lecteur(int row);

    void loadSelectedRowData2_livre(int row);

    void Donner_sanction();

    int selectedRow;

    int selectedRow2;

    void clearchamp();

    void clearchamp_Livre();

    void statistique_1();

    void statistique_2();

    void statistique_3();

    void lecteurs_voraces();

    QPixmap photoModifier;

    QPixmap photoActuelle;

    bool NewPhotoModif = false;

    void valeur_permanente();

    int L1, L2, L3, M1, M2;

    void stat2();

    int S1, S2, S3, S4, S5;

    void stat3();
};
#endif // MAINWINDOW_H
