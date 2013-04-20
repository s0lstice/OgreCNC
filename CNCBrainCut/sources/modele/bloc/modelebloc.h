#ifndef MODELEBLOC_H
#define MODELEBLOC_H

#include <QAbstractItemModel>
#include <Ogre.h>
#include "bloc.h"

namespace OgreCNC{
    class NodeBloc;
    class Bloc;
    class ModeleMain;

    /*!
     * \brief The ModeleBloc class permet la modification des bloc et de l'arbre
     */
    class ModeleBloc : public QAbstractItemModel
    {
        Q_OBJECT

    private:
        /*!
         * \brief m_root le noeud racine de l'arbre
         */
        NodeBloc * m_root;
        /*!
         * \brief m_modeleMain le modele principle de l'application
         */
        ModeleMain * m_modeleMain;

        /*!
         * \brief deleteBloc supprime le bloc apssé en parametre
         * \param bloc
         */
        void deleteBloc(Bloc* bloc);

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
        /*!
         * \brief deleteNodeBloc permet la supression d'un bloc et de ses fils
         * \param node le noued a supprimer
         * \return Le bloc initiale
         */
        Bloc* deleteNodeBloc(NodeBloc* node);


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
        /*!
         * \brief si_ogreDrawBloc est un signal pour demander que le bloc 3D soit redessiné
         * \param bloc
         */
        void si_ogreDrawBloc(Bloc * bloc);
        /*!
         * \brief si_createBloc est un signal pour indiquer la creation d'un bloc
         * \param bloc
         */
        void si_createBloc(Bloc * bloc);
        /*!
         * \brief si_selectBloc est un signal pour indiquer la selaction d'un bloc
         * \param bloc
         */
        void si_selectBloc(Bloc * bloc);
        /*!
         * \brief si_delete3Dbloc est un signal pour demander le masquage d'un bloc 3D
         * \param bloc
         */
        void si_hide3DBloc(Bloc * bloc);
        /*!
         * \brief si_show3DBloc est un signal pour demander l'affichage d'un bloc 3D
         * \param bloc
         */
        void si_show3DBloc(Bloc * bloc);
        /*!
         * \brief si_delete3DBloc est un signal pour demander la supression d'un bloc 3D
         * \param bloc
         */
        void si_delete3DBloc(Bloc * bloc);
        /*!
         * \brief si_updateDimensionBloc est un signal pour indiquer que les dimantion du bloc ont changé
         * \param bloc
         */
        void si_updateDimensionBloc(Bloc * bloc);
        /*!
         * \brief si_updatePositionBloc est un signal pour indiquer que la position du bloc à changé
         * \param bloc
         */
        void si_updatePositionBloc(Bloc * bloc);
        /*!
         * \brief si_updateCouleurBloc  est un signal pour indiquer que la couleur du bloc à changé
         * \param bloc
         */
        void si_updateCouleurBloc(Bloc* bloc);
    public slots:

    };
}
#endif // MODELEBLOC_H
