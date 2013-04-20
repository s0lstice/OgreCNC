#include "controleurogrewidget.h"

#include "../../modele/constantesapplication.h"
#include "../../modele/bloc/bloc.h"
#include "../../modele/bloc/nodebloc.h"

#include "../vuemain.h"
using namespace OgreCNC;

ControleurOgreWidget::ControleurOgreWidget(QObject *parent) :
    QObject(parent)
{
    m_Vue3D = NULL;
    curentSegment = NULL;
    m_BBSize = 10;
    m_vue = qobject_cast<VueMain *>(parent);
}

int ControleurOgreWidget::updateDimentionBloc(Bloc * bloc)
{
    if(bloc == NULL)
    {
        qWarning() << QObject::tr("[Controleur Ogre] mise a jour de la couleur impossible, les bloc est nul");
        return 1;
    }

    if(bloc->getNodeBloc3d() == NULL)
    {
        qWarning() << QObject::tr("[Controleur Ogre] mise a jour de la couleur impossible, les bloc3D est nul");
        return 1;
    }

    Ogre::SceneNode * node = bloc->getNodeBloc3d();

    Bloc::QueryStatus status;
    if(bloc->getVisible() == Bloc::VISIBLE)
        status = Bloc::VISIBLE;
    else
        status = Bloc::HIDE;

    Ogre::Entity * cube = ((Ogre::Entity *)node->getAttachedObject( QString::number(bloc->getId()).toStdString()+"_cube"));
    cube->setQueryFlags(status);

    Ogre::SceneNode * nodeSegments = ((Ogre::SceneNode *)node->getChild(QString::number(bloc->getId()).toStdString()+"_segments"));
    Ogre::Vector3 scale = bloc->getDimension()/(node->getScale()*100);
    node->scale( scale );

    Ogre::MovableObject * segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";12_segment");
    segment->setQueryFlags(status);
    changeColorSegment(segment, constantes::SEGMENT_UNSELECTED); //deselection

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";01_segment");
    segment->setQueryFlags(status);
    changeColorSegment(segment, constantes::SEGMENT_UNSELECTED); //deselection

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";23_segment");
    segment->setQueryFlags(status);
    changeColorSegment(segment, constantes::SEGMENT_UNSELECTED); //deselection

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";30_segment");
    segment->setQueryFlags(status);
    changeColorSegment(segment, constantes::SEGMENT_UNSELECTED); //deselection

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";04_segment");
    segment->setQueryFlags(status);
    changeColorSegment(segment, constantes::SEGMENT_UNSELECTED); //deselection

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";45_segment");
    segment->setQueryFlags(status);
    changeColorSegment(segment, constantes::SEGMENT_UNSELECTED); //deselection

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";51_segment");
    segment->setQueryFlags(status);
    changeColorSegment(segment, constantes::SEGMENT_UNSELECTED); //deselection

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";37_segment");
    segment->setQueryFlags(status);
    changeColorSegment(segment, constantes::SEGMENT_UNSELECTED); //deselection

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";76_segment");
    segment->setQueryFlags(status);
    changeColorSegment(segment, constantes::SEGMENT_UNSELECTED); //deselection

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";62_segment");
    segment->setQueryFlags(status);
    changeColorSegment(segment, constantes::SEGMENT_UNSELECTED); //deselection

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";47_segment");
    segment->setQueryFlags(status);
    changeColorSegment(segment, constantes::SEGMENT_UNSELECTED); //deselection

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";56_segment");
    segment->setQueryFlags(status);
    changeColorSegment(segment, constantes::SEGMENT_UNSELECTED); //deselection

    m_Vue3D->update();

    return 0;
}

int ControleurOgreWidget::updateCouleurBloc(Bloc * bloc)
{
    if(bloc == NULL)
    {
        qWarning() << QObject::tr("[Controleur Ogre] mise a jour des dimantions impossible, les bloc est nul");
        return 1;
    }

    if(bloc->getNodeBloc3d() == NULL)
    {
        qWarning() << QObject::tr("[Controleur Ogre] mise a jour des dimantions impossible, les bloc3D est nul");
        return 1;
    }

    Ogre::Entity * blocFace = ((Ogre::Entity *)bloc->getNodeBloc3d()->getAttachedObject(QString::number(bloc->getId()).toStdString()+"_cube"));

    blocFace->setMaterialName(bloc->getFaceMatName().toStdString());

    m_Vue3D->update();
    return 0;
}

void ControleurOgreWidget::delete3DBloc(Bloc * bloc){
//    deleteSceneNode(bloc->getNodeBloc3d());
//    bloc->setNodeBloc3d(NULL);
    hide3DBloc(bloc);
    //TODO : corriger cette erreur
}

int ControleurOgreWidget::updatePositionBloc(Bloc * bloc)
{
    if(bloc == NULL)
    {
        qWarning() << QObject::tr("[Controleur Ogre] mise a jour de la position impossible, les bloc est nul");
        return 1;
    }

    if(bloc->getNodeBloc3d() == NULL)
    {
        qWarning() << QObject::tr("[Controleur Ogre] mise a jour de la position impossible, les bloc3D est nul");
        return 1;
    }

    Ogre::SceneNode * node = bloc->getNodeBloc3d();
    node->setPosition(bloc->getPosition());

    m_Vue3D->update();
    return 0;
}

void ControleurOgreWidget::hide3DBloc(Bloc * bloc)
{
    Ogre::SceneNode * node = bloc->getNodeBloc3d();
    node->setVisible(false);

    Ogre::Entity * cube = ((Ogre::Entity *)node->getAttachedObject( QString::number(bloc->getId()).toStdString()+"_cube"));
    cube->setQueryFlags(Bloc::HIDE);

    Ogre::SceneNode * nodeSegments = ((Ogre::SceneNode *)node->getChild(QString::number(bloc->getId()).toStdString()+"_segments"));
    Ogre::MovableObject * segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";01_segment");
    segment->setQueryFlags(Bloc::HIDE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";12_segment");
    segment->setQueryFlags(Bloc::HIDE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";23_segment");
    segment->setQueryFlags(Bloc::HIDE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";30_segment");
    segment->setQueryFlags(Bloc::HIDE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";04_segment");
    segment->setQueryFlags(Bloc::HIDE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";45_segment");
    segment->setQueryFlags(Bloc::HIDE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";51_segment");
    segment->setQueryFlags(Bloc::HIDE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";37_segment");
    segment->setQueryFlags(Bloc::HIDE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";76_segment");
    segment->setQueryFlags(Bloc::HIDE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";62_segment");
    segment->setQueryFlags(Bloc::HIDE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";47_segment");
    segment->setQueryFlags(Bloc::HIDE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";56_segment");
    segment->setQueryFlags(Bloc::HIDE);
}

void ControleurOgreWidget::show3DBloc(Bloc * bloc)
{
    Ogre::SceneNode * node = bloc->getNodeBloc3d();
    node->setVisible(true);

    Ogre::Entity * cube = ((Ogre::Entity *)node->getAttachedObject( QString::number(bloc->getId()).toStdString()+"_cube"));
    cube->setQueryFlags(Bloc::VISIBLE);

    Ogre::SceneNode * nodeSegments = ((Ogre::SceneNode *)node->getChild(QString::number(bloc->getId()).toStdString()+"_segments"));

    Ogre::MovableObject * segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";01_segment");
    segment->setQueryFlags(Bloc::VISIBLE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";12_segment");
    segment->setQueryFlags(Bloc::VISIBLE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";12_segment");
    segment->setQueryFlags(Bloc::VISIBLE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";23_segment");
    segment->setQueryFlags(Bloc::VISIBLE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";30_segment");
    segment->setQueryFlags(Bloc::VISIBLE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";04_segment");
    segment->setQueryFlags(Bloc::VISIBLE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";45_segment");
    segment->setQueryFlags(Bloc::VISIBLE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";51_segment");
    segment->setQueryFlags(Bloc::VISIBLE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";37_segment");
    segment->setQueryFlags(Bloc::VISIBLE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";76_segment");
    segment->setQueryFlags(Bloc::VISIBLE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";62_segment");
    segment->setQueryFlags(Bloc::VISIBLE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";47_segment");
    segment->setQueryFlags(Bloc::VISIBLE);

    segment = nodeSegments->getAttachedObject(QString::number(bloc->getId()).toStdString()+";56_segment");
    segment->setQueryFlags(Bloc::VISIBLE);
}

void ControleurOgreWidget::deleteSceneNode(Ogre::SceneNode * i_pSceneNode)
{

    if ( !i_pSceneNode )
    {
        assert( false );
        return;
    }

    // Destroy all the attached objects
    Ogre::SceneNode::ObjectIterator itObject = i_pSceneNode->getAttachedObjectIterator();

    while ( itObject.hasMoreElements() )
    {
        Ogre::MovableObject* pObject = static_cast<Ogre::MovableObject*>(itObject.getNext());
        i_pSceneNode->getCreator()->destroyMovableObject( pObject );
    }

    // Recurse to child SceneNodes
    Ogre::SceneNode::ChildNodeIterator itChild = i_pSceneNode->getChildIterator();

    while ( itChild.hasMoreElements() )
    {
        Ogre::SceneNode* pChildNode = static_cast<Ogre::SceneNode*>(itChild.getNext());
        deleteSceneNode( pChildNode );
    }

     i_pSceneNode->removeAndDestroyAllChildren();

}

int ControleurOgreWidget::create3DBloc(Bloc * bloc){
    if(bloc->getNodeBloc3d() != NULL)
    {
        qWarning() << QObject::tr("[Controleur Ogre] Création d'un boc existant impossible");
        return 1;
    }
    else{

        if( (bloc->getDimension().x <= m_BBSize) || (bloc->getDimension().z <= m_BBSize) || (bloc->getDimension().z <= m_BBSize))
        {
            qWarning() << QObject::tr("[Controleur Ogre] Création d'un boc trop petit impossible");
            return 1;
        }

        qDebug() << QObject::tr("[Controleur Ogre] Création d'un bloc 3D");

        Ogre::Vector3 position = bloc->getPosition();
        Ogre::Vector3 dimention = bloc->getDimension();

        Ogre::SceneNode * node;
        node = m_Vue3D->getSceneManager()->getRootSceneNode()->createChildSceneNode(QString::number(bloc->getId()).toStdString());

        Ogre::SceneNode * SegmentsNode = node->createChildSceneNode(QString::number(bloc->getId()).toStdString()+"_segments");

        //creation des faces du bloc
        Ogre::Entity * blocFace;
        blocFace = m_Vue3D->getSceneManager()->createEntity(QString::number(bloc->getId()).toStdString()+"_cube", "cube.mesh");
        blocFace->setMaterialName(bloc->getFaceMatName().toStdString());
        blocFace->setQueryFlags(Bloc::VISIBLE);
        node->attachObject(blocFace);

        //Creation des arretes du bloc
        //front
        //segment 01
        Ogre::ManualObject * blocContour01 = m_Vue3D->getSceneManager()->createManualObject(QString::number(bloc->getId()).toStdString()+";01_segment"); //std::to_string(m_id) :: Bug avec certain vection de MinGW : error: 'to_string' is not a member of 'std'
        beginSegment(blocContour01, bloc->getSommet0(), bloc->getSommet1(), m_BBSize, constantes::SEGMENT_UNSELECTED, bloc->getSegmentMatName().toStdString(), false);
        blocContour01->setQueryFlags(Bloc::VISIBLE);
        SegmentsNode->attachObject(blocContour01);

        //segment12
        Ogre::ManualObject * blocContour12 = m_Vue3D->getSceneManager()->createManualObject(QString::number(bloc->getId()).toStdString()+";12_segment"); //std::to_string(m_id) :: Bug avec certain vection de MinGW : error: 'to_string' is not a member of 'std'
        beginSegment(blocContour12, bloc->getSommet1(), bloc->getSommet2(), m_BBSize, constantes::SEGMENT_UNSELECTED, bloc->getSegmentMatName().toStdString(), false);
        blocContour12->setQueryFlags(Bloc::VISIBLE);
        SegmentsNode->attachObject(blocContour12);

        //segment23
        Ogre::ManualObject * blocContour23 = m_Vue3D->getSceneManager()->createManualObject(QString::number(bloc->getId()).toStdString()+";23_segment"); //std::to_string(m_id) :: Bug avec certain vection de MinGW : error: 'to_string' is not a member of 'std'
        beginSegment(blocContour23, bloc->getSommet2(), bloc->getSommet3(), m_BBSize, constantes::SEGMENT_UNSELECTED, bloc->getSegmentMatName().toStdString(), false);
        blocContour23->setQueryFlags(Bloc::VISIBLE);
        SegmentsNode->attachObject(blocContour23);

        //segment30
        Ogre::ManualObject * blocContour30 = m_Vue3D->getSceneManager()->createManualObject(QString::number(bloc->getId()).toStdString()+";30_segment"); //std::to_string(m_id) :: Bug avec certain vection de MinGW : error: 'to_string' is not a member of 'std'
        beginSegment(blocContour30, bloc->getSommet3(), bloc->getSommet0(), m_BBSize, constantes::SEGMENT_UNSELECTED, bloc->getSegmentMatName().toStdString(), false);
        blocContour30->setQueryFlags(Bloc::VISIBLE);
        SegmentsNode->attachObject(blocContour30);

        //left
        //segment04
        Ogre::ManualObject * blocContour04 = m_Vue3D->getSceneManager()->createManualObject(QString::number(bloc->getId()).toStdString()+";04_segment"); //std::to_string(m_id) :: Bug avec certain vection de MinGW : error: 'to_string' is not a member of 'std'
        beginSegment(blocContour04, bloc->getSommet0(), bloc->getSommet4(), m_BBSize, constantes::SEGMENT_UNSELECTED, bloc->getSegmentMatName().toStdString(), false);
        blocContour04->setQueryFlags(Bloc::VISIBLE);
        SegmentsNode->attachObject(blocContour04);

        //segment45
        Ogre::ManualObject * blocContour45 = m_Vue3D->getSceneManager()->createManualObject(QString::number(bloc->getId()).toStdString()+";45_segment"); //std::to_string(m_id) :: Bug avec certain vection de MinGW : error: 'to_string' is not a member of 'std'
        beginSegment(blocContour45, bloc->getSommet4(), bloc->getSommet5(), m_BBSize, constantes::SEGMENT_UNSELECTED, bloc->getSegmentMatName().toStdString(), false);
        blocContour04->setQueryFlags(Bloc::VISIBLE);
        SegmentsNode->attachObject(blocContour45);

        //segment51
        Ogre::ManualObject * blocContour51 = m_Vue3D->getSceneManager()->createManualObject(QString::number(bloc->getId()).toStdString()+";51_segment"); //std::to_string(m_id) :: Bug avec certain vection de MinGW : error: 'to_string' is not a member of 'std'
        beginSegment(blocContour51, bloc->getSommet5(), bloc->getSommet1(), m_BBSize, constantes::SEGMENT_UNSELECTED, bloc->getSegmentMatName().toStdString(), false);
        blocContour51->setQueryFlags(Bloc::VISIBLE);
        SegmentsNode->attachObject(blocContour51);

        //right
        //segment37
        Ogre::ManualObject * blocContour37 = m_Vue3D->getSceneManager()->createManualObject(QString::number(bloc->getId()).toStdString()+";37_segment"); //std::to_string(m_id) :: Bug avec certain vection de MinGW : error: 'to_string' is not a member of 'std'
        beginSegment(blocContour37, bloc->getSommet3(), bloc->getSommet7(), m_BBSize, constantes::SEGMENT_UNSELECTED, bloc->getSegmentMatName().toStdString(), false);
        blocContour37->setQueryFlags(Bloc::VISIBLE);
        SegmentsNode->attachObject(blocContour37);

        //segment76
        Ogre::ManualObject * blocContour76 = m_Vue3D->getSceneManager()->createManualObject(QString::number(bloc->getId()).toStdString()+";76_segment"); //std::to_string(m_id) :: Bug avec certain vection de MinGW : error: 'to_string' is not a member of 'std'
        beginSegment(blocContour76, bloc->getSommet7(), bloc->getSommet6(), m_BBSize, constantes::SEGMENT_UNSELECTED, bloc->getSegmentMatName().toStdString(), false);
        blocContour76->setQueryFlags(Bloc::VISIBLE);
        SegmentsNode->attachObject(blocContour76);

        //segment62
        Ogre::ManualObject * blocContour62 = m_Vue3D->getSceneManager()->createManualObject(QString::number(bloc->getId()).toStdString()+";62_segment"); //std::to_string(m_id) :: Bug avec certain vection de MinGW : error: 'to_string' is not a member of 'std'
        beginSegment(blocContour62, bloc->getSommet6(), bloc->getSommet2(), m_BBSize, constantes::SEGMENT_UNSELECTED, bloc->getSegmentMatName().toStdString(), false);
        blocContour62->setQueryFlags(Bloc::VISIBLE);
        SegmentsNode->attachObject(blocContour62);

        //back
        //segment47
        Ogre::ManualObject * blocContour47 = m_Vue3D->getSceneManager()->createManualObject(QString::number(bloc->getId()).toStdString()+";47_segment"); //std::to_string(m_id) :: Bug avec certain vection de MinGW : error: 'to_string' is not a member of 'std'
        beginSegment(blocContour47, bloc->getSommet4(), bloc->getSommet7(), m_BBSize, constantes::SEGMENT_UNSELECTED, bloc->getSegmentMatName().toStdString(), false);
        blocContour47->setQueryFlags(Bloc::VISIBLE);
        SegmentsNode->attachObject(blocContour47);

        //segment56
        Ogre::ManualObject * blocContour56 = m_Vue3D->getSceneManager()->createManualObject(QString::number(bloc->getId()).toStdString()+";56_segment"); //std::to_string(m_id) :: Bug avec certain vection de MinGW : error: 'to_string' is not a member of 'std'
        beginSegment(blocContour56, bloc->getSommet5(), bloc->getSommet6(), m_BBSize, constantes::SEGMENT_UNSELECTED, bloc->getSegmentMatName().toStdString(), false);
        blocContour56->setQueryFlags(Bloc::VISIBLE);
        SegmentsNode->attachObject(blocContour56);

        node->scale(dimention/100);
        node->setPosition(position);

        bloc->setNodeBloc3d(node);

        updateDimentionBloc(bloc); //patch probleme non trouvé
    }
}

void ControleurOgreWidget::selectBloc(Bloc * bloc){
    if(bloc == NULL)
    {
        qWarning() << QObject::tr("[Widget Ogre] sélection d'un bloc impossible, le bloc est null");
        return;
    }

    if(bloc->getNodeBloc3d() == NULL)
    {
        qWarning() << QObject::tr("[Widget Ogre] sélection d'un bloc impossible, le bloc 3D est null");
        return;
    }

    if(m_vue->getCurrentBlock() != bloc) //mise ajour de l'affichagesi les bloc sont diferants
    {
        m_vue->setCurrentBlock(bloc);

        m_Vue3D->setCameraPosition(Ogre::Vector3(bloc->getNodeBloc3d()->_getDerivedPosition() + Ogre::Vector3(0,0,500.000)));
        m_Vue3D->setCameraDirection(bloc->getPosition());
        m_Vue3D->update();
    }

}

void ControleurOgreWidget::beginSegment(Ogre::ManualObject * segment, Ogre::Vector3 debut, Ogre::Vector3 fin, int BBRayon, Ogre::ColourValue couleur, Ogre::String matName, bool isUpDate)
{
    Ogre::Vector3 min, max;

    //debut et fin du segment avec prise en compt du changement d'echel si c'est une modification
    if(debut.x <= fin.x && debut.y <= fin.y && debut.z <= fin.z)
    {
        min = debut;
        max = fin;
    }
    else
    {
        min = fin;
        max = debut;
    }

    if(isUpDate)
    {
        min = min/segment->getParentSceneNode()->getParentSceneNode()->getScale();
        max = max/segment->getParentSceneNode()->getParentSceneNode()->getScale();

        segment->beginUpdate(0);
    }
    else
        segment->begin(matName, Ogre::RenderOperation::OT_LINE_LIST);

    segment->position(min);
    segment->colour(couleur);

    segment->position(max);
    segment->colour(couleur);
    segment->end();

    //debut et fin de la bounding box

    //elimination des angles sur l'axe du segment (offset)
    if(min.x != max.x)
    {
        min.x += 2*BBRayon;
        max.x -= 2*BBRayon;
    }
    else if(min.y != max.y)
    {
        min.y += 2*BBRayon;
        max.y -= 2*BBRayon;
    }
    else if(min.z != max.z)
    {
        min.z += 2*BBRayon;
        max.z -= 2*BBRayon;
    }
    //position
    min += Ogre::Vector3(-BBRayon,-BBRayon, -BBRayon);
    max += Ogre::Vector3(+BBRayon, +BBRayon, +BBRayon);

    Ogre::SceneNode * node;

    Ogre::AxisAlignedBox BB = Ogre::AxisAlignedBox( min, max);
    segment->setBoundingBox(BB);
}

void ControleurOgreWidget::changeColorSegment(Ogre::MovableObject * segment, Ogre::ColourValue color){

    if(segment != NULL)
    {
        Bloc * bloc = emit si_blocFormOgreNode(segment->getParentSceneNode()->getParentSceneNode());
        if(bloc != NULL)
        {
            size_t found = segment->getName().find(';');//recherche le separateur
            if(found!=std::string::npos)
            {
                bool Found = true;
                Ogre::String idSegment = segment->getName().substr(found+1,2);

                //debut
                Ogre::Vector3 min;
                switch (idSegment[0]) {
                case '0':
                    min = bloc->getSommet0();
                    break;
                case '1':
                    min = bloc->getSommet1();
                    break;
                case '2':
                    min = bloc->getSommet2();
                    break;
                case '3':
                    min = bloc->getSommet3();
                    break;
                case '4':
                    min = bloc->getSommet4();
                    break;
                case '5':
                    min = bloc->getSommet5();
                    break;
                case '6':
                    min = bloc->getSommet6();
                    break;
                case '7':
                    min = bloc->getSommet7();
                    break;
                default:
                    Found = false;
                    break;
                }

                //fin
                Ogre::Vector3 max;
                switch (idSegment[1]) {
                case '0':
                    max = bloc->getSommet0();
                    break;
                case '1':
                    max = bloc->getSommet1();
                    break;
                case '2':
                    max = bloc->getSommet2();
                    break;
                case '3':
                    max = bloc->getSommet3();
                    break;
                case '4':
                    max = bloc->getSommet4();
                    break;
                case '5':
                    max = bloc->getSommet5();
                    break;
                case '6':
                    max = bloc->getSommet6();
                    break;
                case '7':
                    max = bloc->getSommet7();
                    break;
                default:
                    Found = false;
                    break;
                }
                if(Found)
                    beginSegment(((Ogre::ManualObject *) segment), min, max, m_BBSize, color, "", true);
                m_Vue3D->update();
            }
        }
    }
}

void ControleurOgreWidget::selectSegment(Ogre::ManualObject * segment)
{
    changeColorSegment(curentSegment, constantes::SEGMENT_UNSELECTED); //deselection
    curentSegment = segment;
    changeColorSegment(curentSegment, constantes::SEGMENT_SELECTED); //selection
}

void ControleurOgreWidget::selectOgreBloc(Ogre::SceneNode * node){
    if(node == NULL)
    {
        qWarning() << QObject::tr("[Widget Ogre] sélection d'un noeud impossible, le noeud est null");
        return;
    }
    Bloc * bloc = emit si_blocFormOgreNode(node);
    if(bloc != NULL)
    {
        emit si_SelectBloc(bloc);
    }
}

void ControleurOgreWidget::selectOgreSegment(Ogre::ManualObject * segment)
{
    emit si_selectSegemnt(((Ogre::ManualObject *) segment));
}
