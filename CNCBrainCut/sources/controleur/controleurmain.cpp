#include "controleurmain.h"

#include "../modele/modelemain.h"
#include "../vue/vuemain.h"

ControleurMain::ControleurMain(QWidget *parent) :
    QWidget(parent)
{
    modele = new ModeleMain(this);
    vue = new VueMain(this);
    vue->setModele(modele);
    modele->setVue(vue);
}
