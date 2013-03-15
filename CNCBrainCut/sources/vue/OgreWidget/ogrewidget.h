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

        void drawBloc(Bloc * bloc);

    public slots:
        void setBackgroundColor(QColor c);
        void setCameraPosition(const Ogre::Vector3 &pos);
        void resizeWidget(int w, int h);

    signals:
        void cameraPositionChanged(const Ogre::Vector3 &pos);

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

    private:
        static const Ogre::Real turboModifier;
        static const QPoint invalidMousePoint;

    private:
        Ogre::Root          *ogreRoot;
        Ogre::SceneManager  *ogreSceneManager;
        Ogre::RenderWindow  *ogreRenderWindow;
        Ogre::Viewport      *ogreViewport;
        Ogre::Camera        *ogreCamera;

        QPoint oldPos;
        Ogre::SceneNode *selectedNode;
    };
}
#endif OGREWIDGET_H
