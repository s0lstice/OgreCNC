#include "controleurcut.h"
#include "../modele/modelecut.h"
#include "controleurmain.h"
//#include "ui_vuemain.h"

using namespace OgreCNC;
ControleurCut::ControleurCut(ModeleCut* modele, QObject *parent) : QObject(parent)
{
    m_modeleCut = modele;
    controleurMain = qobject_cast<ControleurMain *>(parent);
}

void ControleurCut::update_cut(){
    /*On met à jour tous les champs du modèle de découpe*/
    //--------------- A VOIR AVEC MICKAEL : update = mise à jour des champs du modèle (et non de l'Interface car déjà mise à jour
    // par la saisie modifiante de l'utilisateur.... Mais, comment on récupère les valeurs des champs ?
    // Doit-on modifier uniquement les champs réellement modifiés ? Si oui, comment ? Des booléens ? Une valeur transmise par le emit ?
    if(m_modeleCut != NULL)
    {
        /* COMMENT ON ACCEDE A L'ui ???
        m_modeleCut->decoupeCM = ;
        m_modeleCut->decoupeHV = ;
        m_modeleCut->direction = ;
        m_modeleCut->distance = ui->
        m_modeleCut->origineDecoupe[0] = ;
        m_modeleCut->origineDecoupe[1] = ;
        m_modeleCut->origineDecoupe[2] = ;
        m_modeleCut->posPerte = ;
        m_modeleCut->nbBlocs = ;
        */
    }

}
