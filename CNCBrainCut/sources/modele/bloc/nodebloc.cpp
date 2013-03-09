#include "nodebloc.h"

/*Constructeurs*/

NodeBloc::NodeBloc(NodeBloc * parent) : Bloc(parent)
{
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
