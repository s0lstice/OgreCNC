#ifndef NODEBLOC_H
#define NODEBLOC_H

#include <QVector>
#include "bloc.h"

namespace OgreCNC {

    class NodeBloc : public Bloc
    {
        Q_OBJECT
    private:
        /*Liste des noeuds fils issus de la découpe du noeud bloc*/
        QVector<Bloc*> * m_listeFils;
        Bloc * m_bloc; //bloc initial, avant dedoupe

    signals:
        void updateDimensionBloc(Bloc * bloc);
        void updatePostionBloc(Bloc * bloc);
        void updateCouleurBloc(Bloc * bloc);

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
            connect(bloc, SIGNAL(updateDimensionBloc(Bloc*)), this, SIGNAL(updateDimensionBloc(Bloc*)));
            connect(bloc, SIGNAL(updatePostionBloc(Bloc*)), this, SIGNAL(updatePostionBloc(Bloc*)));
            connect(bloc, SIGNAL(updateCouleurBloc(Bloc*)), this, SIGNAL(updateCouleurBloc(Bloc*)));
        }

        inline void remove(Bloc * bloc){
            bloc->setParent(NULL); //met le parent du bloc à null
            for(int i =0; i < m_listeFils->count(); ++i){
                if(m_listeFils->at(i) == bloc) //recherche du bloc dans la liste
                {
                    disconnect(bloc, 0,0,0); //deconnection
                    m_listeFils->remove(i); //supression
                    break;
                }
            }

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
