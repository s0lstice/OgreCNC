#include "nodebloc.h"

using namespace OgreCNC;
/*Constructeurs*/

NodeBloc::NodeBloc( Bloc * bloc, NodeBloc * parent) : Bloc(parent)
{
    m_bloc = bloc;
    m_listeFils = new QVector<Bloc*>();
    m_type = Bloc::NODE;
}

NodeBloc::~NodeBloc()
{
    //destruction de la liste de fils
    while(!m_listeFils->isEmpty()){
        delete m_listeFils->back();
        m_listeFils->pop_back();
    }
    delete m_listeFils;
    m_listeFils = NULL;
}

QVariantMap NodeBloc::serialize(){
    QVariantMap nodeMap;

    nodeMap = serialize();

    nodeMap.insert("bloc", m_bloc->serialize());

    QVariantList childsListe;

    for(int i = 0; m_listeFils->count(); ++i)
    {
        if(m_listeFils->at(i)->getType() == Bloc::BLOC)
            childsListe << ((Bloc *)m_listeFils->at(i))->serialize();
        else
            childsListe << ((NodeBloc *)m_listeFils->at(i))->serialize();

    }

    nodeMap.insert("membres", childsListe);
    return nodeMap;
}

void NodeBloc::deserialize(QVariantMap nodeBloc){
    Bloc::deserialize(nodeBloc);

    QVariantList childsListe = nodeBloc["membres"].toList();

    for(int i = 0; i < childsListe.count() ; ++i)
    {
        QVariantMap childMap = childsListe[i].toMap();
        Etat etat = (Bloc::Etat)childMap["etat"].toInt();

        switch (etat) {
        case Bloc::BLOC:
        {
            Bloc * bloc = new Bloc(this);
            bloc->deserialize(childMap);
            m_listeFils->append(bloc);
        }
            break;

        case Bloc::NODE:
        {
            Bloc * bloc = new Bloc(m_parent);
            bloc->deserialize(childMap["bloc"].toMap());
            NodeBloc * node = new NodeBloc(bloc,this);
            node->deserialize(childMap);
            m_listeFils->append(node);
        }
            break;
        }
    }
}
