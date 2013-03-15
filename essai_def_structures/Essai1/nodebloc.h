#ifndef NODEBLOC_H
#define NODEBLOC_H

#include <QVector>
#include "bloc.h"

class NodeBloc : public Bloc
{

protected:
    /*Liste des noeuds fils issus de la découpe du noeud bloc*/
    QVector<Bloc*> * listeFils;

public:
    /*Constructeurs*/

    explicit NodeBloc(NodeBloc * parent = 0);

    /*Avec arguments*/
    NodeBloc(QVector<Bloc*> * listeFilsNoeud = NULL, NodeBloc * parent = 0);

    /*De recopie*/
    NodeBloc(const NodeBloc& copyNodeBloc);

    /*Définition des accesseurs aux attributs privés*/

    /*Méthodes "Get"*/
    inline QVector<Bloc*> * getListeFils()
    {
        return listeFils;
    }

    /*Méthodes "Set"*/
    inline void setListeFils(QVector<Bloc*> * listeFilsNoeud)
    {
        listeFils = listeFilsNoeud;
    }

    /*Destructeurs des attributs de type "pointeur" et de la classe elle même*/
    void destroyListeFils();
    ~NodeBloc();

};

#endif // NODEBLOC_H
