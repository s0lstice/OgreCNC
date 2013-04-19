#include "controleurmain.h"

#include <Ogre.h>
#include <iostream>
#include <QMessageBox>

#include "../modele/modelemain.h"
#include "../vue/vuemain.h"
#include "controleurbloc.h"
#include "../modele/bloc/bloc.h"
#include "../modele/bloc/nodebloc.h"
#include "../modele/modelecut.h"
#include "controleurcut.h"
#include "../modele/bloc/modelebloc.h"

using namespace OgreCNC;

ControleurMain::ControleurMain(QWidget *parent) :
    QWidget(parent)
{
    modeleMain = new ModeleMain(this);

    m_controleurCut = NULL;

    initControleurs();

    m_vue = new VueMain(this);
    m_vue->setModele(modeleMain);
    modeleMain->setVue(m_vue);

    initConnections();
}

void ControleurMain::initConnections(){
    connect(m_vue, SIGNAL(si_vueEclate(double)), this, SLOT(sl_vueEclate(double)));
    connect(m_vue, SIGNAL(si_start_cut()), this, SLOT(sl_start_cut()));
    connect(m_vue, SIGNAL(si_update_cut()), this, SLOT(sl_update_cut()));
    connect(m_vue, SIGNAL(si_abort_cut()), this, SLOT(sl_abort_cut()));
    connect(m_vue, SIGNAL(si_valid_cut()), this, SLOT(sl_valid_cut()));
    connect(m_vue, SIGNAL(si_newNameForCurrentBloc(QString)), this, SLOT(sl_newNameForCurrentBloc(QString)));
    connect(m_vue, SIGNAL(si_changeEtatForCurrentBloc(Bloc::Etat)), this, SLOT(sl_changeEtatForCurrentBloc(Bloc::Etat)));
    connect(m_controleurBloc, SIGNAL(si_selectSegment(Ogre::ManualObject*)), m_vue, SLOT(sl_selectSegment(Ogre::ManualObject*)));
}

void ControleurMain::initControleurs(){
    m_controleurBloc = new ControleurBloc(this);
    m_controleurBloc->setModeleBloc(modeleMain->getModeleBloc());
}

/*On traite le signal de début de découpe*/
void ControleurMain::sl_start_cut(){
    ModeleCut* mCut = modeleMain->getModeleCut();

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

bool ControleurMain::sl_abort_cut(){
    m_controleurCut->deleteBlocsCrees();
    m_controleurCut = NULL;
    return true;
}


void ControleurMain::sl_valid_cut(){

    /*On fait une dernière mise à jour de la découpe, et on libère tout*/
    ModeleCut* mCut = modeleMain->getModeleCut();

    mCut->isInUse = false;

    m_vue->activerVoletDecoupe();

    /*m_controleurCut->deleteBlocsCrees();
    m_controleurCut = NULL;*/
}


//***** SLOTS *****//
void ControleurMain::sl_selectBloc(Bloc * bloc){
    m_controleurBloc->selectBloc(bloc);
}

void ControleurMain::sl_selectSegment(Ogre::ManualObject * segment){
    m_controleurBloc->selectSegment(segment);
}

void ControleurMain::replacerBlocs(NodeBloc* node){
    /*On replace les blocs dans leur position avant l'application de la vue éclatée*/

    Bloc* bloc;
    Ogre::Vector3 positionBloc;

    if(node == NULL)
    {
        node = modeleMain->getModeleBloc()->getRootNode();
    }

    //Récupération des fils du noeud bloc
    QVector<Bloc*> * listeFils = node->getListeFils();

    //On parcourt tous les fils du noeud
    for(int i = 0; i < listeFils->count(); i++)
    {
        bloc = listeFils->data()[i];

        switch(bloc->getType())
        {
            case Bloc::BLOC:
                positionBloc = bloc->getPositionVueEclatee();
                bloc->setPosition(positionBloc);

            case Bloc::NODE:
                replacerBlocs((NodeBloc*)bloc);
        }
    }
}

void ControleurMain::sl_vueEclate(double distance){
    /*On replace les blocs à leur position initiale*/
    replacerBlocs(getControleurBloc()->getModeleBloc()->getRootNode());
    m_controleurBloc->appliquerVueEclatee(distance, NULL);
    emit si_updateOgreVue();
}

Bloc * ControleurMain::sl_blocFromOgreNode(Ogre::SceneNode * node){
    return modeleMain->getModeleBloc()->blocFromOgreNode(node);
}

void ControleurMain::sl_newNameForCurrentBloc(const QString &arg1){
    modeleMain->getModeleBloc()->SetBlocName(modeleMain->currentBloc, arg1);
}

void ControleurMain::sl_changeEtatForCurrentBloc(Bloc::Etat etat)
{
    modeleMain->getModeleBloc()->setBlocEtat(modeleMain->currentBloc, etat);
}
