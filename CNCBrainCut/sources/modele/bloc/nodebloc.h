#ifndef NODEBLOC_H
#define NODEBLOC_H

#include <QVector>
#include "bloc.h"

namespace OgreCNC {
    /*!
     * \brief The NodeBloc class definit un noeud
     */
    class NodeBloc : public Bloc
    {
        Q_OBJECT
    private:
        /*!
         * \brief m_listeFils Liste des noeuds fils issus de la découpe du noeud bloc
         */
        QVector<Bloc*> * m_listeFils;
        /*!
         * \brief m_bloc est le bloc initial
         */
        Bloc * m_bloc; //bloc initial, avant decoupe

    signals:
        /*!
         * \brief updateDimensionBloc est le signal qui indique que les dimensions du bloc ont changées
         * \param bloc est le bloc qui a ete modifié
         */
        void updateDimensionBloc(Bloc * bloc);
        /*!
         * \brief updatePostionBloc est le signal qui indique que la position du bloc à changée
         * \param bloc est le bloc qui a ete modifié
         */
        void updatePostionBloc(Bloc * bloc);
        /*!
         * \brief updateCouleurBloc est le signal qui indique que la couleur du bloc à changée
         * \param bloc est le bloc qui a ete modifié
         */
        void updateCouleurBloc(Bloc * bloc);

    public:
        /*!
         * \brief NodeBloc est le constructeur
         * \param bloc est le bloc initial
         * \param parent est le noeud parent. Si ce paremetre est null, le NodeBLoc est rattaché à la racine
         */
        explicit NodeBloc(Bloc *bloc, NodeBloc * parent = 0);
        ~NodeBloc();

        /*Définition des accesseurs aux attributs privés*/

        /*Méthodes "Get"*/
        /*!
         * \brief getListeFils renvoie la liste des fils
         * \return
         */
        inline QVector<Bloc*> * getListeFils()
        {
            return m_listeFils;
        }
        /*!
         * \brief append ajout un element au noeud et crée les connections de mise a jour des bloc
         * \param bloc
         */
        inline void append(Bloc * bloc){
            bloc->setParent(this);
            m_listeFils->append(bloc);
            connect(bloc, SIGNAL(updateDimensionBloc(Bloc*)), this, SIGNAL(updateDimensionBloc(Bloc*)));
            connect(bloc, SIGNAL(updatePostionBloc(Bloc*)), this, SIGNAL(updatePostionBloc(Bloc*)));
            connect(bloc, SIGNAL(updateCouleurBloc(Bloc*)), this, SIGNAL(updateCouleurBloc(Bloc*)));
        }

        /*!
         * \brief remove retir un element du noeud et detruit ses connections
         * \param bloc
         */
        inline void remove(Bloc * bloc){
            bloc->setParent(NULL); //met le parent du bloc à null
            for(int i =0; i < m_listeFils->count(); ++i){
                if(m_listeFils->at(i) == bloc) //recherche du bloc dans la liste
                {
                    disconnect(bloc, 0,0,0); //deconnection
                    m_listeFils->remove(i); //supression
                    break;
                }
            }

        }

        /*!
         * \brief at renvoie l'item à la position donné
         * \param i
         * \return
         */
        inline Bloc * at(int i){
            return m_listeFils->at(i);
        }

        /**
         * @brief getInitialBloc renvoi le bloc initial avant la decoupe
         * @return Bloc, le bloc initial, avant la decoupe
         */
        inline Bloc * getInitialBloc(){
            return m_bloc;
        }
        /*!
         * \brief setInitialBloc definit le bloc intial d'avant la découpe
         * \param bloc
         */
        inline void setInitialBloc(Bloc * bloc){
            m_bloc = bloc;
            m_nodeBloc3d = m_bloc->getNodeBloc3d();
        }
        /*!
         * \brief updateSommets met a jour les somme du blic initial
         */
        void updateSommets();
        /*!
         * \brief setEtat change l'etat du bloc initial
         * \param etat est le nouvel etat
         */
        void setEtat(Etat etat);

        /*!
         * \brief getPositionVueEclatee pour connaitre la position dans la vue éclaté du bloc initial
         * \return
         */
        inline Ogre::Vector3 getPositionVueEclatee(){
            return m_bloc->getPositionVueEclatee();
        }

        /*!
         * \brief setCheck sélectionne le noeud et le bloc initial
         * \param state
         */
        void setCheck(Qt::CheckState state);

        /*!
         * \brief setName change le nom du noeud et du bloc initial
         * \param name
         */
        inline void setName(QString name){
            m_bloc->setName(name);
            m_name = name;
        }

        /*!
         * \brief getNodeBloc3d pour obtenir le bloc 3D initial, ne doit etre utilisé que la Ogre !
         * \return
         */
        inline Ogre::SceneNode* getNodeBloc3d(){
            return m_bloc->getNodeBloc3d();
        }

        /*!
         * \brief setNodeBloc3d definit un nouveau blob 3d initial, ne doit etre utilisé que dans ogre
         * \param nodeBloc
         */
        inline void setNodeBloc3d(Ogre::SceneNode* nodeBloc){
            m_bloc->setNodeBloc3d(nodeBloc);
        }

        /*!
         * \brief setDimension change les Dimension du bloc initial
         * \param Dimension
         */
        inline void setDimension(Ogre::Vector3 Dimension){
            m_bloc->setDimension(Dimension);
            emit updateDimensionBloc(m_bloc);
        }

        /*!
         * \brief getDimension renvoie les Dimension du bloc initial
         * \return
         */
        inline Ogre::Vector3 getDimension(){
            return m_bloc->getDimension();
        }

        /*!
         * \brief getPosition renvoie la position du bloc initial
         * \return
         */
        inline Ogre::Vector3 getPosition(){
            return m_bloc->getPosition();
        }

        /*!
         * \brief setPosition change la position du bloc initial
         * \param position
         */
        inline void setPosition(Ogre::Vector3 position){
            m_bloc->setPosition(position);
            emit updatePostionBloc(m_bloc);
        }

        /*!
         * \brief getFaceMatName renvoi le nom du materiau utilisé pour le dessin des faces du bloc initial
         * \return
         */
        inline QString getFaceMatName(){
            return m_bloc->getFaceMatName();
        }

        /*!
         * \brief getSegmentMatName renvoi le nom du materiau utilisé pour dessin les segments du segment du bloc initial
         * \return
         */
        inline QString getSegmentMatName(){
            return m_bloc->getSegmentMatName();
        }

        /*!
         * \brief setPositionVueEclatee revoie la position dans la vue éclaté du bloc initial
         * \param position
         */
        inline void setPositionVueEclatee(Ogre::Vector3 position){
            m_bloc->setPosition(position);
        }

        /*!
         * \brief getSommet0 indique la position du sommet 0 du bloc initial
         * \return
         */
        inline Ogre::Vector3 getSommet0(){ return m_bloc->getSommet0();}

        /*!
         * \brief getSommet1 indique la position du sommet 1 du bloc initial
         * \return
         */
        inline Ogre::Vector3 getSommet1(){ return m_bloc->getSommet1();}

        /*!
         * \brief getSommet2 indique la position du sommet 2 du bloc initial
         * \return
         */
        inline Ogre::Vector3 getSommet2(){ return m_bloc->getSommet2();}

        /*!
         * \brief getSommet3 indique la position du sommet 3 du bloc initial
         * \return
         */
        inline Ogre::Vector3 getSommet3(){ return m_bloc->getSommet3();}

        /*!
         * \brief getSommet4 indique la position du sommet 4 du bloc initial
         * \return
         */
        inline Ogre::Vector3 getSommet4(){ return m_bloc->getSommet4();}

        /*!
         * \brief getSommet5 indique la position du sommet 5 du bloc initial
         * \return
         */
        inline Ogre::Vector3 getSommet5(){ return m_bloc->getSommet5();}

        /*!
         * \brief getSommet6 indique la position du sommet 6 du bloc initial
         * \return
         */
        inline Ogre::Vector3 getSommet6(){ return m_bloc->getSommet6();}

        /*!
         * \brief getSommet7 indique la position du sommet 7 du bloc initial
         * \return
         */
        inline Ogre::Vector3 getSommet7(){ return m_bloc->getSommet7();}

        /*!
         * \brief serialize le NodeBloc
         * \return
         */
        QVariantMap serialize();
        /*!
         * \brief deserialize le NodeBloc
         * \param nodeBloc
         */
        void deserialize(QVariantMap nodeBloc);

    private:

    };

}
#endif // NODEBLOC_H
