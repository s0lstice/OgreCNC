#include "bloc.h"

#include <string>
#include <QDebug>

#include "nodebloc.h"
#include "../constantesapplication.h"

using namespace OgreCNC;
int Bloc::nbBloc = 0;

/*Constructeurs*/

Bloc::Bloc(Ogre::Vector3 dimention, Ogre::Vector3 position, NodeBloc *parent)  :
    QObject(parent)
{
    m_dimension = dimention;
    m_position = position;

    m_id = nbBloc++;
    m_name = QString::number(m_id);
    m_parent = parent;

    m_etat = CHUTE;
    m_type = BLOC;
    m_select = Qt::Unchecked;

    m_nodeBloc3d = NULL;
    m_faceMatName = constantes::BLOC_CHUTE;
    m_segmentMatName = "BaseWhiteNoLighting";

    updateSommets();
}

Bloc::Bloc(NodeBloc *parent)
{
    m_dimension = Ogre::Vector3(0,0,0);
    m_position = Ogre::Vector3(0,0,0);

    m_etat = CHUTE;
    m_type = BLOC;
    m_select = Qt::Unchecked;

    m_id = nbBloc++;
    m_name = QString::number(m_id);
    m_parent = parent;

    m_nodeBloc3d = NULL;
    m_faceMatName = constantes::BLOC_CHUTE;
    m_segmentMatName = "BaseWhiteNoLighting";

    updateSommets();
}

Bloc::~Bloc()
{
    //detruit par ogre !!!

//    if(m_blocContour3d != NULL);
//        delete m_blocContour3d;
//    if(m_blocFace3d != NULL);
//        delete m_blocFace3d;
//    if(m_nodeBloc3d != NULL);
//        delete m_nodeBloc3d;
}

void Bloc::updateSommets(){
    m_sommet0 = Ogre::Vector3(- m_dimension[0]/2, + m_dimension[1]/2, + m_dimension[2]/2);
    m_sommet1 = Ogre::Vector3(- m_dimension[0]/2, - m_dimension[1]/2, + m_dimension[2]/2);
    m_sommet2 = Ogre::Vector3(+ m_dimension[0]/2, - m_dimension[1]/2, + m_dimension[2]/2);
    m_sommet3 = Ogre::Vector3(+ m_dimension[0]/2, + m_dimension[1]/2, + m_dimension[2]/2);
    m_sommet4 = Ogre::Vector3(- m_dimension[0]/2, + m_dimension[1]/2, - m_dimension[2]/2);
    m_sommet5 = Ogre::Vector3(- m_dimension[0]/2, - m_dimension[1]/2, - m_dimension[2]/2);
    m_sommet6 = Ogre::Vector3(+ m_dimension[0]/2, - m_dimension[1]/2, - m_dimension[2]/2);
    m_sommet7 = Ogre::Vector3(+ m_dimension[0]/2, + m_dimension[1]/2, - m_dimension[2]/2);
}

QVariantMap Bloc::serialize(){
    QVariantMap blocMap;

    blocMap.insert("id", m_id);
    blocMap.insert("nom", m_name);
    blocMap.insert("etat", m_etat);
    blocMap.insert("type", m_type);
    blocMap.insert("selection", m_select);

    QVariantMap positionMap;
    positionMap.insert("x", m_position.x);
    positionMap.insert("y", m_position.y);
    positionMap.insert("z", m_position.z);
    blocMap.insert("position", positionMap);

    QVariantMap dimentionMap;
    dimentionMap.insert("x", m_dimension.x);
    dimentionMap.insert("y", m_dimension.y);
    dimentionMap.insert("z", m_dimension.z);
    blocMap.insert("dimention", dimentionMap);

    return blocMap;
}

void Bloc::deserialize(QVariantMap bloc){
    m_id = bloc["id"].toInt();
    m_name = bloc["nom"].toString();
    m_etat = (Etat)bloc["etat"].toInt();
    m_select = (Qt::CheckState)bloc["selection"].toInt();

    QVariantMap position = bloc["position"].toMap();
    m_position.x = position["x"].toInt();
    m_position.y = position["y"].toInt();
    m_position.z = position["z"].toInt();

    QVariantMap dimention = bloc["dimention"].toMap();
    m_dimension.x = dimention["x"].toInt();
    m_dimension.y = dimention["y"].toInt();
    m_dimension.z = dimention["z"].toInt();
}

void Bloc::setEtat(Etat etat)
{
    if(etat != m_etat)
    {
        m_etat = etat;
        if(etat == UTILISE)
            m_faceMatName = constantes::BLOC_USE;
        else
            m_faceMatName = constantes::BLOC_CHUTE;
        if(m_select == Qt::Checked)
            m_faceMatName = constantes::BLOC_SELECTED;

        emit updateCouleurBloc(this);
    }
}

void Bloc::setCheck(Qt::CheckState state){
    if(m_select != state)
    {
        m_select = state;
        if(m_select == Qt::Checked)
        {
            m_faceMatName = constantes::BLOC_SELECTED;
        }
        else
        {
            if(m_etat == CHUTE)
            {
                m_faceMatName = constantes::BLOC_CHUTE;
            }
            else
                m_faceMatName = constantes::BLOC_USE;
        }

        emit updateCouleurBloc(this);
    }
}
