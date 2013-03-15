#include "controleurmain.h"

#include "../modele/modelemain.h"
#include "../vue/vuemain.h"
#include "controleurbloc.h"

using namespace OgreCNC;

ControleurMain::ControleurMain(QWidget *parent) :
    QWidget(parent)
{
    m_modele = new ModeleMain(this);
    m_vue = new VueMain(this);
    m_vue->setModele(m_modele);
    m_modele->setVue(m_vue);

    m_gestionBloc = new ControleurBloc(this);
    m_gestionBloc->setRootNode(m_modele->getTravailBoc());

    initConnections();

    m_gestionBloc->creatBloc(Ogre::Vector3(200,100,300),Ogre::Vector3(0,0,0));
}

void ControleurMain::initConnections(){
    connect(m_gestionBloc, SIGNAL(ogreDrawBloc(Bloc*)), m_vue, SLOT(ogreDrawBloc(Bloc*)));
}
