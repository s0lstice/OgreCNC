#ifndef OGREWIDGET_H
#define OGREWIDGET_H

#include <QtGui>
#include <Ogre.h>
#include <QGLWidget>

namespace OgreCNC {

    class Bloc;

    class OgreWidget : public QGLWidget
    {
        Q_OBJECT

    public:
        OgreWidget(QWidget *parent = 0);
        ~OgreWidget();

        inline Ogre::SceneManager *getSceneManager(){
            return ogreSceneManager;
        }

        inline Ogre::Camera *getCamera(){
            return ogreCamera;
        }

        void selectBloc(Bloc * bloc);
        void selectNode(Ogre::SceneNode * node);
        void createBloc(Bloc * bloc);
        void setCurentNode(Ogre::SceneNode * node);

    public slots:
        void setBackgroundColor(QColor c);
        void setCameraPosition(const Ogre::Vector3 &pos);
        void setCameraDirection(const Ogre::Vector3 &pos);

    signals:
        void cameraPositionChanged(const Ogre::Vector3 &pos);
        void si_select(int id);
        void si_selectionObjet(Ogre::SceneNode *object);
        void si_selectionSegment(Ogre::ManualObject * segment);

    protected:
        virtual void keyPressEvent(QKeyEvent *e);
        virtual void moveEvent(QMoveEvent *e);
        virtual void mouseDoubleClickEvent(QMouseEvent *e);
        virtual void mouseMoveEvent(QMouseEvent *e);
        virtual void mousePressEvent(QMouseEvent *e);
        virtual void mouseReleaseEvent(QMouseEvent *e);
        virtual void paintEvent(QPaintEvent *e);
        virtual void resizeEvent(QResizeEvent *e);
        virtual void showEvent(QShowEvent *e);
        virtual void wheelEvent(QWheelEvent *e);

    private:
        void initOgreSystem();
        void setupNLoadResources();
        void createScene();
        Ogre::MovableObject *picking(QMouseEvent *e);
        void selectionObjet(QMouseEvent *e);

    private:
        static const QPoint invalidMousePoint;

    private:
        Ogre::Root          *ogreRoot;
        Ogre::SceneManager  *ogreSceneManager;
        Ogre::RenderWindow  *ogreRenderWindow;
        Ogre::Viewport      *ogreViewport;
        Ogre::Camera        *ogreCamera;

        QPoint oldPos;
        Ogre::Vector3 initCameraLookAt;
        Ogre::Vector3 initCameraPosition;

        /*!
         * \brief curentNode est le noeud 3d courent
         */
        Ogre::Node * curentNode;
    };
}
#endif OGREWIDGET_H
