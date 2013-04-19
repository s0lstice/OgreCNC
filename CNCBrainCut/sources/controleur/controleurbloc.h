#ifndef CONTROLEURBLOC_H
#define CONTROLEURBLOC_H

#include <QAbstractItemModel>
#include <Ogre.h>

#include "../modele/bloc/bloc.h"

namespace OgreCNC {

    class NodeBloc;
    class ControleurMain;
    class Bloc;
    class ModeleBloc;

    /*!
     * \brief The ControleurBloc class permet la gestion des blocs, decide s'il est selectionné, la position dans la vue ...
     */
    class ControleurBloc : public QObject
    {
        Q_OBJECT
    private:
        /*!
         * \brief m_controleur est le controleur de bloc
         */
        ControleurMain * m_controleur;
        /*!
         * \brief m_modeleBloc est le modele de bloc
         */
        ModeleBloc * m_modeleBloc;

    public:
        /*!
         * \brief ControleurBloc est le constructeur
         * \param parent le parent
         */
        explicit ControleurBloc(QObject *parent = 0);
        /*!
         * \brief setModeleBloc definit le modele bloc
         * \param modeleBloc
         */
        void setModeleBloc(ModeleBloc * modeleBloc);

        /*!
         * \brief selectSegment choisit si le segment passé en parametre doit etre sélectionné, si oui, il se sélectionne
         * \param segment
         */
        void selectSegment(Ogre::ManualObject * segment);
        /*!
         * \brief selectBloc choisit si le bloc passé en parametre doit etre sélectionné, si oui, il se sélectionne
         * \param bloc
         * \param index
         */
        void selectBloc(Bloc *bloc,const QModelIndex & index = QModelIndex());
        /*!
         * \brief appliquerVueEclatee change la position des bloc en fonction en la distance
         * \param eloignement distance déloignemant
         * \param node racine de depart, si null, c'est la racine de l'arbre qui est prise
         */
        void appliquerVueEclatee(double eloignement, NodeBloc* node = NULL);
        /*!
         * \brief calculerConstanteVueEclatee determine la position d'un bloc en fonction de l'éloignement
         * \param noeudAdeplacer est le bloc ou  noeud à deplacer
         * \param eloignement est la distance
         * \return
         */
        Ogre::Vector3 calculerConstanteVueEclatee(Bloc* noeudAdeplacer, double eloignement);
        /*!
         * \brief changeNameOfCurrentBloc permet de changer le nom du bloc courant
         * \param name
         */
        void changeNameOfCurrentBloc(const QString &name);

    signals:
        /*!
         * \brief si_selectSegment indique la selection d'un segment
         * \param segment est le segment selectionné
         */
        void si_selectSegment(Ogre::ManualObject * segment);

    public slots:

    };
}
#endif // CONTROLEURBLOC_H
