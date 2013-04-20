#ifndef OGREWIDGET_H
#define OGREWIDGET_H

#include <QtGui>
#include <Ogre.h>
#include <QGLWidget>

namespace OgreCNC {

    class Bloc;
    class VueMain;

    /*!
     * \brief The OgreWidget class permet l'integration d'Ogre3D dans un QGLWidget
     */
    class OgreWidget : public QGLWidget
    {
        Q_OBJECT

    public:
        /*!
         * \brief OgreWidget est le constructeur
         * \param parent
         */
        OgreWidget(QWidget *parent = 0);
        ~OgreWidget();
        /*!
         * \brief getSceneManager renvoie le gestionaire de scene d'Ogre3D
         * \return
         */
        inline Ogre::SceneManager *getSceneManager(){
            return ogreSceneManager;
        }
        /*!
         * \brief selectBloc applique le changement de materiau au faces du bloc en fonction de son etat
         * \param bloc
         */
        void selectBloc(Bloc * bloc);
        /*!
         * \brief selectNode change la couleur du segment en fonction de son etat
         * \param node
         */
        void selectNode(Ogre::SceneNode * node);
        /*!
         * \brief createBloc créé le bloc 3D d'un Bloc
         * \param bloc
         */
        void createBloc(Bloc * bloc);

    public slots:
        /*!
         * \brief setBackgroundColor change la couleur de fond de la zone 3D
         * \param c
         */
        void setBackgroundColor(QColor c);
        /*!
         * \brief setCameraPosition change la position de la camera
         * \param pos
         */
        void setCameraPosition(const Ogre::Vector3 &pos);
        /*!
         * \brief setCameraDirection change la direction de la camera
         * \param pos
         */
        void setCameraDirection(const Ogre::Vector3 &pos);

    signals:
        /*!
         * \brief cameraPositionChanged est un signal qui indique le changement de position de la camera
         * \param pos
         */
        void cameraPositionChanged(const Ogre::Vector3 &pos);
        /*!
         * \brief si_selectionObjet est un signal qui indique la sélection d'un bloc 3D
         * \param object
         */
        void si_selectionObjet(Ogre::SceneNode *object);
        /*!
         * \brief si_selectionSegment est un signal qui indique la sélection d'un segment
         * \param segment
         */
        void si_selectionSegment(Ogre::ManualObject * segment);

    protected:
        /*!
         * \brief keyPressEvent est l'action effectué quand une touche de clavié est appuié
         * \param e
         */
        virtual void keyPressEvent(QKeyEvent *e);
        /*!
         * \brief moveEvent est l'action effectué quand la zone 3D se deplace
         * \param e
         */
        virtual void moveEvent(QMoveEvent *e);
        /*!
         * \brief mouseDoubleClickEvent est l'action effectué quand un double clique souris est fait
         * \param e
         */
        virtual void mouseDoubleClickEvent(QMouseEvent *e);
        /*!
         * \brief mouseMoveEvent est l'action effectué quand la sourie se deplace
         * \param e
         */
        virtual void mouseMoveEvent(QMouseEvent *e);
        /*!
         * \brief mousePressEvent est l'action effectué quand un bouton de la souris est appuié
         * \param e
         */
        virtual void mousePressEvent(QMouseEvent *e);
        /*!
         * \brief mouseReleaseEvent est l'action effectué quand un bouton de la souris est relaché
         * \param e
         */
        virtual void mouseReleaseEvent(QMouseEvent *e);
        /*!
         * \brief wheelEvent  est l'action effectué quand a molette de la souris est utilisé
         * \param e
         */
        virtual void wheelEvent(QWheelEvent *e);

        virtual void paintEvent(QPaintEvent *e);
        virtual void resizeEvent(QResizeEvent *e);
        virtual void showEvent(QShowEvent *e);


    private:
        /*!
         * \brief initOgreSystem initialise le Ogre3D
         */
        void initOgreSystem();
        /*!
         * \brief setupNLoadResources charge les ressources utilisé par Ogre
         */
        void setupNLoadResources();
        /*!
         * \brief createScene créé un scene vide avec les parametre de base
         */
        void createScene();
        /*!
         * \brief picking revoie un Ogre::MovableObject se trouvant sous le curseur de la sourie
         * \param e
         * \return
         */
        Ogre::MovableObject *picking(QMouseEvent *e);
        /*!
         * \brief selectionObjet demande le picking a la position de l'evenment et emet un signal si c'est une bloc 3D ou un segment
         * \param e
         */
        void selectionObjet(QMouseEvent *e);

    private:
        /*!
         * \brief invalidMousePoint est lavaleur par deflaut en cas de position invalide
         */
        static const QPoint invalidMousePoint;

    private:
        /*!
         * \brief ogreRoot est la racine d'Ogre3D
         */
        Ogre::Root          *ogreRoot;
        /*!
         * \brief ogreSceneManager est le gestionaire de scene
         */
        Ogre::SceneManager  *ogreSceneManager;
        /*!
         * \brief ogreRenderWindow est la partie de la scene affiché
         */
        Ogre::RenderWindow  *ogreRenderWindow;
        /*!
         * \brief ogreViewport est le view port
         */
        Ogre::Viewport      *ogreViewport;
        /*!
         * \brief ogreCamera est la camera
         */
        Ogre::Camera        *ogreCamera;
        /*!
         * \brief oldPos est l'encienne position de la sourie
         */
        QPoint oldPos;
        /*!
         * \brief initCameraLookAt est la position initial du point regardé par la camera
         */
        Ogre::Vector3 initCameraLookAt;
        /*!
         * \brief initCameraPosition est la position de la camera
         */
        Ogre::Vector3 initCameraPosition;
        /*!
         * \brief m_vue est le vue principale de l'application
         */
        VueMain * m_vue;
    };
}
#endif OGREWIDGET_H
