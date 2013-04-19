#include "modelecut.h"
#include "modelemain.h"

using namespace OgreCNC;
ModeleCut::ModeleCut(QObject * parent) : QObject(parent)
{
    m_modeleMain = qobject_cast<ModeleMain *>(parent);

    isInUse = false;
    distance = 0.0;
    nbBlocs = 0;
    rayonChauffe = 0;
    decoupeCM = CLASSIQUE;
    nbFils = 2; //pour une découpe classique, on aura forcément 2 fils créés
    direction = X;
    posPerte = CENTREE;
}


ModeleCut::ModeleCut(decoupe_CM decCM,
                     directionDecoupe directionDec, positionPerte position,
                     qreal dist, int nombreBlocs, qreal rayon, QObject *parent) : QObject(parent)
{
    m_modeleMain = qobject_cast<ModeleMain*>(parent);
    isInUse = false;
    decoupeCM = decCM;
    direction = directionDec;
    posPerte = position;
    distance = dist;
    rayonChauffe = rayon;
    nbBlocs = nombreBlocs;
    if(decoupeCM == CLASSIQUE)
    {
        nbFils = 2;
    }
    else//cas d'une découpe multiple
    {
        if(nbBlocs != 0 && distance == 0)//découpe multiple par définition du nombre de blocs
        {
            nbFils = nbBlocs;
        }
        else
        {
            if(nbBlocs == 0 && distance != 0)//découpe multiple par définition d'une distance
            {
                Ogre::Vector3 dim = m_modeleMain->currentBloc->getDimension();
                if(direction == X)
                {
                    nbFils = floor(dim[0]/(distance+rayonChauffe)) + 1;//+1 pour la chute
                }
                else
                {
                    if(direction == Y)
                    {
                        nbFils = floor(dim[1]/(distance+rayonChauffe)) + 1;
                    }
                    else
                    {
                        nbFils = floor(dim[2]/(distance+rayonChauffe)) + 1;
                    }
                }
            }
            else//découpe multiple par définition d'un nombre de blocs et d'une distance
            {
                if(nbBlocs != 0 && distance != 0)
                {
                    Ogre::Vector3 dim = m_modeleMain->currentBloc->getDimension();
                    if(direction == X)
                    {
                        if((distance+rayonChauffe) * nbBlocs <= dim[0])
                        {
                            nbFils = nbBlocs + 1;//+1 pour la chute
                        }
                        else
                        {
                            int i = 0;
                            while((distance+rayonChauffe) * i <= dim[0])
                                i++;

                            nbFils = i;
                        }
                    }
                    else
                    {
                        if(direction == Y)
                        {
                            if((distance+rayonChauffe) * nbBlocs <= dim[1])
                            {
                                nbFils = nbBlocs + 1;
                            }
                            else
                            {
                                int i = 0;
                                while((distance+rayonChauffe) * i <= dim[1])
                                    i++;

                                nbFils = i;
                            }
                        }
                        else
                        {
                            if((distance+rayonChauffe) * nbBlocs <= dim[2])
                            {
                                nbFils = nbBlocs + 1;
                            }
                            else
                            {
                                int i = 0;
                                while((distance+rayonChauffe) * i <= dim[2])
                                    i++;

                                nbFils = i;
                            }
                        }
                    }
                }
            }
        }
    }
}
