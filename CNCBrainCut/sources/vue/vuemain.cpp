#include "vuemain.h"
#include "ui_vuemain.h"

#include "OgreWidget/ogrewidget.h"
#include "OgreWidget/OgreView.h"

#include "../controleur/controleurmain.h"
#include "../controleur/controleurbloc.h"

using namespace OgreCNC;

VueMain::VueMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VueMain)
{
    ui->setupUi(this);

    controleur = qobject_cast<ControleurMain *>(parent);
    modele = NULL;

    this->setWindowTitle("CNCBrainCut");

    m_Ogre3d =  new OgreWidget(this);
    ui->ogreLayout->addWidget(m_Ogre3d);
    ui->treeBlocs->setModel(controleur->getModeleBlocs());

    this->showNormal();
}

VueMain::~VueMain()
{
    delete ui;
}

bool VueMain::event(QEvent * e)
{
    switch(e->type())
    {
        // ...

        case QEvent::WindowActivate :
            // gained focus
            break ;

        case QEvent::WindowDeactivate :
            // lost focus
        this->showMinimized(); //reduit l'applicatoin pour
            break ;
        // ...
    default:
        break;
    } ;
    return QMainWindow::event(e) ;
}

/////***** SLOTS ******/////
void VueMain::createBloc(Bloc * bloc){
    m_Ogre3d->createBloc(bloc);
}