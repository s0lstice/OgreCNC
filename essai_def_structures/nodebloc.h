#ifndef NODEBLOC_H
#define NODEBLOC_H

#include <QVector>
#include "bloc.h"

class NodeBloc : public Bloc
{

protected:
    /*Liste des noeuds fils issus de la découpe du noeud bloc*/
    QVector<Bloc*> * listeFils;

    /*Pointeur vers le bloc associé à ce noeud*/
    Bloc * bloc;

public:
    /*Constructeurs*/

    explicit NodeBloc(NodeBloc * parent = 0);

    /*Avec arguments*/
    NodeBloc(QVector<Bloc*> * listeFilsNoeud = NULL, Bloc * blocNoeud = NULL, NodeBloc * parent = 0);

    NodeBloc(Bloc & blocNoeud);

    /*Définition des accesseurs aux attributs privés*/

    /*Méthodes "Get"*/
    inline QVector<Bloc*> * getListeFils()
    {
        return listeFils;
    }

    inline Bloc* getBloc()
    {
        return bloc;
    }

    /*Méthodes "Set"*/
    inline void setListeFils(QVector<Bloc*> * listeFilsNoeud)
    {
        listeFils = listeFilsNoeud;
    }

    inline void setBloc(Bloc * blocNoeud)
    {
        bloc = blocNoeud;
    }

    /*Destructeurs des attributs de type "pointeur" et de la classe elle même*/
    void destroyListeFils();
    ~NodeBloc();

};

#endif // NODEBLOC_H