#include "controleurmain.h"

#include <Ogre.h>
#include <iostream>
#include <QMessageBox>

#include "../modele/modelemain.h"
#include "../vue/vuemain.h"
#include "controleurbloc.h"
#include "../modele/bloc/bloc.h"
#include "../modele/modelecut.h"
#include "controleurcut.h"

using namespace OgreCNC;

ControleurMain::ControleurMain(QWidget *parent) :
    QWidget(parent)
{
    m_modele = new ModeleMain(this);

    m_controleurCut = NULL;

    initControleurs();

    m_vue = new VueMain(this);
    m_vue->setModele(m_modele);
    m_modele->setVue(m_vue);

    initConnections();

    Bloc* bloc1 = m_gestionBloc->creatBloc(Ogre::Vector3(80,50,50),Ogre::Vector3(0, 0, 0)); //800 600 150
    Bloc* bloc2 = m_gestionBloc->creatBloc(Ogre::Vector3(500,150,950),Ogre::Vector3(0, 0, 0)); //800 600 150
    Bloc* bloc3 = m_gestionBloc->creatBloc(Ogre::Vector3(5010,1500,9550),Ogre::Vector3(0, 0, 0)); //800 600 150

    bloc1->setDimension(Ogre::Vector3(800,150,600));
    bloc2->setDimension(Ogre::Vector3(50,50,50));
    bloc3->setDimension(Ogre::Vector3(300,300,300));
}

void ControleurMain::initConnections(){
    connect(m_vue, SIGNAL(si_vueEclate(double)), this, SLOT(sl_vueEclate(double)));
    connect(m_vue, SIGNAL(si_start_cut()), this, SLOT(sl_start_cut()));
    connect(m_vue, SIGNAL(si_update_cut()), this, SLOT(sl_update_cut()));
    connect(m_vue, SIGNAL(si_abort_cut()), this, SLOT(sl_abort_cut()));
    connect(m_gestionBloc, SIGNAL(si_createBloc(Bloc*)), m_vue, SLOT(sl_creat3Dbloc(Bloc*)));
    connect(m_gestionBloc, SIGNAL(si_selectBloc(Bloc*)), m_vue, SLOT(sl_selectBloc(Bloc*)));
    connect(m_gestionBloc, SIGNAL(si_selectSegment(Ogre::ManualObject*)), m_vue, SLOT(sl_selectSegment(Ogre::ManualObject*)));
}

void ControleurMain::initControleurs(){
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

void ControleurMain::sl_abort_cut(){
//COMMANTE CAR ui N EST PAS DECLARE

//    /*VOIR AVEC MICKAEL : EST-CE QU'ON FAIT ICI LA REACTIVATION/DESACTIVATION DE TOUS LES BOUTONS OU PAS ?*/
//    /*On désactive les boutons d'annulation et de validation*/
//    ui->validerDecoupe_pushButton->setEnabled(false);
//    ui->annulerDecoupe_pushButton->setEnabled(false);
//    /*On réactive le bouton de lancement d'une découpe*/
//    ui->demarrerDecoupe_pushButton->setEnabled(true);
//    /*On désactive également tous les autres boutons, qui ne sont accessibles que lorsque l'utilisateur démarre une découpe*/
//    ui->definitionDecoupeGroupBox->setEnabled(false);
//    ui->modeDecoupeDroit_GroupBox->setEnabled(false);
//    ui->modeDecoupeGauche_GroupBox->setEnabled(false);
//    ui->positionPerteGroupBox->setEnabled(false);
}


//***** SLOTS *****//
void ControleurMain::sl_selectBloc(Bloc * bloc){
    m_gestionBloc->selectBloc(bloc);
}

void ControleurMain::sl_selectSegment(Ogre::ManualObject * segment){
    m_gestionBloc->selectSegment(segment);
}

void ControleurMain::sl_vueEclate(double distance){
    m_gestionBloc->appliquerVueEclatee(distance, NULL);
    emit si_updateOgreVue();
}

Bloc * ControleurMain::sl_blocFromOgreNode(Ogre::SceneNode * node){
    return m_gestionBloc->blocFromOgreNode(node);
}
