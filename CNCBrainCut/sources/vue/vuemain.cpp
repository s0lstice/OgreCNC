#include "vuemain.h"
#include "ui_vuemain.h"

#include "OgreWidget/ogrewidget.h"

#include "../controleur/controleurmain.h"
#include "../controleur/controleurbloc.h"
#include "../modele/modelecut.h"
#include "../modele/modelemain.h"
#include "OgreWidget/controleurogrewidget.h"
#include "../modele/bloc/modelebloc.h"
#include "../modele/bloc/nodebloc.h"

using namespace OgreCNC;

VueMain::VueMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VueMain)
{
    ui->setupUi(this);
    griserVoletDecoupe();

    controleur = qobject_cast<ControleurMain *>(parent);
    modele = NULL;
    m_modeleCut = NULL;

    this->setWindowTitle("CNCBrainCut");

    m_Ogre3d =  new OgreWidget(this);
    m_ControleurOgreWidget = new ControleurOgreWidget(this);
    m_ControleurOgreWidget->setWidget(m_Ogre3d);

    ui->ogreLayout->addWidget(m_Ogre3d);

    initConnections();

    this->showNormal();
}

VueMain::~VueMain()
{
    delete ui;

    delete m_Ogre3d;
    delete m_ControleurOgreWidget;
}

void VueMain::initConnections(){
    connect(controleur, SIGNAL(si_init_cut(ModeleCut*)), this, SLOT(sl_init_cut(ModeleCut*)));
    connect(controleur, SIGNAL(si_updateOgreVue()), m_Ogre3d, SLOT(update()));
    connect(m_ControleurOgreWidget, SIGNAL(si_blocFormOgreNode(Ogre::SceneNode*)), controleur, SLOT(sl_blocFromOgreNode(Ogre::SceneNode*)));
    connect(m_ControleurOgreWidget, SIGNAL(si_SelectBloc(Bloc*)), controleur, SLOT(sl_selectBloc(Bloc*)));
    connect(m_ControleurOgreWidget, SIGNAL(si_selectSegemnt(Ogre::ManualObject*)), controleur, SLOT(sl_selectSegment(Ogre::ManualObject*)));
}

void VueMain::sl_creat3Dbloc(Bloc * bloc){
    m_ControleurOgreWidget->create3DBloc(bloc);
}

void VueMain::sl_delete3Dbloc(Bloc * bloc){
    m_ControleurOgreWidget->delete3DBloc(bloc);
}

void VueMain::sl_updateDimentionBloc(Bloc * bloc){
    m_ControleurOgreWidget->updateDimentionBloc(bloc);
}

void VueMain::sl_updatePositionBloc(Bloc * bloc){
    m_ControleurOgreWidget->updatePositionBloc(bloc);
}

void VueMain::sl_updateCouleurBloc(Bloc * bloc){
    m_ControleurOgreWidget->updateCouleurBloc(bloc);
}

//bool VueMain::event(QEvent * e)
//{
//    switch(e->type())
//    {
//        // ...

//        case QEvent::WindowActivate :
//            // gained focus
//            break ;

//        case QEvent::WindowDeactivate :
//            // lost focus
//        this->showMinimized(); //reduit l'applicatoin pour
//            break ;
//        // ...
//    default:
//        break;
//    } ;
//    return QMainWindow::event(e) ;
//}

void VueMain::griserVoletDecoupe()
{
    /*On active uniquement le bouton de lancement d'une découpe (Démarrer), tout le reste est désactivé*/

    /*On active le bouton de lancement d'une découpe*/
    ui->demarrerDecoupe_pushButton->setEnabled(true);
    /*On désactive tous les autres boutons*/
    ui->validerDecoupe_pushButton->setEnabled(false);
    ui->annulerDecoupe_pushButton->setEnabled(false);
    ui->definitionDecoupeGroupBox->setEnabled(false);
    ui->modeDecoupeDroit_GroupBox->setEnabled(false);
    ui->positionPerteGroupBox->setEnabled(false);
}

void VueMain::activerVoletDecoupe()
{
    /*On active tous les boutons sauf le bouton Démarrer qui sera grisé*/

    /*On désactive le bouton de lancement d'une découpe*/
    ui->demarrerDecoupe_pushButton->setEnabled(false);
    /*On réactive tous les autres boutons*/
    ui->validerDecoupe_pushButton->setEnabled(true);
    ui->annulerDecoupe_pushButton->setEnabled(true);
    ui->definitionDecoupeGroupBox->setEnabled(true);
    ui->modeDecoupeDroit_GroupBox->setEnabled(true);
    ui->positionPerteGroupBox->setEnabled(true);
}

/////***** SLOTS ******/////

void VueMain::sl_setTreeBlocModele(ModeleBloc * modeleBloc)
{
    ui->treeBlocs->setModel(modeleBloc);
}

void VueMain::sl_init_cut(ModeleCut *modele){
    activerVoletDecoupe();

    /*On renseigne le modéle de la vue*/
    m_modeleCut = modele;

    /*On affiche les paramètres dans l'interface*/

    /*Découpe classique ou multiple*/
    if(m_modeleCut->decoupeCM == ModeleCut::CLASSIQUE)
    {
        ui->classiqueRadioButton->setChecked(true);
    }
    else
    {
        ui->multipleRadioButton->setChecked(true);
    }

    /*Direction de la découpe*/
    if(m_modeleCut->direction == ModeleCut::X)
    {
        ui->directionX_radioButton->setChecked(true);
    }
    else
    {
        if(m_modeleCut->direction == ModeleCut::Y)
        {
            ui->directionY_radioButton->setChecked(true);
        }
        else
        {
            ui->directionZ_radioButton->setChecked(true);
        }
    }

    /*Position de la perte*/
    if(m_modeleCut->posPerte == ModeleCut::GAUCHE)
    {
        ui->perteGauche_RadioButton->setChecked(true);
    }
    else
    {
        if(m_modeleCut->posPerte == ModeleCut::CENTREE)
        {
            ui->perteCentree_RadioButton->setChecked(true);
        }
        else
        {
            ui->perteDroite_RadioButton->setChecked(true);
        }
    }

    /*Rayon de chauffe*/
    ui->rayon_chauffe_text->setText(QString::number(m_modeleCut->rayonChauffe));

    /*Distance de l'origine au point de découpe*/
    ui->distance_text->setText(QString::number(m_modeleCut->distance));

    /*Nombre de blocs*/
    ui->nbBlocs_text->setText(QString::number(m_modeleCut->nbBlocs));
}


void VueMain::sl_selectBloc(Bloc * bloc){
    m_ControleurOgreWidget->selectBloc(bloc); //mise à jour de la vue 3D
    //nom
    ui->blocNom_text->setText(bloc->getName());
    //etat
    if(bloc->getEtat() == Bloc::CHUTE)
    {
        ui->etatblocchute->setChecked(true);
        ui->etatblocuse->setChecked(false);
    }
    else
    {
        ui->etatblocchute->setChecked(false);
        ui->etatblocuse->setChecked(true);
    }

    //volume
    int volume = (bloc->getDimension().x)*(bloc->getDimension().y)*(bloc->getDimension().z);
    ui->volume->setText(QString::number(volume));

    //dimention
    ui->longeurbloc->setText(QString::number(bloc->getDimension().x));
    ui->largeurbloc->setText(QString::number(bloc->getDimension().z));
    ui->hauteurbloc->setText(QString::number(bloc->getDimension().y));
}

void VueMain::sl_selectSegment(Ogre::ManualObject * segment){
    m_ControleurOgreWidget->selectSegment(segment);
}

/////***** Gestion de l'interaction avec l'IHM *****/////
void OgreCNC::VueMain::on_demarrerDecoupe_pushButton_clicked()
{
    emit si_start_cut();
}

void OgreCNC::VueMain::on_validerDecoupe_pushButton_clicked()
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->isInUse = false;
    }

    emit si_valid_cut();
}

void OgreCNC::VueMain::on_annulerDecoupe_pushButton_clicked()
{
    bool accept = emit si_abort_cut();

    if(accept == true)
    {
        griserVoletDecoupe();
        if(m_modeleCut != NULL)
        {
            m_modeleCut->isInUse = false;
        }
    }
}

void OgreCNC::VueMain::on_classiqueRadioButton_clicked()
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->decoupeCM = ModeleCut::CLASSIQUE;

        /*On met à jour le nombre de fils à créer*/
        m_modeleCut->nbFils = 2;

        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_multipleRadioButton_clicked()
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->decoupeCM = ModeleCut::MULTIPLE;

        /*On met à jour le nombre de fils à créer*/
        if(m_modeleCut->nbBlocs == 0 && m_modeleCut->distance != 0)//découpe multiple par définition d'une distance
        {
            Ogre::Vector3 dim = m_modeleCut->m_modeleMain->currentBloc->getDimension();
            if(m_modeleCut->direction == ModeleCut::X)
            {
                if(floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[0])
                {
                    m_modeleCut->nbFils = floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                }
                else
                    m_modeleCut->nbFils = floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
            }
            else
            {
                if(m_modeleCut->direction == ModeleCut::Y)
                {
                    if(floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[1])
                    {
                        m_modeleCut->nbFils = floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                    }
                    else
                        m_modeleCut->nbFils = floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                }
                else
                {
                    if(floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[2])
                    {
                        m_modeleCut->nbFils = floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                    }
                    else
                        m_modeleCut->nbFils = floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                }
            }
        }
        else//découpe multiple par définition d'un nombre de blocs et d'une distance
        {
            if(m_modeleCut->nbBlocs != 0 && m_modeleCut->distance != 0)
            {
                Ogre::Vector3 dim = m_modeleCut->m_modeleMain->currentBloc->getDimension();
                if(m_modeleCut->direction == ModeleCut::X)
                {
                    if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[0])
                    {
                        m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                    }
                    else
                    {
                        if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[0])
                            m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                        else
                        {
                            int i = 1;
                            while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[0])
                                i++;

                            m_modeleCut->nbFils = i;
                        }
                    }
                }
                else
                {
                    if(m_modeleCut->direction == ModeleCut::Y)
                    {
                        if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[1])
                        {
                            m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                        }
                        else
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[1])
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                            else
                            {
                                int i = 1;
                                while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[1])
                                    i++;

                                m_modeleCut->nbFils = i;
                            }
                        }
                    }
                    else
                    {
                        if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[2])
                        {
                            m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                        }
                        else
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[2])
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                            else
                            {
                                int i = 1;
                                while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[2])
                                    i++;

                                m_modeleCut->nbFils = i;
                            }
                        }
                    }
                }
            }
        }

        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_directionX_radioButton_clicked()
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->direction = ModeleCut::X;

        /*On met à jour le nombre de fils à créer*/
        if(m_modeleCut->decoupeCM == ModeleCut::CLASSIQUE)
        {
            m_modeleCut->nbFils = 2;
        }
        else//cas d'une découpe multiple
        {
            if(m_modeleCut->nbBlocs == 0 && m_modeleCut->distance != 0)//découpe multiple par définition d'une distance
            {
                Ogre::Vector3 dim = m_modeleCut->m_modeleMain->currentBloc->getDimension();
                if(m_modeleCut->direction == ModeleCut::X)
                {
                    if(floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[0])
                    {
                        m_modeleCut->nbFils = floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                    }
                    else
                        m_modeleCut->nbFils = floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                }
                else
                {
                    if(m_modeleCut->direction == ModeleCut::Y)
                    {
                        if(floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[1])
                        {
                            m_modeleCut->nbFils = floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                        }
                        else
                            m_modeleCut->nbFils = floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                    }
                    else
                    {
                        if(floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[2])
                        {
                            m_modeleCut->nbFils = floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                        }
                        else
                            m_modeleCut->nbFils = floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                    }
                }
            }
            else//découpe multiple par définition d'un nombre de blocs et d'une distance
            {
                if(m_modeleCut->nbBlocs != 0 && m_modeleCut->distance != 0)
                {
                    Ogre::Vector3 dim = m_modeleCut->m_modeleMain->currentBloc->getDimension();
                    if(m_modeleCut->direction == ModeleCut::X)
                    {
                        if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[0])
                        {
                            m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                        }
                        else
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[0])
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                            else
                            {
                                int i = 1;
                                while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[0])
                                    i++;

                                m_modeleCut->nbFils = i;
                            }
                        }
                    }
                    else
                    {
                        if(m_modeleCut->direction == ModeleCut::Y)
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[1])
                            {
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                            }
                            else
                            {
                                if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[1])
                                    m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                                else
                                {
                                    int i = 1;
                                    while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[1])
                                        i++;

                                    m_modeleCut->nbFils = i;
                                }
                            }
                        }
                        else
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[2])
                            {
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                            }
                            else
                            {
                                if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[2])
                                    m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                                else
                                {
                                    int i = 1;
                                    while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[2])
                                        i++;

                                    m_modeleCut->nbFils = i;
                                }
                            }
                        }
                    }
                }
            }
        }

        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_directionY_radioButton_clicked()
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->direction = ModeleCut::Y;

        /*On met à jour le nombre de fils à créer*/
        if(m_modeleCut->decoupeCM == ModeleCut::CLASSIQUE)
        {
            m_modeleCut->nbFils = 2;
        }
        else//cas d'une découpe multiple
        {
            if(m_modeleCut->nbBlocs == 0 && m_modeleCut->distance != 0)//découpe multiple par définition d'une distance
            {
                Ogre::Vector3 dim = m_modeleCut->m_modeleMain->currentBloc->getDimension();
                if(m_modeleCut->direction == ModeleCut::X)
                {
                    if(floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[0])
                    {
                        m_modeleCut->nbFils = floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                    }
                    else
                        m_modeleCut->nbFils = floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                }
                else
                {
                    if(m_modeleCut->direction == ModeleCut::Y)
                    {
                        if(floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[1])
                        {
                            m_modeleCut->nbFils = floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                        }
                        else
                            m_modeleCut->nbFils = floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                    }
                    else
                    {
                        if(floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[2])
                        {
                            m_modeleCut->nbFils = floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                        }
                        else
                            m_modeleCut->nbFils = floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                    }
                }
            }
            else//découpe multiple par définition d'un nombre de blocs et d'une distance
            {
                if(m_modeleCut->nbBlocs != 0 && m_modeleCut->distance != 0)
                {
                    Ogre::Vector3 dim = m_modeleCut->m_modeleMain->currentBloc->getDimension();
                    if(m_modeleCut->direction == ModeleCut::X)
                    {
                        if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[0])
                        {
                            m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                        }
                        else
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[0])
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                            else
                            {
                                int i = 1;
                                while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[0])
                                    i++;

                                m_modeleCut->nbFils = i;
                            }
                        }
                    }
                    else
                    {
                        if(m_modeleCut->direction == ModeleCut::Y)
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[1])
                            {
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                            }
                            else
                            {
                                if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[1])
                                    m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                                else
                                {
                                    int i = 1;
                                    while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[1])
                                        i++;

                                    m_modeleCut->nbFils = i;
                                }
                            }
                        }
                        else
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[2])
                            {
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                            }
                            else
                            {
                                if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[2])
                                    m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                                else
                                {
                                    int i = 1;
                                    while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[2])
                                        i++;

                                    m_modeleCut->nbFils = i;
                                }
                            }
                        }
                    }
                }
            }
        }

        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_directionZ_radioButton_clicked()
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->direction = ModeleCut::Z;

        /*On met à jour le nombre de fils à créer*/
        if(m_modeleCut->decoupeCM == ModeleCut::CLASSIQUE)
        {
            m_modeleCut->nbFils = 2;
        }
        else//cas d'une découpe multiple
        {
            if(m_modeleCut->nbBlocs == 0 && m_modeleCut->distance != 0)//découpe multiple par définition d'une distance
            {
                Ogre::Vector3 dim = m_modeleCut->m_modeleMain->currentBloc->getDimension();
                if(m_modeleCut->direction == ModeleCut::X)
                {
                    if(floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[0])
                    {
                        m_modeleCut->nbFils = floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                    }
                    else
                        m_modeleCut->nbFils = floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                }
                else
                {
                    if(m_modeleCut->direction == ModeleCut::Y)
                    {
                        if(floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[1])
                        {
                            m_modeleCut->nbFils = floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                        }
                        else
                            m_modeleCut->nbFils = floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                    }
                    else
                    {
                        if(floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[2])
                        {
                            m_modeleCut->nbFils = floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                        }
                        else
                            m_modeleCut->nbFils = floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                    }
                }
            }
            else//découpe multiple par définition d'un nombre de blocs et d'une distance
            {
                if(m_modeleCut->nbBlocs != 0 && m_modeleCut->distance != 0)
                {
                    Ogre::Vector3 dim = m_modeleCut->m_modeleMain->currentBloc->getDimension();
                    if(m_modeleCut->direction == ModeleCut::X)
                    {
                        if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[0])
                        {
                            m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                        }
                        else
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[0])
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                            else
                            {
                                int i = 1;
                                while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[0])
                                    i++;

                                m_modeleCut->nbFils = i;
                            }
                        }
                    }
                    else
                    {
                        if(m_modeleCut->direction == ModeleCut::Y)
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[1])
                            {
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                            }
                            else
                            {
                                if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[1])
                                    m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                                else
                                {
                                    int i = 1;
                                    while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[1])
                                        i++;

                                    m_modeleCut->nbFils = i;
                                }
                            }
                        }
                        else
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[2])
                            {
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                            }
                            else
                            {
                                if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[2])
                                    m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                                else
                                {
                                    int i = 1;
                                    while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[2])
                                        i++;

                                    m_modeleCut->nbFils = i;
                                }
                            }
                        }
                    }
                }
            }
        }

        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_perteGauche_RadioButton_clicked()
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->posPerte = ModeleCut::GAUCHE;
        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_perteDroite_RadioButton_clicked()
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->posPerte = ModeleCut::DROITE;
        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_perteCentree_RadioButton_clicked()
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->posPerte = ModeleCut::CENTREE;
        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_distance_text_textEdited(const QString &arg1)
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->distance = (qreal)arg1.toDouble();

        /*On met à jour le nombre de fils à créer*/
        if(m_modeleCut->decoupeCM == ModeleCut::CLASSIQUE)
        {
            m_modeleCut->nbFils = 2;
        }
        else//cas d'une découpe multiple
        {
            if(m_modeleCut->nbBlocs == 0 && m_modeleCut->distance != 0)//découpe multiple par définition d'une distance
            {
                Ogre::Vector3 dim = m_modeleCut->m_modeleMain->currentBloc->getDimension();
                if(m_modeleCut->direction == ModeleCut::X)
                {
                    if(floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[0])
                    {
                        m_modeleCut->nbFils = floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                    }
                    else
                        m_modeleCut->nbFils = floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                }
                else
                {
                    if(m_modeleCut->direction == ModeleCut::Y)
                    {
                        if(floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[1])
                        {
                            m_modeleCut->nbFils = floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                        }
                        else
                            m_modeleCut->nbFils = floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                    }
                    else
                    {
                        if(floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[2])
                        {
                            m_modeleCut->nbFils = floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                        }
                        else
                            m_modeleCut->nbFils = floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                    }
                }
            }
            else//découpe multiple par définition d'un nombre de blocs et d'une distance
            {
                if(m_modeleCut->nbBlocs != 0 && m_modeleCut->distance != 0)
                {
                    Ogre::Vector3 dim = m_modeleCut->m_modeleMain->currentBloc->getDimension();
                    if(m_modeleCut->direction == ModeleCut::X)
                    {
                        if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[0])
                        {
                            m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                        }
                        else
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[0])
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                            else
                            {
                                int i = 1;
                                while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[0])
                                    i++;

                                m_modeleCut->nbFils = i;
                            }
                        }
                    }
                    else
                    {
                        if(m_modeleCut->direction == ModeleCut::Y)
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[1])
                            {
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                            }
                            else
                            {
                                if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[1])
                                    m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                                else
                                {
                                    int i = 1;
                                    while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[1])
                                        i++;

                                    m_modeleCut->nbFils = i;
                                }
                            }
                        }
                        else
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[2])
                            {
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                            }
                            else
                            {
                                if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[2])
                                    m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                                else
                                {
                                    int i = 1;
                                    while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[2])
                                        i++;

                                    m_modeleCut->nbFils = i;
                                }
                            }
                        }
                    }
                }
            }
        }

        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_nbBlocs_text_textEdited(const QString &arg1)
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->nbBlocs = arg1.toInt();

        /*On met à jour le nombre de fils à créer*/
        if(m_modeleCut->decoupeCM == ModeleCut::CLASSIQUE)
        {
            m_modeleCut->nbFils = 2;
        }
        else//cas d'une découpe multiple
        {
            if(m_modeleCut->nbBlocs == 0 && m_modeleCut->distance != 0)//découpe multiple par définition d'une distance
            {
                Ogre::Vector3 dim = m_modeleCut->m_modeleMain->currentBloc->getDimension();
                if(m_modeleCut->direction == ModeleCut::X)
                {
                    if(floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[0])
                    {
                        m_modeleCut->nbFils = floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                    }
                    else
                        m_modeleCut->nbFils = floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                }
                else
                {
                    if(m_modeleCut->direction == ModeleCut::Y)
                    {
                        if(floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[1])
                        {
                            m_modeleCut->nbFils = floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                        }
                        else
                            m_modeleCut->nbFils = floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                    }
                    else
                    {
                        if(floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[2])
                        {
                            m_modeleCut->nbFils = floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                        }
                        else
                            m_modeleCut->nbFils = floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                    }
                }
            }
            else//découpe multiple par définition d'un nombre de blocs et d'une distance
            {
                if(m_modeleCut->nbBlocs != 0 && m_modeleCut->distance != 0)
                {
                    Ogre::Vector3 dim = m_modeleCut->m_modeleMain->currentBloc->getDimension();
                    if(m_modeleCut->direction == ModeleCut::X)
                    {
                        if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[0])
                        {
                            m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                        }
                        else
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[0])
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                            else
                            {
                                int i = 1;
                                while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[0])
                                    i++;

                                m_modeleCut->nbFils = i;
                            }
                        }
                    }
                    else
                    {
                        if(m_modeleCut->direction == ModeleCut::Y)
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[1])
                            {
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                            }
                            else
                            {
                                if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[1])
                                    m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                                else
                                {
                                    int i = 1;
                                    while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[1])
                                        i++;

                                    m_modeleCut->nbFils = i;
                                }
                            }
                        }
                        else
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[2])
                            {
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                            }
                            else
                            {
                                if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[2])
                                    m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                                else
                                {
                                    int i = 1;
                                    while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[2])
                                        i++;

                                    m_modeleCut->nbFils = i;
                                }
                            }
                        }
                    }
                }
            }
        }

        emit si_update_cut();
    }
}



void OgreCNC::VueMain::on_distanceVueEclate_valueChanged(int arg1)
{
    if(ui->vueEclateCheched->checkState() == Qt::Checked)
    {
        /*On applique le nouveau déplacement*/
        emit si_vueEclate(ui->distanceVueEclate->value());
    }
    else
        emit si_vueEclate(0);
}

void OgreCNC::VueMain::on_vueEclateCheched_clicked(bool checked)
{
    if(checked == true)
        emit si_vueEclate(ui->distanceVueEclate->value());
    else
        emit si_vueEclate(0);
}

void OgreCNC::VueMain::on_blocNom_text_textEdited(const QString &arg1)
{
    emit si_newNameForCurrentBloc(arg1);
}

void OgreCNC::VueMain::on_etatblocuse_clicked(bool checked)
{
    if(checked)
        emit si_changeEtatForCurrentBloc(Bloc::UTILISE);
    else
        emit si_changeEtatForCurrentBloc(Bloc::CHUTE);
}

void OgreCNC::VueMain::on_etatblocchute_clicked(bool checked)
{
    if(!checked)
        emit si_changeEtatForCurrentBloc(Bloc::UTILISE);
    else
        emit si_changeEtatForCurrentBloc(Bloc::CHUTE);
}

void OgreCNC::VueMain::on_rayon_chauffe_text_textEdited(const QString &arg1)
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->rayonChauffe = ui->rayon_chauffe_text->text().toFloat();

        /*On met à jour le nombre de fils à créer*/
        if(m_modeleCut->decoupeCM == ModeleCut::CLASSIQUE)
        {
            m_modeleCut->nbFils = 2;
        }
        else//cas d'une découpe multiple
        {
            if(m_modeleCut->nbBlocs == 0 && m_modeleCut->distance != 0)//découpe multiple par définition d'une distance
            {
                Ogre::Vector3 dim = m_modeleCut->m_modeleMain->currentBloc->getDimension();
                if(m_modeleCut->direction == ModeleCut::X)
                {
                    if(floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[0])
                    {
                        m_modeleCut->nbFils = floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                    }
                    else
                        m_modeleCut->nbFils = floor(dim[0]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                }
                else
                {
                    if(m_modeleCut->direction == ModeleCut::Y)
                    {
                        if(floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[1])
                        {
                            m_modeleCut->nbFils = floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                        }
                        else
                            m_modeleCut->nbFils = floor(dim[1]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                    }
                    else
                    {
                        if(floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) * m_modeleCut->distance != dim[2])
                        {
                            m_modeleCut->nbFils = floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe)) + 1; //+1 pour la chute
                        }
                        else
                            m_modeleCut->nbFils = floor(dim[2]/(m_modeleCut->distance+m_modeleCut->rayonChauffe));
                    }
                }
            }
            else//découpe multiple par définition d'un nombre de blocs et d'une distance
            {
                if(m_modeleCut->nbBlocs != 0 && m_modeleCut->distance != 0)
                {
                    Ogre::Vector3 dim = m_modeleCut->m_modeleMain->currentBloc->getDimension();
                    if(m_modeleCut->direction == ModeleCut::X)
                    {
                        if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[0])
                        {
                            m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                        }
                        else
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[0])
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                            else
                            {
                                int i = 1;
                                while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[0])
                                    i++;

                                m_modeleCut->nbFils = i;
                            }
                        }
                    }
                    else
                    {
                        if(m_modeleCut->direction == ModeleCut::Y)
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[1])
                            {
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                            }
                            else
                            {
                                if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[1])
                                    m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                                else
                                {
                                    int i = 1;
                                    while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[1])
                                        i++;

                                    m_modeleCut->nbFils = i;
                                }
                            }
                        }
                        else
                        {
                            if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs == dim[2])
                            {
                                m_modeleCut->nbFils = m_modeleCut->nbBlocs;
                            }
                            else
                            {
                                if((m_modeleCut->distance+m_modeleCut->rayonChauffe) * m_modeleCut->nbBlocs < dim[2])
                                    m_modeleCut->nbFils = m_modeleCut->nbBlocs + 1;//+1 pour la chute
                                else
                                {
                                    int i = 1;
                                    while((m_modeleCut->distance+m_modeleCut->rayonChauffe) * i < dim[2])
                                        i++;

                                    m_modeleCut->nbFils = i;
                                }
                            }
                        }
                    }
                }
            }
        }

        emit si_update_cut();
    }
}
