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
    class ModeleBloc;

    /*!
     * \brief The VueMain class est la vue de l'application
     */
    class VueMain : public QMainWindow
    {
        Q_OBJECT

    public:
        /*!
         * \brief VueMain est le constructeur
         * \param parent
         */
        explicit VueMain(QWidget *parent = 0);
        ~VueMain();

        /*!
         * \brief setModele definit le modele
         * \param modele
         */
        inline void setModele(ModeleMain * modele){
            modele = modele;
        }
        /*!
         * \brief setControleur definit le controleur de l'application
         * \param controleur
         */
        inline void setControleur(ControleurMain * controleur){
            controleur = controleur;
        }
        /*!
         * \brief griserVoletDecoupe rand inaccessible les fonctions de decoupe
         */
        void griserVoletDecoupe();
        /*!
         * \brief activerVoletDecoupe rand accessible les fonctions de decoupe
         */
        void activerVoletDecoupe();

        inline Bloc * getCurrentBlock(){return m_currentBlock;}
        inline void setCurrentBlock(Bloc * bloc){m_currentBlock = bloc;}
    private:
        /*!
         * \brief controleur est le controleur de l'application
         */
        ControleurMain * controleur;
        /*!
         * \brief modele est le modele principale
         */
        ModeleMain * modele;
        /*!
         * \brief m_Ogre3d est le Widget 3D
         */
        OgreWidget * m_Ogre3d;
        /*!
         * \brief ui est le contenur graphique
         */
        Ui::VueMain * ui;
        /*!
         * \brief m_modeleCut est le modele de découpe
         */
        ModeleCut* m_modeleCut;
        /*!
         * \brief m_ControleurOgreWidget est le controleur d'ogreWidget
         */
        ControleurOgreWidget * m_ControleurOgreWidget;
        /*!
         * \brief initConnections intialise les connections
         */
        void initConnections();

        /*!
         * \brief curentBlock est le bloc courent
         */
        Bloc * m_currentBlock;

    signals:
        void si_start_cut();
        void si_valid_cut();
        bool si_abort_cut();
        void si_update_cut();
        void si_vueEclate(double distance);
        void si_newNameForCurrentBloc(const QString &arg1);
        void si_changeEtatForCurrentBloc(Bloc::Etat etat);
        void si_deleteCurrentNodeBloc();

   public  slots:
        void sl_creat3Dbloc(Bloc * bloc);
        void sl_hide3DBloc(Bloc * bloc);
        void sl_show3DBloc(Bloc * bloc);
        void sl_updateDimentionBloc(Bloc * bloc);
        void sl_updatePositionBloc(Bloc * bloc);
        void sl_updateCouleurBloc(Bloc *bloc);
        void sl_delete3DBloc(Bloc * bloc);

        void on_demarrerDecoupe_pushButton_clicked();
        void on_validerDecoupe_pushButton_clicked();
        void on_annulerDecoupe_pushButton_clicked();
        void on_classiqueRadioButton_clicked();
        void on_multipleRadioButton_clicked();
        void on_directionX_radioButton_clicked();
        void on_directionY_radioButton_clicked();
        void on_directionZ_radioButton_clicked();
        void on_perteGauche_RadioButton_clicked();
        void on_perteDroite_RadioButton_clicked();
        void on_perteCentree_RadioButton_clicked();
        void on_distance_text_textEdited(const QString &arg1);
        void on_nbBlocs_text_textEdited(const QString &arg1);
        void on_distanceVueEclate_valueChanged(int arg1);
        void on_vueEclateCheched_clicked(bool checked);
        void on_blocNom_text_textEdited(const QString &arg1);
        void on_etatblocuse_clicked(bool checked);
        void on_etatblocchute_clicked(bool checked);

        void sl_selectBloc(Bloc * bloc);
        void sl_selectSegment(Ogre::ManualObject * segment);
        void sl_init_cut(ModeleCut* modele);
        void sl_setTreeBlocModele(ModeleBloc * modeleBloc);
    private slots:
        void on_rayon_chauffe_text_textEdited(const QString &arg1);
        void on_blocSupprimer_clicked();
    };
}
#endif // VUEMAIN_H
