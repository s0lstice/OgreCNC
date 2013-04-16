#ifndef NODEBLOC_H
#define NODEBLOC_H

#include <QVector>
#include "bloc.h"

namespace OgreCNC {

    class NodeBloc : public Bloc
    {

    private:
        /*Liste des noeuds fils issus de la découpe du noeud bloc*/
        QVector<Bloc*> * m_listeFils;
        Bloc * m_bloc; //bloc initial, avant dedoupe

    public:
        /*Constructeurs*/

        explicit NodeBloc(Bloc *bloc = 0, NodeBloc * parent = 0);
        ~NodeBloc();

        /*Définition des accesseurs aux attributs privés*/

        /*Méthodes "Get"*/
        inline QVector<Bloc*> * getListeFils()
        {
            return m_listeFils;
        }

        /*Méthodes "Set"*/
        inline void setListeFils(QVector<Bloc*> * listeFilsNoeud)
        {
            m_listeFils = listeFilsNoeud;
        }

        inline void append(Bloc * bloc){
            bloc->setParent(this);
            m_listeFils->append(bloc);
        }

        inline Bloc * at(int i){
            return m_listeFils->at(i);
        }

        /**
         * @brief getInitialBloc
         * @return Bloc, le bloc initial, avant la decoupe
         */
        inline Bloc * getInitialBloc(){
            return m_bloc;
        }

        QVariantMap serialize();
        void deserialize(QVariantMap nodeBloc);
        /*Destructeurs des attributs de type "pointeur" et de la classe elle même*/
    private:
        void destroyListeFils();

    };

}
#endif // NODEBLOC_H
