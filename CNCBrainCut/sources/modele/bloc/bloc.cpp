#include "bloc.h"

#include <string>
#include <QDebug>

#include "nodebloc.h"

using namespace OgreCNC;
int Bloc::m_id = 0;

/*Constructeurs*/

Bloc::Bloc(Ogre::Vector3 dimention, Ogre::Vector3 position, NodeBloc *parent)
{
    m_dimention = dimention;
    m_position = position;

    m_id++;
    m_name = QString(m_id);
    m_parent = parent;

    m_etat = CHUTE;
    m_visible = Qt::Checked;

    m_bloc3d = NULL;
    m_nodeBloc3d = NULL;
    m_matName = "BaseWhiteNoLighting";
}

Bloc::Bloc(NodeBloc *parent)
{
    m_dimention[1] = 0;
    m_dimention[0] = 0;
    m_dimention[2] = 0;

    m_etat = CHUTE;
    m_visible = Qt::Unchecked;

    m_id++;
    m_name = QString(m_id);
    m_parent = parent;

    m_bloc3d = NULL;
    m_nodeBloc3d = NULL;
    m_matName = "BaseWhiteNoLighting";
}

Bloc::~Bloc()
{
    if(m_bloc3d != NULL);
        delete m_bloc3d;
    if(m_nodeBloc3d != NULL);
        delete m_nodeBloc3d;
}

void Bloc::updateBloc3d(){

    //Creation d'un bloc
    if(m_bloc3d==NULL){
        m_bloc3d = new Ogre::ManualObject(QString(m_id).toStdString()); //std::to_string(m_id) :: Bug avec certain vection de MinGW : error: 'to_string' is not a member of 'std'

        m_bloc3d->begin(m_matName.toStdString(), Ogre::RenderOperation::OT_TRIANGLE_LIST);

        m_bloc3d->position(- m_dimention[0]/2, + m_dimention[1]/2, + m_dimention[2]/2);
        m_bloc3d->colour(Ogre::ColourValue(0.0f,1.0f,0.0f,1.0f));
        m_bloc3d->textureCoord(0.0, 1.0);

        m_bloc3d->position(- m_dimention[0]/2, - m_dimention[1]/2, + m_dimention[2]/2);
        m_bloc3d->colour(Ogre::ColourValue(1.0f,1.0f,0.0f,1.0f));
        m_bloc3d->textureCoord(1.0, 1.0);

        m_bloc3d->position(+ m_dimention[0]/2, - m_dimention[1]/2, + m_dimention[2]/2);
        m_bloc3d->colour(Ogre::ColourValue(1.0f,0.0f,0.0f,1.0f));
        m_bloc3d->textureCoord(1.0, 0.0);

        m_bloc3d->position(+ m_dimention[0]/2, + m_dimention[1]/2, + m_dimention[2]/2);
        m_bloc3d->colour(Ogre::ColourValue(0.0f,0.0f,0.0f,1.0f));
        m_bloc3d->textureCoord(0.0, 0.0);

        m_bloc3d->position(- m_dimention[0]/2, + m_dimention[1]/2, - m_dimention[2]/2);
        m_bloc3d->colour(Ogre::ColourValue(0.0f,1.0f,1.0f,1.0f));
        m_bloc3d->textureCoord(0.0, 1.0);

        m_bloc3d->position(- m_dimention[0]/2, - m_dimention[1]/2, - m_dimention[2]/2);
        m_bloc3d->colour(Ogre::ColourValue(1.0f,1.0f,1.0f,1.0f));
        m_bloc3d->textureCoord(1.0, 1.0);

        m_bloc3d->position(+ m_dimention[0]/2, - m_dimention[1]/2, - m_dimention[2]/2);
        m_bloc3d->colour(Ogre::ColourValue(1.0f,0.0f,1.0f,1.0f));
        m_bloc3d->textureCoord(1.0, 0.0);

        m_bloc3d->position(+ m_dimention[0]/2, + m_dimention[1]/2, - m_dimention[2]/2);
        m_bloc3d->colour(Ogre::ColourValue(0.0f,0.0f,1.0f,1.0f));
        m_bloc3d->textureCoord(0.0, 0.0);

        // face behind / front
        m_bloc3d->triangle(0,1,2);
        m_bloc3d->triangle(2,3,0);
        m_bloc3d->triangle(4,6,5);
        m_bloc3d->triangle(6,4,7);

        // face top / down
        m_bloc3d->triangle(0,4,5);
        m_bloc3d->triangle(5,1,0);
        m_bloc3d->triangle(2,6,7);
        m_bloc3d->triangle(7,3,2);

        // face left / right
        m_bloc3d->triangle(0,7,4);
        m_bloc3d->triangle(7,0,3);
        m_bloc3d->triangle(1,5,6);
        m_bloc3d->triangle(6,2,1);

        m_bloc3d->end();
    }
    else //modification des dimentions
    {
         m_bloc3d->beginUpdate(0);

         m_bloc3d->position(- m_dimention[0]/2, + m_dimention[1]/2, + m_dimention[2]/2);
         m_bloc3d->position(- m_dimention[0]/2, - m_dimention[1]/2, + m_dimention[2]/2);
         m_bloc3d->position(+ m_dimention[0]/2, - m_dimention[1]/2, + m_dimention[2]/2);
         m_bloc3d->position(+ m_dimention[0]/2, + m_dimention[1]/2, + m_dimention[2]/2);
         m_bloc3d->position(- m_dimention[0]/2, + m_dimention[1]/2, - m_dimention[2]/2);
         m_bloc3d->position(- m_dimention[0]/2, - m_dimention[1]/2, - m_dimention[2]/2);
         m_bloc3d->position(+ m_dimention[0]/2, - m_dimention[1]/2, - m_dimention[2]/2);
         m_bloc3d->position(+ m_dimention[0]/2, + m_dimention[1]/2, - m_dimention[2]/2);

         m_bloc3d->end();
    }
}
