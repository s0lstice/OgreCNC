#ifndef BLOC_H
#define BLOC_H

#include <QString>
#include <Ogre.h>
#include <QVariantMap>

namespace  OgreCNC {

    class NodeBloc;

    class Bloc : public QObject
    {
        Q_OBJECT
    public:
        enum Etat {UTILISE, PERTE, CHUTE};
        enum Type {BLOC, NODE};

    protected:
        /*Dimensions d'un bloc (en mm) -- le volume n'est pas stocké comme attribut, mais un accesseur spécifique le calculera*/
        /*!
         * \brief m_Dimension Dimension d'un bloc (mm), longeur = x; hauteur = y; largeur = z
         */
        Ogre::Vector3 m_dimension;
        /*!
         * \brief m_position est laposition d'un bloc dans l'espace (mm). Definit en fonction du centre de l'objet.
         */
        Ogre::Vector3 m_position;

        /*!
         * \brief m_parent est le pointeur vers le noeud parent -- pour le noeud racine, qui n'a pas de père, le pointeur vaut NULL
         */
        NodeBloc* m_parent;

        /*!
         * \brief m_etat indique si le bloc est utilisé ou non voir OgreCNC::Bloc::Etat
         */
        Etat m_etat;

        /*!
         * \brief m_select indique si le bloc est sélectionné (seul le bloc courent est sélectionné)
         */
        Qt::CheckState m_select;

        /*!
         * \brief m_type indique si c'est un bloc ou un noeud
         */
        Type m_type;

        /*!
         * \brief nbBloc indique le nombre de bloc déjà créé
         */
        static int nbBloc;

        /*!
         * \brief m_id identifiant du bloc
         */
        int m_id;
        /*!
         * \brief m_name est le nom du bloc
         */
        QString m_name;

        /*!
         * \brief m_sommet0 est le sommet 0
         */
        Ogre::Vector3 m_sommet0;
        /*!
         * \brief m_sommet1 est le sommet 1
         */
        Ogre::Vector3 m_sommet1;
        /*!
         * \brief m_sommet2 est le sommet 2
         */
        Ogre::Vector3 m_sommet2;
        /*!
         * \brief m_sommet3 est le sommet 3
         */
        Ogre::Vector3 m_sommet3;
        /*!
         * \brief m_sommet4 est le sommet 4
         */
        Ogre::Vector3 m_sommet4;
        /*!
         * \brief m_sommet5 est le sommet 5
         */
        Ogre::Vector3 m_sommet5;
        /*!
         * \brief m_sommet6 est le sommet 6
         */
        Ogre::Vector3 m_sommet6;
        /*!
         * \brief m_sommet7 est le sommet 7
         */
        Ogre::Vector3 m_sommet7;

        /*!
         * \brief m_nodeBloc3d est un pointeur sur le noeud de l'objet 3D
         */
        Ogre::SceneNode * m_nodeBloc3d;
        /*!
         * \brief m_faceMatName est le nom du materiau pour les faces
         */
        QString m_faceMatName;
        /*!
         * \brief m_segmentMatName est le nom du materiau pour les segments
         */
        QString m_segmentMatName;
        /*!
         * \brief m_colorBloc est la couleur courante des face du bloc
         */
        Ogre::ColourValue m_colorBloc;

        //Modif Mel
        Ogre::Vector3 m_positionVueEclatee; // position du centre de l'objet dans la vue éclatée

    signals:
        void updateDimensionBloc(Bloc * bloc);
        void updatePostionBloc(Bloc * bloc);

    public:


        void updateSommets();

        /*!
         * \brief Bloc est le constructeur
         * \param Dimension est la Dimension du bloc
         * \param position est la position du bloc
         * \param m_parent est le pernet du bloc
         */
        explicit Bloc(Ogre::Vector3 Dimension, Ogre::Vector3 position, NodeBloc * m_parent = NULL);

        /*!
         * \brief Bloc contstructeur de blocdepuis un NodeBloc, la creation du bloc 3D ne serra pas faite car les Dimension minimal ne serront pas réspecté. Le bloc doit etre initilisé et updaté.
         * \param parent
         */
        Bloc(NodeBloc *parent);

        ~Bloc();

        /*!
         * \brief setParent definit un nouveau parent au bloc.
         * \param parent
         */
        inline void setParent(NodeBloc * parent){m_parent = parent;}

        /*!
         * \brief getType pour savoir si c'est un Bloc ou un NodeBloc
         * \return
         */
        inline Type getType(){
            return m_type;
        }

        /*!
         * \brief getParent pour connetre le partent du bloc
         * \return
         */
        inline NodeBloc * getParent(){
            return m_parent;
        }

        /*!
         * \brief getPositionVueEclatee pour connaitre la position dans la vue éclaté
         * \return
         */
        inline Ogre::Vector3 getPositionVueEclatee(){
            return m_positionVueEclatee;
        }

        /*!
         * \brief getCheck est utilisé pour saboir si le bloc est lobjet courent
         * \return
         */
        inline Qt::CheckState getCheck(){
            return m_select;
        }

        /*!
         * \brief setCheck sélectionne le bloc
         * \param state
         */
        inline void setCheck(Qt::CheckState state){
            m_select = state;
        }

        /*!
         * \brief getName renvoie le nom du bloc
         * \return
         */
        inline QString getName(){
            return m_name;
        }

        /*!
         * \brief setName change le nom du bloc
         * \param name
         */
        inline void setName(QString name){
            m_name = name;
        }

        /*!
         * \brief getId renvoie l'identifiant du bloc
         * \return
         */
          inline int getId(){
            return m_id;
        }

        /*!
         * \brief getNodeBloc3d pour obtenir le bloc 3D, ne doit etre utilisé que la Ogre !
         * \return
         */
        inline Ogre::SceneNode* getNodeBloc3d(){
            return m_nodeBloc3d;
        }

        /*!
         * \brief setNodeBloc3d definit un nouveau blob 3d, ne doit etre utilisé que dans ogre
         * \param nodeBloc
         */
        inline void setNodeBloc3d(Ogre::SceneNode* nodeBloc){
            m_nodeBloc3d = nodeBloc;
        }

        /*!
         * \brief setDimension change les Dimension du bloc
         * \param Dimension
         */
        inline void setDimension(Ogre::Vector3 Dimension){
            m_dimension = Dimension;
            updateSommets();
            emit updateDimensionBloc(this);
        }

        /*!
         * \brief getDimension renvoie les Dimension du bloc
         * \return
         */
        inline Ogre::Vector3 getDimension(){
            return m_dimension;
        }

        /*!
         * \brief getPosition renvoie la position du bloc
         * \return
         */
        inline Ogre::Vector3 getPosition(){
            return m_position;
        }

        /*!
         * \brief setPosition change la position du bloc
         * \param position
         */
        inline void setPosition(Ogre::Vector3 position){
            m_position = position;
            emit updatePostionBloc(this);
        }

        /*!
         * \brief getFaceMatName renvoi le nom du materiau utilisé pour le dessin des faces
         * \return
         */
        inline QString getFaceMatName(){
            return m_faceMatName;
        }
        /*!
         * \brief getSegmentMatName renvoi le nom du materiau utilisé pour dessin les segments
         * \return
         */
        inline QString getSegmentMatName(){
            return m_segmentMatName;
        }

        /*!
         * \brief getCouleurFacerenvoie la couleur courente des faces
         * \return
         */
        inline Ogre::ColourValue getCouleurFace(){
            return m_colorBloc;
        }

        /*!
         * \brief setPositionVueEclatee revoie la position dans la vue éclaté
         * \param position
         */
        inline void setPositionVueEclatee(Ogre::Vector3 position){
            m_positionVueEclatee = position;
        }

        /*!
         * \brief getSommet0 indique la position du sommet 0
         * \return
         */
        inline Ogre::Vector3 getSommet0(){ return m_sommet0;}
        /*!
         * \brief getSommet1 indique la position du sommet 1
         * \return
         */
        inline Ogre::Vector3 getSommet1(){ return m_sommet1;}
        /*!
         * \brief getSommet2 indique la position du sommet 2
         * \return
         */
        inline Ogre::Vector3 getSommet2(){ return m_sommet2;}
        /*!
         * \brief getSommet3 indique la position du sommet 3
         * \return
         */
        inline Ogre::Vector3 getSommet3(){ return m_sommet3;}
        /*!
         * \brief getSommet4 indique la position du sommet 4
         * \return
         */
        inline Ogre::Vector3 getSommet4(){ return m_sommet4;}
        /*!
         * \brief getSommet5 indique la position du sommet 5
         * \return
         */
        inline Ogre::Vector3 getSommet5(){ return m_sommet5;}
        /*!
         * \brief getSommet6 indique la position du sommet 6
         * \return
         */
        inline Ogre::Vector3 getSommet6(){ return m_sommet6;}
        /*!
         * \brief getSommet7 indique la position du sommet 7
         * \return
         */
        inline Ogre::Vector3 getSommet7(){ return m_sommet7;}
        /*!
         * \brief serialize le bloc
         * \return
         */
        QVariantMap serialize();
        /*!
         * \brief deserialize le bloc
         * \param bloc
         */
        void deserialize(QVariantMap bloc);
    };

}
#endif // BLOC_H
