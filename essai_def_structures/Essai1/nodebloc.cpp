#include "nodebloc.h"

/*Constructeurs*/

NodeBloc::NodeBloc(NodeBloc * parent) : Bloc(parent)
{
    listeFils = NULL;
}

/*Avec arguments*/
NodeBloc::NodeBloc(QVector<Bloc*> * listeFilsNoeud, NodeBloc * parent) : Bloc(parent)
{
    listeFils = listeFilsNoeud;
}

/*De recopie*/
/*NodeBloc::NodeBloc(const NodeBloc& copyNodeBloc) : Bloc(copyNodeBloc.noeudPere)
{*/
    /*Recopie des paramètres hérités de Bloc*/
    /*this->hauteur = copyNodeBloc.hauteur;
    this->longueur = copyNodeBloc.longueur;
    this->largeur = copyNodeBloc.largeur;
    this->etat = copyNodeBloc.etat;
    this->noeudPere = copyNodeBloc.noeudPere;*/

    /*Recopie des attributs spécifiques à un noeud*/
    //this->listeFils = new QVector<Bloc*>;
    /*for(int i = 0; i < copyNodeBloc.listeFils->size(); i++)
    {
        this->listeFils->append(copyNodeBloc.listeFils->data()[i]);
    }*/

    /*Bloc tmp;
    for(int i = 0; i < copyNodeBloc.listeFils->size(); i++)
    {
        tmp = new Bloc(copyNodeBloc.listeFils->data()[i]);
        this->listeFils->append(&tmp);
    }

}*/

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
