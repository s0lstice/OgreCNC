#ifndef BLOC_H
#define BLOC_H

#include <QObject>

class NodeBloc;

class Bloc
{
public:
    enum enumEtat {UTILISE, PERTE, CHUTE};

protected:
    /*Dimensions d'un bloc (en mm) -- le volume n'est pas stocké comme attribut, mais un accesseur spécifique le calculera*/
    float hauteur;
    float longueur;
    float largeur;

    /*Etat du bloc*/
    enumEtat etat;

    /*Visibilité du bloc : vaut 0 si le bloc est invisible, et 1 sinon*/
    bool visible;

    /*Pointeur vers le noeud parent -- pour le noeud racine, qui n'a pas de père, le pointeur vaut NULL*/
    NodeBloc* noeudPere;

public:

    /*Constructeurs*/

    explicit Bloc(NodeBloc * parent = NULL);

    /*Avec arguments*/
    Bloc(float hauteurBloc, float longueurBloc, float largeurBloc, enumEtat etatBloc = CHUTE, bool visibleBloc = 1, NodeBloc* noeudPereBloc = NULL);

    /*De recopie*/
    Bloc(const Bloc& copyBloc);

    /*Définition des accesseurs aux attributs privés*/

    /*Méthodes "Get"*/
    inline float getHauteurBloc()
    {
        return hauteur;
    }

    inline float getLongueurBloc()
    {
        return longueur;
    }

    inline float getLargeurBloc()
    {
        return largeur;
    }

    inline float getVolumeBloc_cm3()
    {
        return(hauteur*longueur*largeur/1000); //on multiplie par mille pour la conversion mm3 => cm3
    }

    inline enumEtat getEtat()
    {
        return etat;
    }

    inline bool getVisibilite()
    {
        return visible;
    }

    inline NodeBloc* getNoeudPere()
    {
        return noeudPere;
    }

    /*Méthodes "Set"*/
    inline void setHauteurBloc(float hauteurBloc)
    {
        hauteur = hauteurBloc;
    }

    inline void setLongueurBloc(float longueurBloc)
    {
        longueur = longueurBloc;
    }

    inline void setLargeurBloc(float largeurBloc)
    {
        largeur = largeurBloc;
    }

    inline void setEtat(enumEtat etatBloc)
    {
        etat = etatBloc;
    }

    inline void setVisibilite(bool visibleBloc)
    {
        visible = visibleBloc;
    }

    inline void setNoeudPere(NodeBloc* noeudPereBloc)
    {
        noeudPere = noeudPereBloc;
    }

    /*Modificateur des éléments de type "pointeur"*/
    /*inline void modifierNoeudPere(NodeBloc* noeudPereBloc)
    {
        delete noeudPere;
        noeudPere = noeudPereBloc;
    }*/

    /*Destructeurs des attributs de type "pointeur" et de la classe elle même*/
    void destroyNoeudPere();

    ~Bloc();
    
signals:
    
public slots:
    
};

#endif // BLOC_H
