#include "bloc.h"

#include <string>
#include <QDebug>

#include "nodebloc.h"

using namespace OgreCNC;
int Bloc::nbBloc = 0;

/*Constructeurs*/

Bloc::Bloc(Ogre::Vector3 dimention, Ogre::Vector3 position, NodeBloc *parent)
{
    m_dimention = dimention;
    m_position = position;

    m_id = nbBloc++;
    m_name = QString::number(m_id);
    m_parent = parent;

    m_etat = CHUTE;
    m_type = BLOC;
    m_select = Qt::Unchecked;

    m_blocContour3d = NULL;
    m_blocFace3d = NULL;
    m_nodeBloc3d = NULL;
    m_faceMatName = "cube";
    m_segmentMatName = "BaseWhiteNoLighting";
    m_colorBloc = Ogre::ColourValue(0,0.5,1.0,0.5);
    m_colorSegments = Ogre::ColourValue(0.0,0.0,0.0,1);
}

Bloc::Bloc(NodeBloc *parent)
{
    m_dimention = Ogre::Vector3(0,0,0);
    m_position = Ogre::Vector3(0,0,0);

    m_etat = CHUTE;
    m_type = BLOC;
    m_select = Qt::Unchecked;

    m_id = nbBloc++;
    m_name = QString::number(m_id);
    m_parent = parent;

    m_blocContour3d = NULL;
    m_blocFace3d = NULL;
    m_nodeBloc3d = NULL;
    m_faceMatName = "cube";
    m_segmentMatName = "BaseWhiteNoLighting";
    m_colorBloc = Ogre::ColourValue(0,0.5,1.0,0.5);
    m_colorSegments = Ogre::ColourValue(0.0,0.0,0.0,1);

    m_id++;
}

Bloc::~Bloc()
{
    if(m_blocContour3d != NULL);
        delete m_blocContour3d;
    if(m_blocFace3d != NULL);
        delete m_blocFace3d;
    if(m_nodeBloc3d != NULL);
        delete m_nodeBloc3d;
}

void Bloc::updateSommets(){
    m_sommet0 = Ogre::Vector3(- m_dimention[0]/2, + m_dimention[1]/2, + m_dimention[2]/2);
    m_sommet1 = Ogre::Vector3(- m_dimention[0]/2, - m_dimention[1]/2, + m_dimention[2]/2);
    m_sommet2 = Ogre::Vector3(+ m_dimention[0]/2, - m_dimention[1]/2, + m_dimention[2]/2);
    m_sommet3 = Ogre::Vector3(+ m_dimention[0]/2, + m_dimention[1]/2, + m_dimention[2]/2);
    m_sommet4 = Ogre::Vector3(- m_dimention[0]/2, + m_dimention[1]/2, - m_dimention[2]/2);
    m_sommet5 = Ogre::Vector3(- m_dimention[0]/2, - m_dimention[1]/2, - m_dimention[2]/2);
    m_sommet6 = Ogre::Vector3(+ m_dimention[0]/2, - m_dimention[1]/2, - m_dimention[2]/2);
    m_sommet7 = Ogre::Vector3(+ m_dimention[0]/2, + m_dimention[1]/2, - m_dimention[2]/2);
}


