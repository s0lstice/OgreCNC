#include "nodebloc.h"

/*Constructeurs*/

NodeBloc::NodeBloc(NodeBloc * parent) : Bloc(parent)
{
    listeFils = NULL;
    bloc = NULL;
}

/*Avec arguments*/
NodeBloc::NodeBloc(QVector<Bloc*> * listeFilsNoeud, Bloc * blocNoeud, NodeBloc * parent) : Bloc(parent)
{
    listeFils = listeFilsNoeud;
    bloc = blocNoeud;
}

NodeBloc::NodeBloc(Bloc & blocNoeud)
{
    bloc = &blocNoeud;
    listeFils = NULL;
}

/*Destructeurs des attributs de type "pointeur" et de la classe elle même*/
void NodeBloc::destroyListeFils()
{
    qDeleteAll(listeFils->begin(),listeFils->end());
    listeFils->clear();
    delete listeFils;
    listeFils = NULL;
}

NodeBloc::~NodeBloc()
{
    destroyListeFils();
}
