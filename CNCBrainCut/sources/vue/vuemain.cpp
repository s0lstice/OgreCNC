#include "vuemain.h"

#include "../modele/modelemain.h"
#include "../controleur/controleurmain.h"

#include "OgreWidget/vue3d.h"


VueMain::VueMain(QWidget *parent) :
    QMainWindow(parent)
{
    controleur = qobject_cast<ControleurMain *>(parent);
    modele = NULL;

    this->setWindowTitle("CNCBrainCut");

    OgreWidget * ow = new OgreWidget(this);
    ow->show();

    this->setCentralWidget(ow);
    this->showMaximized();
    //window3d->show();

}
