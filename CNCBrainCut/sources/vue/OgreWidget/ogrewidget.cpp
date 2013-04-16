#include "ogrewidget.h"

#include <QtGui/QX11Info>
#include <QGLWidget>
#include <iostream>

#include "../../modele/bloc/bloc.h"

using namespace OgreCNC;
using namespace std;

const QPoint     OgreWidget::invalidMousePoint(-1,-1);

OgreWidget::OgreWidget(QWidget *parent)
:QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
ogreRoot(0), ogreSceneManager(0), ogreRenderWindow(0), ogreViewport(0),
ogreCamera(0), oldPos(invalidMousePoint)
{
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_PaintOnScreen);
    setFocusPolicy(Qt::ClickFocus);
    setMinimumSize(800, 600);

    initCameraLookAt = Ogre::Vector3(0,0,0);
    initCameraPosition  = Ogre::Vector3(0,0,500.000);

    curentNode = NULL;
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

void OgreWidget::setCameraPosition(const Ogre::Vector3 &pos){
    ogreCamera->setPosition(pos);
    update();
    emit cameraPositionChanged(pos);
}

void OgreWidget::setCameraDirection(const Ogre::Vector3 &pos){
    ogreCamera->lookAt(pos);
    update();
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
    e->ignore();
}

void OgreWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons().testFlag(Qt::LeftButton) && oldPos != invalidMousePoint)
    {
        const QPoint &pos = e->pos();
        Ogre::Real deltaX = pos.x() - oldPos.x();
        Ogre::Real deltaY = pos.y() - oldPos.y();
              
        Ogre::Real dist = (ogreCamera->getPosition() - curentNode->_getDerivedPosition()).length();

        ogreCamera->setPosition(curentNode->_getDerivedPosition());
        ogreCamera->yaw(Ogre::Degree(-deltaX * 0.25f));
        ogreCamera->pitch(Ogre::Degree(-deltaY * 0.25f));
        ogreCamera->moveRelative(Ogre::Vector3(0, 0, dist));

        update();
        emit cameraPositionChanged(ogreCamera->getPosition());

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
    if(e->buttons().testFlag(Qt::RightButton))
    {
        selectionObjet(e);
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
    Ogre::Real dist = (ogreCamera->getPosition() - curentNode->_getDerivedPosition()).length();

    ogreCamera->moveRelative(Ogre::Vector3(0, 0, -e->delta() * 0.004f * dist));

    update();
    emit cameraPositionChanged(ogreCamera->getPosition());

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
    ogreCamera->setPosition(initCameraPosition);
    ogreCamera->lookAt(initCameraLookAt);
    emit cameraPositionChanged(ogreCamera->getPosition());
    
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
    ogreViewport->setBackgroundColour(Ogre::ColourValue(0.5,0.5,0.5));
}

Ogre::MovableObject * OgreWidget::picking(QMouseEvent *e){
    // initialisation de la requête
    Ogre::RaySceneQuery *raySceneQuery = ogreSceneManager->createRayQuery(Ogre::Ray());

    // initialisation du rayon de mesure
    Ogre::Ray mouseRay = ogreCamera->getCameraToViewportRay(
    e->posF().x()/(float)width(),
    e->posF().y()/(float)height());
    raySceneQuery->setRay(mouseRay);
    raySceneQuery->setSortByDistance(true);

    // exécution de la requête
    Ogre::RaySceneQueryResult &result = raySceneQuery->execute();

    // parcours des résultats, récupération du premier « MovableObject »
    Ogre::RaySceneQueryResult::iterator itr = result.begin();

    if(itr != result.end())
    {
        while(itr->movable ==NULL && itr!=result.end())
            itr++;

        if(itr->movable)
        {
            cout << "[Ogre] Objet : " << itr->movable->getName() << endl;
            return itr->movable;
        }
        else{
            cout << "[Ogre] pas d'objet " << endl;
            return NULL;
        }
    }

    return NULL;
}

void OgreWidget::selectionObjet(QMouseEvent *e){
    Ogre::MovableObject * objet = picking(e);
    if(objet != NULL)
        if(objet->getName().find("_segment") != std::string::npos)
            emit si_selectionSegment(((Ogre::ManualObject *)objet));
        else
            emit si_selectionObjet(objet->getParentSceneNode());
}

void OgreWidget::setCurentNode(Ogre::SceneNode * node)
{
    curentNode = node;
}
