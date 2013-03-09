#ifndef BLOC_H
#define BLOC_H

#include <QString>
#include <Ogre.h>

class NodeBloc;

class Bloc
{
public:
    enum Etat {UTILISE, PERTE, CHUTE};
    enum Visible {VISIBLE, MASQUE};

    /*Dimensions d'un bloc (en mm) -- le volume n'est pas stocké comme attribut, mais un accesseur spécifique le calculera*/
    float hauteur;
    float longueur;
    float largeur;

    /*Etat du bloc*/
    Etat utilisation;

    /*Visibilité du bloc : vaut 0 si le bloc est invisible, et 1 sinon*/
    Visible visible;

    /*Pointeur vers le noeud parent -- pour le noeud racine, qui n'a pas de père, le pointeur vaut NULL*/
    NodeBloc* parent;

    /*identifiant et denomination*/
    int id;
    QString name;

    /*Ogre*/
    Ogre::ManualObject * bloc3d; //obet 3d
    Ogre::SceneNode * nodeBloc3d; //noeud de l'obset 3d dans le scenemanangeur
    QString matName; //nom du materiaux
    int posx; //position du centre de l'objet en x
    int posy; //position du centre de l'objet en y
    int posz; //position du centre de l'objet en z

    /*Constructeurs*/

    explicit Bloc(NodeBloc * parent = NULL);
    ~Bloc();
    void updateBloc3d();
};

#endif // BLOC_H
