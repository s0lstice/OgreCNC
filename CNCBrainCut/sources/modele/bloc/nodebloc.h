#ifndef NODEBLOC_H
#define NODEBLOC_H

#include <QVector>
#include "bloc.h"

class NodeBloc : public Bloc
{

private:
    /*Liste des noeuds fils issus de la découpe du noeud bloc*/
    QVector<Bloc*> * listeFils;

public:
    /*Constructeurs*/

    explicit NodeBloc(NodeBloc * parent = 0);

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

    inline void append(Bloc * bloc){
        bloc->parent = this;
        listeFils->append(bloc);
    }

    inline Bloc * at(int i){
        return listeFils->at(i);
    }

    /*Destructeurs des attributs de type "pointeur" et de la classe elle même*/
    void destroyListeFils();
    ~NodeBloc();

};

#endif // NODEBLOC_H
