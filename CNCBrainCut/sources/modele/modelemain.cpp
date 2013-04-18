#include "modelemain.h"
#include "modelecut.h"
#include "bloc/nodebloc.h"
#include "bloc/modelebloc.h"

using namespace OgreCNC;
ModeleMain::ModeleMain(QObject *parent) :
    QObject(parent)
{
    m_vue = NULL;

    currentBloc = NULL;
    currentSegment = NULL;
    currentIndex = QModelIndex();

    /* l'initialisation  de l'arbre des bloc se fait maintenant, il n'y a pas de vue et de ModeleBloc pour ressevoir les signaux de creation et c'est le but
     * Ainsi le NodeBloc est initialité avec un bloc, la structure est donc valide et Ogre ne les connaient pas.
     * La creation du bloc de base de fait apres la déclaration de la vue au modele
     **/

    //initialisation de l'arbre des blocs
    m_InitialBloc = new Bloc(Ogre::Vector3(800,150,600), Ogre::Vector3(0,0,0),NULL); //bloc de la racine, n'est pas utilisable
    m_InitialBloc->setName("Bloc Facultatif inutilisable");
    m_RootTravailBlocs = new NodeBloc(m_InitialBloc); //racine
    m_RootTravailBlocs->setName("ROOT");
    m_InitialBloc->setParent(m_RootTravailBlocs);
    m_RootTravailBlocs->setInitialBloc(m_InitialBloc);

    //modele pour la gestion et l'affichage de l'arbre
    m_modeleBloc = new ModeleBloc(m_RootTravailBlocs, this);

    m_modeleCut = NULL;

}

ModeleMain::~ModeleMain(){
    delete m_RootTravailBlocs;
    //ModeleCut::~ModeleCut();
}

ModeleCut* ModeleMain::getModeleCut(){
    if(m_modeleCut == NULL)
    {
        m_modeleCut = new ModeleCut(this);
    }
    return m_modeleCut;
}
