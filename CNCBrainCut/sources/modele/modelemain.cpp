#include "modelemain.h"
#include "modelecut.h"
#include "bloc/nodebloc.h"

using namespace OgreCNC;
ModeleMain::ModeleMain(QObject *parent) :
    QObject(parent)
{
    m_RootTravailBlocs = new NodeBloc();
    m_RootTravailBlocs->setName("ROOT");
    m_modeleCut = NULL;
}

ModeleMain::~ModeleMain(){
    delete m_RootTravailBlocs;
    //ModeleCut::~ModeleCut();
}

ModeleCut* ModeleMain::getModeleCut(){
    if(m_modeleCut == NULL)
    {
        m_modeleCut = new ModeleCut();
    }
    return m_modeleCut;
}
