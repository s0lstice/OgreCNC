#include "controleurmain.h"

#include "../modele/modelemain.h"
#include "../vue/vuemain.h"
#include "controleurbloc.h"
#include "../modele/bloc/bloc.h"
#include <Ogre.h>
#include <iostream>

using namespace OgreCNC;

ControleurMain::ControleurMain(QWidget *parent) :
    QWidget(parent)
{
    m_modele = new ModeleMain(this);

    initControleur();

    m_vue = new VueMain(this);
    m_vue->setModele(m_modele);
    m_modele->setVue(m_vue);

    initConnections();

    Bloc* bloc1 = m_gestionBloc->creatBloc(Ogre::Vector3(200,100,300),Ogre::Vector3(0,0,0));
    Bloc* bloc2 = m_gestionBloc->creatBloc(Ogre::Vector3(300,100,200),Ogre::Vector3(100,20,50));

    Ogre::SceneNode* node2 = bloc2->getNodeBloc3d();
    Ogre::SceneNode* node1 = bloc1->getNodeBloc3d();

    Ogre::Vector3 positionIni1;
    positionIni1= bloc1->getPosition();
    Ogre::Vector3 positionIni2;
    positionIni2 = bloc2->getPosition();

    m_gestionBloc->appliquerVueEclatee(50,NULL);


}

void ControleurMain::initConnections(){
    connect(m_gestionBloc, SIGNAL(ogreDrawBloc(Bloc*)), m_vue, SLOT(ogreDrawBloc(Bloc*)));
}

void ControleurMain::initControleur(){
    m_gestionBloc = new ControleurBloc(this);
    m_gestionBloc->setRootNode(m_modele->getTravailBloc());
}
