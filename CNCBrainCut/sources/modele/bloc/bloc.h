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

        //Modif Mel
        Ogre::Vector3 m_positionVueEclatee; // position du centre de l'objet dans la vue éclatée

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

        /* Sommets du cube*/
        Ogre::Vector3 m_sommet0;
        Ogre::Vector3 m_sommet1;
        Ogre::Vector3 m_sommet2;
        Ogre::Vector3 m_sommet3;
        Ogre::Vector3 m_sommet4;
        Ogre::Vector3 m_sommet5;
        Ogre::Vector3 m_sommet6;
        Ogre::Vector3 m_sommet7;

        /*Ogre*/
        Ogre::ManualObject * m_blocContour3d; //contour de l'objet 3d
        Ogre::Entity * m_blocFace3d;
        Ogre::SceneNode * m_nodeBloc3d; //noeud de l'obset 3d dans le scenemanangeur
        QString m_faceMatName; //nom du materiaux pour les faces
        QString m_segmentMatName;  //nom du materiaux pour les segments
        Ogre::ColourValue m_colorBloc; //couleur des faces
        Ogre::ColourValue m_colorSegments;

        void updateSommets();
        void updateFaces();
        void updateContour();

    public:

        /*Constructeurs*/
        explicit Bloc(Ogre::Vector3 dimention, Ogre::Vector3 position, NodeBloc * m_parent = NULL);
        Bloc(NodeBloc *parent);
        ~Bloc();

        inline Type getType(){
            return m_type;
        }

        inline NodeBloc * getParent(){
            return m_parent;
        }

        inline Ogre::Vector3 getPositionVueEclatee(){
            return m_positionVueEclatee;
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

        inline Ogre::ManualObject * getBlocContour3d(){
            return m_blocContour3d;
        }

        inline void setBlocContour3d(Ogre::ManualObject *blocContour){
            m_blocContour3d = blocContour;
        }

        inline Ogre::SceneNode* getNodeBloc3d(){
            return m_nodeBloc3d;
        }

        inline void setNodeBloc3d(Ogre::SceneNode* nodeBloc){
            m_nodeBloc3d = nodeBloc;
        }

        inline Ogre::Entity * getBlocFace3d(){
            return m_blocFace3d;
        }

        inline void setBlocFace3d(Ogre::Entity * blocFace){
            m_blocFace3d = blocFace;
        }

        inline void setDimention(Ogre::Vector3 dimention){
            m_dimention = dimention;
            updateSommets();
            updateFaces();
        }

        inline Ogre::Vector3 getDimention(){
            return m_dimention;
        }

        inline Ogre::Vector3 getPosition(){
            return m_position;
        }

        inline void setPosition(Ogre::Vector3 position){
            m_position = position;
            updateFaces();
        }

        inline QString getFaceMatName(){
            return m_faceMatName;
        }

        inline QString getSegmentMatName(){
            return m_segmentMatName;
        }

        inline Ogre::ColourValue getCouleurFace(){
            return m_colorBloc;
        }

        inline Ogre::ColourValue getCouleurSegment(){
            return m_colorSegments;
        }

        inline void setPositionVueEclatee(Ogre::Vector3 position){
            m_positionVueEclatee = position;
        }
    };

}
#endif // BLOC_H
