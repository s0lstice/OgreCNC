#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMdiSubWindow>
#include "Coordinate3DModifier.h"
#include "ogrewidget.h"

class vue3d : public QMdiSubWindow
{
Q_OBJECT

public:
    vue3d()
    :ogreWidget(0)
    {
        ogreWidget = new OgreWidget(this);

        camPosModifier = new Coordinate3DModifier(this);


        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(ogreWidget);

        this->setLayout(layout);
        this->resize(800, 600);
        this->setWindowTitle("Simple example");

        connect(camPosModifier, SIGNAL(coordinateChanged(const Ogre::Vector3&)),
                ogreWidget, SLOT(setCameraPosition(const Ogre::Vector3&)));
        connect(ogreWidget, SIGNAL(cameraPositionChanged(const Ogre::Vector3&)),
                camPosModifier, SLOT(setNewCoordinate(const Ogre::Vector3&)));
    }
/*
private:
    void createActionMenus()
    {
        QAction *closeAct = new QAction("Quitter", this);
        connect(closeAct, SIGNAL(triggered()), this, SLOT(close()));

        QAction *changeColorAct = new QAction("Changer la couleur de fond", this);
        connect(changeColorAct, SIGNAL(triggered()), this, SLOT(chooseBgColor()));

        QMenu *menu = menuBar()->addMenu("Divers");
        menu->addAction(changeColorAct);
        menu->addAction(closeAct);
    }

    void createDockWidget()
    {
        QDockWidget *camPosDock = new QDockWidget("Camera Position", this);
        camPosDock->setAllowedAreas(Qt::AllDockWidgetAreas);
        camPosDock->setFeatures(QDockWidget::DockWidgetMovable |
                                QDockWidget::DockWidgetFloatable);
        camPosDock->setWidget(camPosModifier);

        addDockWidget(Qt::NoDockWidgetArea, camPosDock);
    }
*/
private slots:
    void chooseBgColor()
    {
        QColor c = QColorDialog::getColor();
        ogreWidget->setBackgroundColor(c);
    }

private:
    OgreWidget *ogreWidget;
    Coordinate3DModifier *camPosModifier;
};

#endif // MAINWINDOW_H
