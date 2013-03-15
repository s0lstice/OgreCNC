#include "modelemain.h"
#include "bloc/nodebloc.h"

using namespace OgreCNC;
ModeleMain::ModeleMain(QObject *parent) :
    QObject(parent)
{
    m_RootTravailBlocs = new NodeBloc();
    m_RootTravailBlocs->setName("ROOT");
}

ModeleMain::~ModeleMain(){
    delete m_RootTravailBlocs;
}
