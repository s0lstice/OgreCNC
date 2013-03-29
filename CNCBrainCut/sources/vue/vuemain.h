#ifndef VUEMAIN_H
#define VUEMAIN_H

#include <QMainWindow>
#include <QMdiArea>

namespace Ui {
class VueMain;
}

namespace OgreCNC {

    class vue3d;
    class ControleurMain;
    class ModeleMain;
    class OgreWidget;
    class Bloc;
    class ModeleCut;

    class VueMain : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit VueMain(QWidget *parent = 0);
        ~VueMain();

        inline void setModele(ModeleMain * modele){
            modele = modele;
        }

        inline void setControleur(ControleurMain * controleur){
            controleur = controleur;
        }

    private:
        ControleurMain * controleur;
        ModeleMain * modele;

        QMdiArea * mdi;
        OgreWidget * m_Ogre3d;

        Ui::VueMain *ui;

        ModeleCut* m_modeleCut;

        void initConnections();

        bool event(QEvent * e);
    signals:
        void si_start_cut();
        void si_valid_cut();
        void si_abort_cut();
        void si_update_cut();

    public slots:
        void createBloc(Bloc * bloc);
        void sl_init_cut(ModeleCut* modele);
    private slots:
        void on_demarrerDecoupe_pushButton_clicked();
        void on_validerDecoupe_pushButton_clicked();
        void on_annulerDecoupe_pushButton_clicked();
        void on_horizontaleRadioButton_clicked();
    };
}
#endif // VUEMAIN_H
