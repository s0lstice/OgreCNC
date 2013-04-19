#ifndef CONTROLEURMAIN_H
#define CONTROLEURMAIN_H

#include <QWidget>
#include <Ogre.h>

#include "../modele/bloc/bloc.h"

namespace OgreCNC {

    class VueMain;
    class ModeleMain;
    class ControleurBloc;
    class ControleurCut;
    class ModeleCut;
    class Bloc;
    class ControleurOgreWidget;
    /*!
     * \brief The ControleurMain class est le controleur proncipale
     */
    class ControleurMain : public QWidget
    {
        Q_OBJECT
    public:
        /*!
         * \brief ControleurMain est le constructeur
         * \param parent
         */
        explicit ControleurMain(QWidget *parent = 0);

        /*!
         * \brief modeleMain est le modele principale de l'application
         */
        ModeleMain * modeleMain;
    private:
        /*!
         * \brief m_vue est la vue principale de l'application
         */
        VueMain * m_vue;
        /*!
         * \brief m_controleurBloc est le controleur de Bloc
         */
        ControleurBloc * m_controleurBloc;
        /*!
         * \brief m_controleurCut est le controleur de découpe
         */
        ControleurCut * m_controleurCut;

        /*!
         * \brief initControleurs initalise les sous controleur
         */
        void initControleurs();
        /*!
         * \brief initConnections initalise les connections avec la vue et le modele
         */
        void initConnections();

    signals:
        /*!
         * \brief si_init_cut est le signale de début de la coupe, il permet d'indiquer quel est le modele de découpe utilisé
         * \param modeleCut
         */
        void si_init_cut(ModeleCut* modeleCut);
        /*!
         * \brief si_updateOgreVue est le signale pour demande de metre à jour la vue 3D
         */
        void si_updateOgreVue();

    public slots:
        /*!
         * \brief sl_start_cut est le slot pour traiter la demande de debut de coupe
         */
        void sl_start_cut();
        /*!
         * \brief sl_update_cut est le slot pour traiter la mise ajour de la découpe
         */
        void sl_update_cut();
        /*!
         * \brief sl_selectBloc est le slot pour traiter la selection d'un bloc
         * \param bloc
         */
        void sl_selectBloc(Bloc * bloc);
        /*!
         * \brief sl_abort_cut est le slot pour traiter l'annulation de la découpe
         * \return
         */
        bool sl_abort_cut();
        /*!
         * \brief sl_valid_cut est le slot pour traiter la fin de la découpe
         */
        void sl_valid_cut();
        /*!
         * \brief sl_vueEclate est le slot pour traiter la demande de vue éclaté
         * \param distance
         */
        void sl_vueEclate(double distance);
        /*!
         * \brief sl_blocFromOgreNode est le slot permet d'indiquer quel Bloc correspond au noeud Ogre
         * \param node est le noeud 3D a trouver
         * \return est le Bloc correspondant au noeud
         */
        Bloc * sl_blocFromOgreNode(Ogre::SceneNode * node);
        /*!
         * \brief sl_selectSegment est le slot permet de gerer la selection d'un segment
         * \param segment
         */
        void sl_selectSegment(Ogre::ManualObject * segment);
        /*!
         * \brief sl_newNameForCurrentBloc est le slot pour gerer la demande de changement de nom du bloc courent
         * \param arg1
         */
        void sl_newNameForCurrentBloc(const QString &arg1);
        /*!
         * \brief sl_changeEtatForCurrentBloc est le slot pour chager l'etat du bloc courent
         * \param etat
         */
        void sl_changeEtatForCurrentBloc(Bloc::Etat etat);
    };

}
#endif // CONTROLEURMAIN_H
