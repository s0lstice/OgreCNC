#include "controleurbloc.h"

#include <QObject>
#include <QDebug>
#include <QString>

#include <Ogre.h>

#include "../modele/bloc/nodebloc.h"
#include "../modele/bloc/bloc.h"
#include "controleurmain.h"
#include "../modele/bloc/modelebloc.h"
#include "../modele/modelemain.h"
#include "../modele/constantesapplication.h"

using namespace OgreCNC;

ControleurBloc::ControleurBloc(QObject *parent) : QObject(parent)
{
    m_controleur = qobject_cast<ControleurMain *>(parent);
    m_modeleBloc = NULL;
}

void ControleurBloc::setModeleBloc(ModeleBloc * modeleBloc)
{
    m_modeleBloc = modeleBloc;
}

void ControleurBloc::selectSegment(Ogre::ManualObject * segment)
{
    m_controleur->modeleMain->currentSegment = segment;

    emit si_selectSegment(m_controleur->modeleMain->currentSegment); //indique la selection d'un segment

    //selctionne le bloc si le segemnt ne fait pas partie du bloc courent
    if(m_controleur->modeleMain->currentSegment->getParentSceneNode()->getParentSceneNode() != m_controleur->modeleMain->currentBloc->getNodeBloc3d())
    {
        selectBloc(m_modeleBloc->blocFromOgreNode(m_controleur->modeleMain->currentSegment->getParentSceneNode()->getParentSceneNode()));
    }
}

void ControleurBloc::selectBloc(Bloc *bloc,const QModelIndex & index){
    if(m_modeleBloc == NULL)
    {
        qWarning() << QObject::tr("[Controleur Bloc] il n'y a pas de controleur de bloc, l'opperation ne peut etre autorisé");
        return;
    }

    if(m_controleur->modeleMain->currentBloc  != bloc)
    {

        m_modeleBloc->setBlocCheck(bloc, Qt::Checked);
        m_controleur->modeleMain->currentIndex = index;

        //deslectione du segment courent s'il n'est pas sur le bloc selectionne
        if(m_controleur->modeleMain->currentSegment != NULL)
            if(m_modeleBloc->blocFromOgreNode(m_controleur->modeleMain->currentSegment->getParentSceneNode()->getParentSceneNode()) != m_controleur->modeleMain->currentBloc)
            {
                m_controleur->modeleMain->currentSegment = NULL;
                emit si_selectSegment(m_controleur->modeleMain->currentSegment);
            }
    }
}

//Modif Mel
/*Cette fonction éloigne tous les blocs d'une distance "eloignement" sur l'axe donné par positionRoot->positionBloc
* Le bloc racine n'est pas déplacé.
*/
void ControleurBloc::appliquerVueEclatee(double eloignement, NodeBloc* node){

    if(eloignement != 0)
    {
        //eloignement = eloignement/100;

        int i;
        Bloc* bloc;
        Ogre::Vector3 positionBloc;
        Ogre::Vector3 nouvellePosition;
        Ogre::SceneNode* nodeBloc;

        if(node == NULL)
        {
            node = m_modeleBloc->getRootNode();
        }

        //Récupération des fils du noeud bloc
        QVector<Bloc*> * listeFils = node->getListeFils();

        //On parcourt tous les fils du noeud
        for(i = 0; i < listeFils->count(); i++)
        {
            bloc = listeFils->data()[i];
            positionBloc = bloc->getPosition();
            nodeBloc = bloc->getNodeBloc3d();

            switch(bloc->getType())
            {
                case Bloc::BLOC:
                    //On applique le changement de position sur le noeud feuille
                    nouvellePosition = ControleurBloc::calculerConstanteVueEclatee(bloc, eloignement);
                    nouvellePosition[0] = nouvellePosition[0] + positionBloc[0];
                    nouvellePosition[1] = nouvellePosition[1] + positionBloc[1];
                    nouvellePosition[2] = nouvellePosition[2] + positionBloc[2];
                    bloc->setPositionVueEclatee(positionBloc); //on enregistre la position avant éclatement
                    nodeBloc->setPosition(nouvellePosition[0],nouvellePosition[1],nouvellePosition[2]);
                    break;
                case Bloc::NODE:
                    //On applique le changement de position sur le noeud bloc
                    nouvellePosition = ControleurBloc::calculerConstanteVueEclatee(bloc, eloignement);
                    nouvellePosition[0] = nouvellePosition[0] + positionBloc[0];
                    nouvellePosition[1] = nouvellePosition[1] + positionBloc[1];
                    nouvellePosition[2] = nouvellePosition[2] + positionBloc[2];
                    bloc->setPositionVueEclatee(positionBloc); //on enregistre la position avant éclatement
                    nodeBloc->setPosition(nouvellePosition[0],nouvellePosition[1],nouvellePosition[2]);
                    //On parcourt ses fils
                    ControleurBloc::appliquerVueEclatee(eloignement, (NodeBloc*)bloc);
            }
        }
    }
    else
    {
        if(node == NULL)
        {
            node = m_modeleBloc->getRootNode();
        }

        /*On replace tous les blocs*/
        m_controleur->replacerBlocs(node);
    }
}

//Rappel : on déplace par rapport au centre de gravité de la racine
Ogre::Vector3 ControleurBloc::calculerConstanteVueEclatee(Bloc* noeudAdeplacer, double eloignement){

    //En vue éclatée, la racine reste à sa position initiale
    if( (noeudAdeplacer == m_modeleBloc->getRootNode()) || (noeudAdeplacer->getPosition() == m_modeleBloc->getRootNode()->getPosition()) )
    {
        return( Ogre::Vector3(0,0,0) );
    }

    Ogre::Vector3 positionRoot = m_modeleBloc->getRootNode()->getPosition();
    Ogre::Vector3 positionNoeud = noeudAdeplacer->getPosition();

    double X = positionNoeud[0]-positionRoot[0];
    double Y = positionNoeud[1]-positionRoot[1];
    double Z = positionNoeud[2]-positionRoot[2];

    double norme = sqrt(  (positionNoeud[0]-positionRoot[0])*(positionNoeud[0]-positionRoot[0])
                        + (positionNoeud[1]-positionRoot[1])*(positionNoeud[1]-positionRoot[1])
                        + (positionNoeud[2]-positionRoot[2])*(positionNoeud[2]-positionRoot[2])
                       );

    double normalisationX = X/norme;
    double normalisationY = Y/norme;
    double normalisationZ = Z/norme;

    norme = norme + eloignement;

    X = X + norme * normalisationX;
    Y = Y + norme * normalisationY;
    Z = Z + norme * normalisationZ;

    return( Ogre::Vector3(X,Y,Z) );
}

void ControleurBloc::changeNameOfCurrentBloc(const QString &name)
{
    m_controleur->modeleMain->currentBloc->setName(name);
}

void ControleurBloc::deleteCurrentNodeBloc(){
    if(m_controleur->modeleMain->currentBloc->getType() == Bloc::NODE)
        m_controleur->modeleMain->getModeleBloc()->deleteNodeBloc(((NodeBloc*) m_controleur->modeleMain->currentBloc));
}
