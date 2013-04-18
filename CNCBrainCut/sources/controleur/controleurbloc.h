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

    class ControleurBloc : public QObject
    {
        Q_OBJECT
    private:

        ControleurMain * m_controleur;
        ModeleBloc * m_modeleBloc;

    public:
        explicit ControleurBloc(QObject *parent = 0);

        void setModeleBloc(ModeleBloc * modeleBloc);
        void selectSegment(Ogre::ManualObject * segment);
        void selectBloc(Bloc *bloc,const QModelIndex & index = QModelIndex());
        void appliquerVueEclatee(double eloignement, NodeBloc* node = NULL);
        Ogre::Vector3 calculerConstanteVueEclatee(Bloc* noeudAdeplacer, double eloignement);
        /*!
         * \brief changeNameOfCurrentBloc permet de changer le nom du bloc courant
         * \param name
         */
        void changeNameOfCurrentBloc(const QString &name);

    signals:
        void si_selectSegment(Ogre::ManualObject * segment);

    public slots:

    };
}
#endif // CONTROLEURBLOC_H
