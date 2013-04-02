#include "vuemain.h"
#include "ui_vuemain.h"

#include "OgreWidget/ogrewidget.h"

#include "../controleur/controleurmain.h"
#include "../controleur/controleurbloc.h"
#include "../modele/modelecut.h"

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

    initConnections();

    this->showNormal();
}

VueMain::~VueMain()
{
    delete ui;
}

void VueMain::initConnections(){
    //select
    connect(m_Ogre3d, SIGNAL(si_select(int)), this, SIGNAL(si_select(int)));

    connect(controleur, SIGNAL(si_init_cut(ModeleCut*)), this, SLOT(sl_init_cut(ModeleCut*)));
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
void VueMain::sl_createBloc(Bloc * bloc){
    m_Ogre3d->createBloc(bloc);
}

void VueMain::sl_init_cut(ModeleCut *modele){
    /*On désactive le bouton de lancement d'une découpe*/
    ui->demarrerDecoupe_pushButton->setEnabled(false);
    /*On réactive tous les autres boutons*/
    ui->validerDecoupe_pushButton->setEnabled(true);
    ui->annulerDecoupe_pushButton->setEnabled(true);
    ui->definitionDecoupeGroupBox->setEnabled(true);
    ui->modeDecoupeDroit_GroupBox->setEnabled(true);
    ui->modeDecoupeGauche_GroupBox->setEnabled(true);
    ui->positionPerteGroupBox->setEnabled(true);

    /*On renseigne le modéle de la vue*/
    m_modeleCut = modele;

    /*On affiche les paramètres dans l'interface*/

    /*Découpe horizontale ou verticale*/
    if(m_modeleCut->decoupeHV == ModeleCut::HORIZONTALE)
    {
        ui->horizontaleRadioButton->setChecked(true);
    }
    else
    {
        ui->verticaleRadioButton->setChecked(true);
    }

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

    /*Origine de la découpe*/
    ui->origineX_text->setText(QString::number(m_modeleCut->origineDecoupe[0]));
    ui->origineY_text->setText(QString::number(m_modeleCut->origineDecoupe[1]));
    ui->origineZ_text->setText(QString::number(m_modeleCut->origineDecoupe[2]));

    /*Distance de l'origine au point de découpe*/
    ui->distance_text->setText(QString::number(m_modeleCut->distance));

    /*Nombre de blocs*/
    ui->nbBlocs_text->setText(QString::number(m_modeleCut->nbBlocs));
}


void VueMain::sl_selectBloc(Bloc * bloc){
    m_Ogre3d->selectBloc(bloc);
}

/////***** Gestion de l'interaction avec l'IHM *****/////
void OgreCNC::VueMain::on_demarrerDecoupe_pushButton_clicked()
{
    emit si_start_cut();
}

void OgreCNC::VueMain::on_validerDecoupe_pushButton_clicked()
{
    emit si_valid_cut();
}

void OgreCNC::VueMain::on_annulerDecoupe_pushButton_clicked()
{
    emit si_abort_cut();
}

void OgreCNC::VueMain::on_horizontaleRadioButton_clicked()
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->decoupeHV = ModeleCut::HORIZONTALE;
        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_verticaleRadioButton_clicked()
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->decoupeHV = ModeleCut::VERTICALE;
        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_classiqueRadioButton_clicked()
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->decoupeCM = ModeleCut::CLASSIQUE;
        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_multipleRadioButton_clicked()
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->decoupeCM = ModeleCut::MULTIPLE;
        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_directionX_radioButton_clicked()
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->direction = ModeleCut::X;
        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_directionY_radioButton_clicked()
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->direction = ModeleCut::Y;
        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_directionZ_radioButton_clicked()
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->direction = ModeleCut::Z;
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

void OgreCNC::VueMain::on_origineX_text_textEdited(const QString &arg1)
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->origineDecoupe[0] = (qreal)arg1.toDouble();
        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_origineY_text_textEdited(const QString &arg1)
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->origineDecoupe[1] = (qreal)arg1.toDouble();
        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_origineZ_text_textEdited(const QString &arg1)
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->origineDecoupe[2] = (qreal)arg1.toDouble();
        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_distance_text_textEdited(const QString &arg1)
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->distance = (qreal)arg1.toDouble();
        emit si_update_cut();
    }
}

void OgreCNC::VueMain::on_nbBlocs_text_textEdited(const QString &arg1)
{
    if(m_modeleCut != NULL)
    {
        m_modeleCut->nbBlocs = arg1.toInt();
        emit si_update_cut();
    }
}
