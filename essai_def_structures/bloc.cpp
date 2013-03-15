#include "bloc.h"

#include "nodebloc.h"

/*Constructeurs*/

Bloc::Bloc(NodeBloc *parent)
{
    hauteur = 0;
    longueur = 0;
    largeur = 0;
    etat = CHUTE;
    visible = 1;
    noeudPere = parent;
}

/*Avec arguments*/
Bloc::Bloc(float hauteurBloc, float longueurBloc, float largeurBloc, enumEtat etatBloc, bool visibleBloc, NodeBloc* noeudPereBloc)
{
    hauteur = hauteurBloc;
    longueur = longueurBloc;
    largeur = largeurBloc;
    etat = etatBloc;
    visible = visibleBloc;
    noeudPere = noeudPereBloc;
}

/*Destructeurs des attributs de type "pointeur" et de la classe elle même*/
void Bloc::destroyNoeudPere()
{
    delete noeudPere;
    noeudPere = NULL;
}

Bloc::~Bloc()
{
    destroyNoeudPere();
}
