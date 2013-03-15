#ifndef BLOC_H
#define BLOC_H

#include <QString>
#include <Ogre.h>

namespace  OgreCNC {

    class NodeBloc;

    class Bloc
    {
    public:
        enum Etat {UTILISE, PERTE, CHUTE};
        enum Type {BLOC, NODE};

    protected:
        /*Dimensions d'un bloc (en mm) -- le volume n'est pas stocké comme attribut, mais un accesseur spécifique le calculera*/
        Ogre::Vector3 m_dimention; //longeur = x; hauteur = y; largeur = z
        Ogre::Vector3 m_position; // position du centre de l'objet

        /*Pointeur vers le noeud parent -- pour le noeud racine, qui n'a pas de père, le pointeur vaut NULL*/
        NodeBloc* m_parent;

        /*Etat du bloc*/
        Etat m_etat;

        /*Visibilité du bloc : vaut 0 si le bloc est invisible, et 1 sinon*/
        Qt::CheckState m_visible;

        /*Type de bloc, boc (leaf) or node*/
        Type m_type;

        /*identifiant et denomination*/
        static int m_id;
        QString m_name;

        /*Ogre*/
        Ogre::ManualObject * m_bloc3d; //obet 3d
        Ogre::SceneNode * m_nodeBloc3d; //noeud de l'obset 3d dans le scenemanangeur
        QString m_matName; //nom du materiaux


    public:

        /*Constructeurs*/
        explicit Bloc(Ogre::Vector3 dimention, Ogre::Vector3 position, NodeBloc * m_parent = NULL);
        Bloc(NodeBloc *parent);
        ~Bloc();
        void updateBloc3d();

        inline Type getType(){
            return m_type;
        }

        inline NodeBloc * getParent(){
            return m_parent;
        }

        inline void setParent(NodeBloc * parent){
            m_parent = parent;
        }

        inline Qt::CheckState getVisibilite(){
            return m_visible;
        }

        inline void setVisibilite(Qt::CheckState state){
            m_visible = state;
        }

        inline QString getName(){
            return m_name;
        }

        inline void setName(QString name){
            m_name = name;
        }

        inline int getId(){
            return m_id;
        }

        inline Ogre::ManualObject * getBloc3d(){
            return m_bloc3d;
        }

        inline void setNodeBloc3d(Ogre::SceneNode * node){
            m_nodeBloc3d = node;
        }
    };

}
#endif // BLOC_H
