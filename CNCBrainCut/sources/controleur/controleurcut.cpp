#include "controleurcut.h"
#include "../modele/modelecut.h"
#include "controleurmain.h"
#include "../modele/modelemain.h"
#include "controleurbloc.h"
#include "../modele/bloc/nodebloc.h"


using namespace OgreCNC;
ControleurCut::ControleurCut(ModeleCut* modele, QObject *parent) : QObject(parent)
{
    m_modeleCut = modele;
    controleurMain = qobject_cast<ControleurMain *>(parent);

    /*Création du noeud correspondant au bloc courant*/
    if(m_modeleCut->nbFils != 0)
        noeud = controleurMain->modeleMain->getModeleBloc()->creatNodeBloc(controleurMain->modeleMain->currentBloc,controleurMain->modeleMain->currentBloc->getParent());

    /*Création du nombre de blocs fils nécessaires*/
    Ogre::Vector3 dim(controleurMain->modeleMain->currentBloc->getDimension()/m_modeleCut->nbFils);
    for(int i = 0; i < m_modeleCut->nbFils; i++)
    {
        Bloc* blocFils = controleurMain->modeleMain->getModeleBloc()->creatBloc(dim,controleurMain->modeleMain->currentBloc->getPosition()+i,noeud);
    }
}


void ControleurCut::deleteBlocsCrees(){
    /*if(noeud->getListeFils() != NULL)
    {
        if(m_modeleCut != NULL)
        {
            for(int i = 0; i < m_modeleCut->nbFils; i++)
            {
                //détruire les blocs fils
                controleurMain->m_modele->getModeleBloc()->deleteBloc(noeud->getListeFils()->at(i));
            }
        }
    }*/
    if(noeud != NULL)
    {
        /*détruire le noeud*/
        Bloc* bloc = controleurMain->modeleMain->getModeleBloc()->deleteNodeBloc(noeud);
        controleurMain->modeleMain->getModeleBloc()->setBlocCheck(bloc, Qt::Checked);
    }
}

void ControleurCut::update_cut(){
    /*On met à jour tous les champs du modèle de découpe*/
    //--------------- A VOIR AVEC MICKAEL : update = mise à jour des champs du modèle (et non de l'Interface car déjà mise à jour
    // par la saisie modifiante de l'utilisateur.... Mais, comment on récupère les valeurs des champs ?
    // Doit-on modifier uniquement les champs réellement modifiés ? Si oui, comment ? Des booléens ? Une valeur transmise par le emit ?
    if(m_modeleCut != NULL)
    {
        //appliquer les modifications sur les blocs, on applique la découpe à partir du modèle
    }

}
