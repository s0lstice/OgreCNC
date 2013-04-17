#ifndef VUEMAIN_H
#define VUEMAIN_H

#include <QMainWindow>
#include <QMdiArea>
#include <Ogre.h>

#include "../modele/bloc/bloc.h"

namespace Ui {
class VueMain;
}

namespace OgreCNC {

    class vue3d;
    class ControleurMain;
    class ModeleMain;
    class OgreWidget;
    class ModeleCut;
    class ControleurOgreWidget;

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

        Ui::VueMain * ui;

        ModeleCut* m_modeleCut;

        ControleurOgreWidget * m_ControleurOgreWidget;
        bool event(QEvent * e);

        void initConnections();

    signals:
        void si_start_cut();
        void si_valid_cut();
        void si_abort_cut();
        void si_update_cut();
        void si_select(int id);
        void si_vueEclate(double distance);
        void si_newNameForCurrentBloc(const QString &arg1);
        void si_changeEtatForCurrentBloc(Bloc::Etat etat);

    private slots:
        void sl_creat3Dbloc(Bloc * bloc);
        void sl_updateDimentionBloc(Bloc * bloc);
        void sl_updatePositionBloc(Bloc * bloc);
        void sl_updateCouleurBloc(Bloc *bloc);
        void on_demarrerDecoupe_pushButton_clicked();
        void on_validerDecoupe_pushButton_clicked();
        void on_annulerDecoupe_pushButton_clicked();
        void on_horizontaleRadioButton_clicked();
        void on_verticaleRadioButton_clicked();
        void on_classiqueRadioButton_clicked();
        void on_multipleRadioButton_clicked();
        void on_directionX_radioButton_clicked();
        void on_directionY_radioButton_clicked();
        void on_directionZ_radioButton_clicked();
        void on_perteGauche_RadioButton_clicked();
        void on_perteDroite_RadioButton_clicked();
        void on_perteCentree_RadioButton_clicked();
        void on_origineX_text_textEdited(const QString &arg1);
        void on_origineY_text_textEdited(const QString &arg1);
        void on_origineZ_text_textEdited(const QString &arg1);
        void on_distance_text_textEdited(const QString &arg1);
        void on_nbBlocs_text_textEdited(const QString &arg1);
        void on_distanceVueEclate_valueChanged(int arg1);
        void on_vueEclateCheched_clicked(bool checked);
        void on_blocNom_text_textEdited(const QString &arg1);

        void on_etatblocuse_clicked(bool checked);

    public slots:
        void sl_selectBloc(Bloc * bloc);
        void sl_selectSegment(Ogre::ManualObject * segment);
        void sl_init_cut(ModeleCut* modele);
    };
}
#endif // VUEMAIN_H
