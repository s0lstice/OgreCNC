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
