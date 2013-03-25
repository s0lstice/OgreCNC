#include "ogrewidget.h"

#include <QtGui/QX11Info>
#include <QGLWidget>
#include <iostream>

#include "../../modele/bloc/bloc.h"

using namespace OgreCNC;
using namespace std;

const QPoint     OgreWidget::invalidMousePoint(-1,-1);
const Ogre::Real OgreWidget::turboModifier(10);

OgreWidget::OgreWidget(QWidget *parent)
:QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
ogreRoot(0), ogreSceneManager(0), ogreRenderWindow(0), ogreViewport(0),
ogreCamera(0), oldPos(invalidMousePoint)
{
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_PaintOnScreen);
    setFocusPolicy(Qt::ClickFocus);
    setMinimumSize(800, 600);

    cameraLookAt = Ogre::Vector3(0,0,0);
    cameraPosition  = Ogre::Vector3(300.000,300.000,300.000);
    cameraDistanceBloc  = Ogre::Vector3(300.000,300.000,300.000);
    curentBlock = NULL;
}

OgreWidget::~OgreWidget()
{
    if(ogreRenderWindow)
    {
        ogreRenderWindow->removeAllViewports();
    }
    
    if(ogreRoot)
    {
        ogreRoot->detachRenderTarget(ogreRenderWindow);
        
        if(ogreSceneManager)
        {
            ogreRoot->destroySceneManager(ogreSceneManager);
        }
    }
    
    delete ogreRoot;
}

void OgreWidget::setBackgroundColor(QColor c)
{
    if(ogreViewport)
    {
        Ogre::ColourValue ogreColour;
        ogreColour.setAsARGB(c.rgba());
        ogreViewport->setBackgroundColour(ogreColour);
    }
}

void OgreWidget::upDateCamera()
{
    ogreCamera->setPosition(cameraPosition);
    ogreCamera->lookAt(cameraLookAt);
    update();
    emit cameraPositionChanged(cameraPosition);
}

void OgreWidget::setCameraPosition(const Ogre::Vector3 &pos){
    cameraPosition = pos;
    upDateCamera();
}

void OgreWidget::setCameraDirection(const Ogre::Vector3 &pos){
    cameraLookAt = pos;
    upDateCamera();
}

void OgreWidget::keyPressEvent(QKeyEvent *e)
{
	static QMap<int, Ogre::Vector3> keyCoordModificationMapping;
	static bool mappingInitialised = false;
	
	if(!mappingInitialised)
	{
        keyCoordModificationMapping[Qt::Key_Z] 		  = Ogre::Vector3( 0, 0,-10);
        keyCoordModificationMapping[Qt::Key_S] 		  = Ogre::Vector3( 0, 0, 10);
        keyCoordModificationMapping[Qt::Key_Q] 		  = Ogre::Vector3(-10, 0, 0);
        keyCoordModificationMapping[Qt::Key_D] 		  = Ogre::Vector3( 10, 0, 0);
        keyCoordModificationMapping[Qt::Key_PageUp]   = Ogre::Vector3( 0, 10, 0);
        keyCoordModificationMapping[Qt::Key_PageDown] = Ogre::Vector3( 0,-10, 0);
		
		mappingInitialised = true;
	}
	
    QMap<int, Ogre::Vector3>::iterator keyPressed = keyCoordModificationMapping.find(e->key());
	if(keyPressed != keyCoordModificationMapping.end() && ogreCamera)
	{
		const Ogre::Vector3 &actualCamPos = ogreCamera->getPosition();
		setCameraPosition(actualCamPos + keyPressed.value());
		
		e->accept();
	}
    else
    {
        e->ignore();
    }
}

void OgreWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(e->buttons().testFlag(Qt::LeftButton))
    {
        // initialisation de la requête
        Ogre::RaySceneQuery *raySceneQuery =
        ogreSceneManager->createRayQuery(Ogre::Ray());
        // initialisation du rayon de mesure
        Ogre::Ray mouseRay = ogreCamera->getCameraToViewportRay(
        e->posF().x()/(float)width(),
        e->posF().y()/(float)height());
        raySceneQuery->setRay(mouseRay);
        raySceneQuery->setSortByDistance(true);

        // exécution de la requête
        Ogre::RaySceneQueryResult &result = raySceneQuery->execute();

        // parcours des résultats, récupération du premier « MovableObject »
        Ogre::RaySceneQueryResult::iterator itr;

        if(itr == result.begin())
            cout << "[Ogre] pas d'objet " << endl;

        for (itr = result.begin();itr!=result.end();itr++)
        {
            if(itr->movable)
            {
                cout << "[Ogre] Objet : " << itr->movable->getName() << endl;
                selectNode(itr->movable->getParentSceneNode());
            }
            else{
                cout << "[Ogre] Rien a prender" << endl;
            }
        }
        
        update();
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

void OgreWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons().testFlag(Qt::LeftButton) && oldPos != invalidMousePoint)
    {
        const QPoint &pos = e->pos();
        Ogre::Real deltaX = pos.x() - oldPos.x();
        Ogre::Real deltaY = pos.y() - oldPos.y();
        
        if(e->modifiers().testFlag(Qt::ControlModifier))
        {
            deltaX *= turboModifier;
            deltaY *= turboModifier;
        }
        
        Ogre::Vector3 camTranslation(deltaX, deltaY, 0);
        const Ogre::Vector3 &actualCamPos = ogreCamera->getPosition();
        setCameraPosition(actualCamPos + camTranslation);
        
        oldPos = pos;
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

void OgreWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons().testFlag(Qt::LeftButton))
    {
        oldPos = e->pos();
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

void OgreWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(!e->buttons().testFlag(Qt::LeftButton))
    {
        oldPos = QPoint(invalidMousePoint);
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

void OgreWidget::moveEvent(QMoveEvent *e)
{
    QWidget::moveEvent(e);
    
    if(e->isAccepted() && ogreRenderWindow)
    {
        ogreRenderWindow->windowMovedOrResized();
        update();
    }
}

void OgreWidget::paintEvent(QPaintEvent *e)
{
    ogreRoot->_fireFrameStarted();
        ogreRenderWindow->update();
    ogreRoot->_fireFrameEnded();
    
    e->accept();
}

void OgreWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    
    if(e->isAccepted())
    {
        const QSize &newSize = e->size();
        if(ogreRenderWindow)
        {
            ogreRenderWindow->resize(newSize.width(), newSize.height());
            ogreRenderWindow->windowMovedOrResized();
        }
        if(ogreCamera)
        {
            Ogre::Real aspectRatio = Ogre::Real(newSize.width()) / Ogre::Real(newSize.height());
            ogreCamera->setAspectRatio(aspectRatio);
        }
        update();
    }
}

void OgreWidget::showEvent(QShowEvent *e)
{
    if(!ogreRoot)
    {
        initOgreSystem();
    }
    
    QWidget::showEvent(e);
}

void OgreWidget::wheelEvent(QWheelEvent *e)
{
    Ogre::Vector3 zTranslation(0,0, -e->delta() / 60);
    
    if(e->modifiers().testFlag(Qt::ControlModifier))
    {
        zTranslation.z *= turboModifier;
    }

    const Ogre::Vector3 &actualCamPos = ogreCamera->getPosition();
    setCameraPosition(actualCamPos + zTranslation);
    
    e->accept();
}

void OgreWidget::initOgreSystem()
{
    ogreRoot = new Ogre::Root();
    
    Ogre::RenderSystem *renderSystem = ogreRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
    ogreRoot->setRenderSystem(renderSystem);
    ogreRoot->initialise(false);
    
    ogreSceneManager = ogreRoot->createSceneManager(Ogre::ST_GENERIC);
    
    Ogre::NameValuePairList viewConfig;
    Ogre::String widgetHandle;

#ifdef Q_WS_WIN
    widgetHandle = Ogre::StringConverter::toString((size_t)((HWND)winId()));
#else
    QWidget *q_parent = dynamic_cast <QWidget *> (parent());
    QX11Info xInfo = x11Info();

    widgetHandle = Ogre::StringConverter::toString ((unsigned long)xInfo.display()) +
        ":" + Ogre::StringConverter::toString ((unsigned int)xInfo.screen()) +
        ":" + Ogre::StringConverter::toString ((unsigned long)q_parent->winId());
#endif
    viewConfig["externalWindowHandle"] = widgetHandle;
    ogreRenderWindow = ogreRoot->createRenderWindow("Ogre rendering window",
		width(), height(), false, &viewConfig);
    
    ogreCamera = ogreSceneManager->createCamera("myCamera");
    ogreCamera->setPosition(cameraPosition);
    ogreCamera->lookAt(cameraLookAt);
    emit cameraPositionChanged(cameraPosition);
    
    ogreViewport = ogreRenderWindow->addViewport(ogreCamera);
    ogreViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
    ogreCamera->setAspectRatio(Ogre::Real(width()) / Ogre::Real(height()));
	
	setupNLoadResources();
	createScene();
}

void OgreWidget::setupNLoadResources()
{
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load("resources.cfg");

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
			// OS X does not set the working directory relative to the app,
			// In order to make things portable on OS X we need to provide
			// the loading with it's own bundle path location
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				Ogre::String(macBundlePath() + "/" + archName), typeName, secName);
#else
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
#endif
		}
	}
	
	// Initialise, parse scripts etc
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void OgreWidget::createScene()
{
	ogreSceneManager->setAmbientLight(Ogre::ColourValue(1,1,1));

    ogreSceneManager->setSkyDome(true, "CloudySky", 5, 8);

}

void OgreWidget::selectBloc(Bloc * bloc){
    cameraLookAt = bloc->getPosition();
    cameraPosition = Ogre::Vector3(cameraLookAt + cameraDistanceBloc);

    curentBlock = bloc;
    curentNode = bloc->getNodeBloc3d();

    ogreCamera->setPosition(cameraPosition);
    ogreCamera->lookAt(cameraLookAt);
    emit cameraPositionChanged(cameraPosition);
}

void OgreWidget::selectNode(Ogre::SceneNode * node){
    cameraLookAt = node->getPosition();
    cameraPosition = Ogre::Vector3(cameraLookAt + cameraDistanceBloc);

    curentBlock = NULL;
    curentNode = node;

    ogreCamera->setPosition(cameraPosition);
    ogreCamera->lookAt(cameraLookAt);
    emit cameraPositionChanged(cameraPosition);
}

void OgreWidget::createBloc(Bloc * bloc){
    Ogre::Vector3 position = bloc->getPosition();
    Ogre::Vector3 dimention = bloc->getDimention();
    Ogre::Entity * blocFace = bloc->getBlocFace3d();
    Ogre::SceneNode * node = bloc->getNodeBloc3d();
    Ogre::ManualObject * blocContour = bloc->getBlocContour3d();

    if(blocFace == NULL){
        blocFace = ogreSceneManager->createEntity(QString::number(bloc->getId()).toStdString()+"_cube", "cube.mesh");
        blocFace->setMaterialName(bloc->getFaceMatName().toStdString());
        bloc->setBlocFace3d(blocFace);
    }

    if(blocContour==NULL){
        Ogre::Vector3 sommet0 = Ogre::Vector3(- 100/2, + 100/2, + 100/2);
        Ogre::Vector3 sommet1 = Ogre::Vector3(- 100/2, - 100/2, + 100/2);
        Ogre::Vector3 sommet2 = Ogre::Vector3(+ 100/2, - 100/2, + 100/2);
        Ogre::Vector3 sommet3 = Ogre::Vector3(+ 100/2, + 100/2, + 100/2);
        Ogre::Vector3 sommet4 = Ogre::Vector3(- 100/2, + 100/2, - 100/2);
        Ogre::Vector3 sommet5 = Ogre::Vector3(- 100/2, - 100/2, - 100/2);
        Ogre::Vector3 sommet6 = Ogre::Vector3(+ 100/2, - 100/2, - 100/2);
        Ogre::Vector3 sommet7 = Ogre::Vector3(+ 100/2, + 100/2, - 100/2);


        blocContour = new Ogre::ManualObject(QString::number(bloc->getId()).toStdString()+"_contour"); //std::to_string(m_id) :: Bug avec certain vection de MinGW : error: 'to_string' is not a member of 'std'

        blocContour->begin(bloc->getSegmentMatName().toStdString(), Ogre::RenderOperation::OT_LINE_LIST);

        //front
        blocContour->position(sommet0);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        blocContour->position(sommet1);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(1.0, 1.0);

        blocContour->position(sommet1);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(1.0, 1.0);

        blocContour->position(sommet2);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(1.0, 0.0);

        blocContour->position(sommet2);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(1.0, 0.0);

        blocContour->position(sommet3);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 0.0);

        blocContour->position(sommet3);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 0.0);

        blocContour->position(sommet0);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 0.0);

        //left
        blocContour->position(sommet0);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        blocContour->position(sommet4);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        blocContour->position(sommet4);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        blocContour->position(sommet5);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        blocContour->position(sommet5);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        blocContour->position(sommet1);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        //right
        blocContour->position(sommet3);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        blocContour->position(sommet7);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        blocContour->position(sommet7);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        blocContour->position(sommet6);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        blocContour->position(sommet6);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        blocContour->position(sommet2);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        //back
        blocContour->position(sommet4);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        blocContour->position(sommet7);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        blocContour->position(sommet5);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        blocContour->position(sommet6);
        blocContour->colour(bloc->getCouleurSegment());
        blocContour->textureCoord(0.0, 1.0);

        blocContour->end();
        bloc->setBlocContour3d(blocContour);
    }

    if(node == NULL){
        node = ogreSceneManager->getRootSceneNode()->createChildSceneNode(QString::number(bloc->getId()).toStdString()+"_node");

        node->attachObject(blocFace);
        node->attachObject(blocContour);

        node->scale(dimention);
        node->setPosition(position);

        bloc->setNodeBloc3d(node);
    }

    if(bloc->getVisibilite() == Qt::Checked)
        node->setVisible(true);
    else
        node->setVisible(false);
}
