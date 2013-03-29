#include "controleurcut.h"
#include "../modele/modelecut.h"
#include "controleurmain.h"

using namespace OgreCNC;
ControleurCut::ControleurCut(ModeleCut* modele, QObject *parent) : QObject(parent)
{
    m_modeleCut = modele;
    controleurMain = qobject_cast<ControleurMain *>(parent);
}

void ControleurCut::update_cut(){

}
