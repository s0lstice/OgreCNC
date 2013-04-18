#ifndef MODELEBLOC_H
#define MODELEBLOC_H

#include <QAbstractItemModel>
#include <Ogre.h>
#include "bloc.h"

namespace OgreCNC{
    class NodeBloc;
    class Bloc;
    class ModeleMain;

    class ModeleBloc : public QAbstractItemModel
    {
        Q_OBJECT

    private:
        NodeBloc * m_root;
        ModeleMain * m_modeleMain;

    public:
        /*!
         * \brief ModeleBloc est le constructeur
         * \param parent est l'object parent
         */
        explicit ModeleBloc(QObject *parent = 0);
        /*!
         * \brief ModeleBloc est le constructeur
         * \param rootBloc est le noeud root
         * \param parent est l'object parent
         */
        ModeleBloc(NodeBloc *rootBloc, QObject *parent);

        Bloc* deleteNodeBloc(NodeBloc* node);

        void deleteBloc(Bloc* bloc);

        /*!
         * \brief setRootNode change le noeud root
         * \param rootBloc
         */
        void setRootNode(NodeBloc *rootBloc);

        /*!
         * \brief getRootNode renvoie la racine de l'arbre
         * \return
         */
        NodeBloc * getRootNode(){
            return m_root;
        }

        /*!
         * \brief index permet de connaitre l'index à la position donné
         * \param row est la ligne
         * \param column est le collone
         * \param parent est l'index du parent
         * \return l'index ciblé
         */
        QModelIndex index(int row, int column, const QModelIndex &parent) const;

        /*!
         * \brief nodeFromIndex permet de connaitre le noeud à l'index donné
         * \param index est l'index
         * \return le noeud
         */
        NodeBloc * nodeFromIndex(const QModelIndex &index) const;

        /*!
         * \brief blocFromOgreNode permet de connaitre le bloc ayant construit le bloc 3D
         * \param node est les bloc 3D
         * \param racine est le noeud où la recherche doit commancer.
         * \return le bloc
         */
        Bloc * blocFromOgreNode(Ogre::SceneNode * node, NodeBloc * racine = NULL);

        /*!
         * \brief rowCount indique le nombre de ligne à l'index donné
         * \param parent est l'index
         * \return le nombre de ligne
         */
        int rowCount(const QModelIndex &parent) const;
        /*!
         * \brief columnCount indique le nombre de collone à l'index donné
         * \param parent est l'index
         * \return le nombre de collone
         */
        int columnCount(const QModelIndex &parent) const;
        /*!
         * \brief parent indique l'index du parent
         * \param child est l'index de l'enefant
         * \return
         */
        QModelIndex parent(const QModelIndex &child) const;
        /*!
         * \brief data permet de conaitre l'information indiqué par role à l'index donné
         * \param index
         * \param role
         * \return la donnée demandé
         */
        QVariant data(const QModelIndex &index, int role) const;

        /*!
         * \brief add ajout un bloc à l'index donné
         * \param bloc est le bloc à ajouter
         * \param index est l'index du parent
         */
        void add(Bloc * bloc, const QModelIndex  &index);

        /*!
         * \brief creatBloc créé un bloc à l'index donné
         * \param index est l'index du parent
         * \return le bloc créé
         */
        Bloc* creatBloc(const QModelIndex  &index);
        /*!
         * \brief creatBloc créé un bloc à l'index donné
         * \param dimension est la dimension du bloc
         * \param position est la position du bloc
         * \param index est l'index du parent
         * \return le bloc créé
         */
        Bloc* creatBloc(Ogre::Vector3 dimension, Ogre::Vector3 position, const QModelIndex  &index = QModelIndex());
        /*!
         * \brief creatBloc créé un bloc à dans le nodeBloc indiqué
         * \param dimension est la dimension du bloc
         * \param position est la position du bloc
         * \param node est le noeud parent du nouveau bloc
         * \return le bloc créé
         */
        Bloc* creatBloc(Ogre::Vector3 dimension, Ogre::Vector3 position, NodeBloc *node);
        /*!
         * \brief creatNodeBloc créé un NodeBloc à partir d'un bloc
         * \param bloc est le bloc initial
         * \param parent est le parent du NodeBloc
         */
        NodeBloc *creatNodeBloc(Bloc *bloc, NodeBloc *parent);
        /*!
         * \brief flags permet de connaitre ce qui est permit à l'index donné
         * \param index
         * \return
         */
        Qt::ItemFlags flags (const QModelIndex  &index ) const;
        /*!
         * \brief changeNameOfCurrentBloc permet de changer le nom du bloc courant
         * \param name
         */
        void changeNameOfCurrentBloc(const QString &name);
        /*!
         * \brief setData permet de changer les donnés à l'index donnée
         * \param index designe l'objet à modifier
         * \param value est la nouvelle valeur
         * \param role est l'action a effectuer
         * \return
         */
        bool setData (const QModelIndex &index, const QVariant &value, int role);
        /*!
         * \brief setBlocCheck change l'etat de selection d'un bloc
         * \param bloc le bloc
         * \param state l'etat
         */
        void setBlocCheck(Bloc * bloc, Qt::CheckState state);
        /*!
         * \brief SetBlocName change le nom du bloc
         * \param bloc
         * \param name
         */
        void SetBlocName(Bloc * bloc, const QString name);
        /*!
         * \brief setBlocEtat change l'etat du bloc
         * \param bloc
         * \param etat
         */
        void setBlocEtat(Bloc * bloc, Bloc::Etat etat);
    signals:
        void si_select(Bloc * bloc);
        void si_ogreDrawBloc(Bloc * bloc);
        void si_createBloc(Bloc * bloc);
        void si_selectBloc(Bloc * bloc);
        void si_delete3Dbloc(Bloc * bloc);
        void si_updateDimensionBloc(Bloc * bloc);
        void si_updatePostionBloc(Bloc * bloc);
        void si_updateCouleurBloc(Bloc* bloc);
    public slots:

    };
}
#endif // MODELEBLOC_H
