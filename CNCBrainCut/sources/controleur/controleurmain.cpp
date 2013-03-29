#include "controleurmain.h"

#include "../modele/modelemain.h"
#include "../vue/vuemain.h"
#include "controleurbloc.h"
#include "../modele/bloc/bloc.h"
#include "../modele/modelecut.h"
#include "controleurcut.h"
#include <Ogre.h>
#include <iostream>
#include <QMessageBox>

using namespace OgreCNC;

ControleurMain::ControleurMain(QWidget *parent) :
    QWidget(parent)
{
    m_modele = new ModeleMain(this);

    m_controleurCut = NULL;

    initControleur();

    m_vue = new VueMain(this);
    m_vue->setModele(m_modele);
    m_modele->setVue(m_vue);

    initConnections();

    Bloc* bloc1 = m_gestionBloc->creatBloc(Ogre::Vector3(2.00,1.00,3.00),Ogre::Vector3(0,0,0));
    Bloc* bloc2 = m_gestionBloc->creatBloc(Ogre::Vector3(3.00,1.00,2.00),Ogre::Vector3(1.00,0.20,0.50));

    Ogre::SceneNode* node2 = bloc2->getNodeBloc3d();
    Ogre::SceneNode* node1 = bloc1->getNodeBloc3d();

    Ogre::Vector3 positionIni1;
    positionIni1= bloc1->getPosition();
    Ogre::Vector3 positionIni2;
    positionIni2 = bloc2->getPosition();

    m_gestionBloc->appliquerVueEclatee(100,NULL);
}

void ControleurMain::initConnections(){
    connect(m_vue, SIGNAL(si_start_cut()), this, SLOT(sl_start_cut()));
    connect(m_vue, SIGNAL(si_update_cut()), this, SLOT(sl_update_cut()));
    connect(m_gestionBloc, SIGNAL(si_createBloc(Bloc*)), m_vue, SLOT(sl_createBloc(Bloc*)));
    connect(m_vue, SIGNAL(si_select(int)), this, SLOT(sl_select(int)));
    connect(m_gestionBloc, SIGNAL(si_select(Bloc*)), m_vue, SLOT(sl_selectBloc(Bloc*)));
}

void ControleurMain::initControleur(){
    m_gestionBloc = new ControleurBloc(this);
    m_gestionBloc->setRootNode(m_modele->getTravailBloc());
}

/*On traite le signal de début de découpe*/
void ControleurMain::sl_start_cut(){
    ModeleCut* mCut = m_modele->getModeleCut();

    if(mCut->isInUse == true)
    {
        QMessageBox::warning(m_vue,QObject::tr("Découpe en cours"),QObject::tr("Une découpe est déjà en cours,\nveuillez la terminer pour en commencer une nouvelle\n"));
    }
    else
    {
        /*Initialise le controleurCut à partir de son modeleCut*/
        m_controleurCut = new ControleurCut(mCut,this);
        /*Le modèle est en cours d'utilisation*/
        mCut->isInUse = true;
        /*On informe la vue que l'initialisation a eu lieu*/
        emit si_init_cut(mCut);
    }
}


/*On traite la mise à jour des paramètres saisis pour la découpe*/
void ControleurMain::sl_update_cut(){
    if(m_controleurCut != NULL)
    {
        m_controleurCut->update_cut();
    }
}

//***** SLOTS *****//
void ControleurMain::sl_select(int id){
    m_gestionBloc->select(id);
}
