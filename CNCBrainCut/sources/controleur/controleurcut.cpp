#include "controleurcut.h"
#include "../modele/modelecut.h"
#include "controleurmain.h"
#include "../modele/modelemain.h"
#include "controleurbloc.h"
#include "../modele/bloc/nodebloc.h"
//#include "ui_vuemain.h"

using namespace OgreCNC;
ControleurCut::ControleurCut(ModeleCut* modele, QObject *parent) : QObject(parent)
{
    m_modeleCut = modele;
    controleurMain = qobject_cast<ControleurMain *>(parent);

    /*Création du noeud correspondant au bloc courant*/
    if(m_modeleCut->nbFils != 0)
        noeud = controleurMain->getModeleBlocs()->getModeleBloc()->creatNodeBloc(controleurMain->m_modele->currentBloc,controleurMain->m_modele->currentBloc->getParent());

    /*Création du nombre de blocs fils nécessaires*/
    Ogre::Vector3 dim(controleurMain->m_modele->currentBloc->getDimension()/m_modeleCut->nbFils);
    for(int i = 0; i < m_modeleCut->nbFils; i++)
    {
        Bloc* blocFils = controleurMain->getModeleBlocs()->getModeleBloc()->creatBloc(dim,controleurMain->m_modele->currentBloc->getPosition()+i,noeud);
    }
}


void ControleurCut::deleteBlocsCrees(){
    /*if(noeud->getListeFils() != NULL)
    {
        if(m_modeleCut != NULL)
        {
            for(int i = 0; i < m_modeleCut->nbFils; i++)
            {
                //détruire les blocs fils
                controleurMain->m_modele->getModeleBloc()->deleteBloc(noeud->getListeFils()->at(i));
            }
        }
    }*/
    if(noeud != NULL)
    {
        /*détruire le noeud et tous ses fils*/
        Bloc* bloc = controleurMain->m_modele->getModeleBloc()->deleteNodeBloc(noeud);
        controleurMain->m_modele->getModeleBloc()->setBlocCheck(bloc, Qt::Checked);
    }
}

void ControleurCut::update_cut(){
    /*On met à jour des blocs créés pour la découpe en fonction du modèle*/
    if(m_modeleCut != NULL)
    {
        Bloc* fils;
        Ogre::Vector3 dim;
        if(m_modeleCut->decoupeCM == ModeleCut::CLASSIQUE) //on n'a que 2 blocs fils à modifier
        {
            //Premier fils
            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(0);

            if(m_modeleCut->direction == ModeleCut::X)
            {
                dim[0] = m_modeleCut->distance;
                dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1];
                dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2];
                fils->setDimension(dim);
            }
            else
            {
                if(m_modeleCut->direction == ModeleCut::Y)
                {
                    dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0];
                    dim[1] = m_modeleCut->distance;
                    dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2];
                    fils->setDimension(dim);
                }
                else
                {
                    dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0];
                    dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1];
                    dim[2] = m_modeleCut->distance;
                    fils->setDimension(dim);
                }
            }

            //Deuxième fils
            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(1);
            if(m_modeleCut->direction == ModeleCut::X)
            {
                dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0]-m_modeleCut->distance;
                dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1];
                dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2];
                fils->setDimension(dim);
            }
            else
            {
                if(m_modeleCut->direction == ModeleCut::Y)
                {
                    dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0];
                    dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1]-m_modeleCut->distance;
                    dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2];
                    fils->setDimension(dim);
                }
                else
                {
                    dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0];
                    dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1];
                    dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2]-m_modeleCut->distance;
                    fils->setDimension(dim);
                }
            }
        }
        else //découpe multiple
        {
            if(m_modeleCut->nbBlocs != 0 && m_modeleCut->distance == 0)//découpe multiple par définition du nombre de blocs
            {
                if(m_modeleCut->direction == ModeleCut::X)
                {
                    dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0]/m_modeleCut->nbFils;
                    dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1];
                    dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2];
                    for(int i = 0; i < m_modeleCut->nbFils; i++)
                    {
                        fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                        fils->setDimension(dim);
                    }
                }
                else
                {
                    if(m_modeleCut->direction == ModeleCut::Y)
                    {
                        dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0];
                        dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1]/m_modeleCut->nbFils;
                        dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2];
                        for(int i = 0; i < m_modeleCut->nbFils; i++)
                        {
                            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                            fils->setDimension(dim);
                        }
                    }
                    else
                    {
                        dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0];
                        dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1];
                        dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2]/m_modeleCut->nbFils;
                        for(int i = 0; i < m_modeleCut->nbFils; i++)
                        {
                            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                            fils->setDimension(dim);
                        }
                    }
                }
            }
            else
            {
                if(m_modeleCut->nbBlocs == 0 && m_modeleCut->distance != 0)//découpe multiple par définition d'une distance
                {
                    if(m_modeleCut->direction == ModeleCut::X)
                    {
                        if(m_modeleCut->nbFils == controleurMain->m_modele->currentBloc->getDimension()[0]/m_modeleCut->distance)
                        {
                            //IDEM cas 1
                            dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0]/m_modeleCut->nbFils;
                            dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1];
                            dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2];
                            for(int i = 0; i < m_modeleCut->nbFils; i++)
                            {
                                fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                fils->setDimension(dim);
                            }
                        }
                        else
                        {
                            dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0]/m_modeleCut->distance;
                            dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1];
                            dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2];
                            for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                            {
                                fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                fils->setDimension(dim);
                            }
                            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                            dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
                            fils->setDimension(dim);
                        }
                    }
                    else
                    {
                        if(m_modeleCut->direction == ModeleCut::Y)
                        {
                            if(m_modeleCut->nbFils == controleurMain->m_modele->currentBloc->getDimension()[1]/m_modeleCut->distance)
                            {
                                //IDEM cas 1
                                dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0];
                                dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1]/m_modeleCut->nbFils;
                                dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2];
                                for(int i = 0; i < m_modeleCut->nbFils; i++)
                                {
                                    fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                    fils->setDimension(dim);
                                }
                            }
                            else
                            {
                                dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0];
                                dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1]/m_modeleCut->distance;
                                dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2];
                                for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                                {
                                    fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                    fils->setDimension(dim);
                                }
                                fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                                dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
                                fils->setDimension(dim);
                            }
                        }
                        else
                        {
                            if(m_modeleCut->nbFils == controleurMain->m_modele->currentBloc->getDimension()[2]/m_modeleCut->distance)
                            {
                                //IDEM cas 1
                                dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0];
                                dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1];
                                dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2]/m_modeleCut->nbFils;
                                for(int i = 0; i < m_modeleCut->nbFils; i++)
                                {
                                    fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                    fils->setDimension(dim);
                                }
                            }
                            else
                            {
                                dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0];
                                dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1];
                                dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2]/m_modeleCut->distance;
                                for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                                {
                                    fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                    fils->setDimension(dim);
                                }
                                fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                                dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
                                fils->setDimension(dim);
                            }
                        }
                    }
                }
                else//découpe multiple par définition d'un nombre de blocs et d'une distance
                {
                    if(m_modeleCut->nbBlocs != 0 && m_modeleCut->distance != 0)
                    {
                        if(m_modeleCut->direction == ModeleCut::X)
                        {
                            if(m_modeleCut->nbFils == m_modeleCut->nbBlocs)
                            {
                                //IDEM cas 1
                                dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0]/m_modeleCut->nbFils;
                                dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1];
                                dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2];
                                for(int i = 0; i < m_modeleCut->nbFils; i++)
                                {
                                    fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                    fils->setDimension(dim);
                                }
                            }
                            else
                            {
                                if(m_modeleCut->nbFils < m_modeleCut->nbBlocs)
                                {
                                    //IDEM cas 2
                                    dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0]/m_modeleCut->distance;
                                    dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1];
                                    dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2];
                                    for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                                    {
                                        fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                        fils->setDimension(dim);
                                    }
                                    fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                                    dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
                                    fils->setDimension(dim);
                                }
                                else
                                {
                                    dim[0] = m_modeleCut->distance;
                                    dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1];
                                    dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2];
                                    for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                                    {
                                        fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                        fils->setDimension(dim);
                                    }
                                    fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                                    dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
                                    fils->setDimension(dim);
                                }
                            }
                        }
                        else
                        {
                            if(m_modeleCut->direction == ModeleCut::Y)
                            {
                                if(m_modeleCut->nbFils == m_modeleCut->nbBlocs)
                                {
                                    //IDEM cas 1
                                    dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0];
                                    dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1]/m_modeleCut->nbFils;
                                    dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2];
                                    for(int i = 0; i < m_modeleCut->nbFils; i++)
                                    {
                                        fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                        fils->setDimension(dim);
                                    }
                                }
                                else
                                {
                                    if(m_modeleCut->nbFils < m_modeleCut->nbBlocs)
                                    {
                                        //IDEM cas 2
                                        dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0];
                                        dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1]/m_modeleCut->distance;
                                        dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2];
                                        for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                                        {
                                            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                            fils->setDimension(dim);
                                        }
                                        fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                                        dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
                                        fils->setDimension(dim);
                                    }
                                    else
                                    {
                                        dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0];
                                        dim[1] = m_modeleCut->distance;
                                        dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2];
                                        for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                                        {
                                            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                            fils->setDimension(dim);
                                        }
                                        fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                                        dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
                                        fils->setDimension(dim);
                                    }
                                }
                            }
                            else
                            {
                                if(m_modeleCut->nbFils == m_modeleCut->nbBlocs)
                                {
                                    //IDEM cas 1
                                    dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0];
                                    dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1];
                                    dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2]/m_modeleCut->nbFils;
                                    for(int i = 0; i < m_modeleCut->nbFils; i++)
                                    {
                                        fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                        fils->setDimension(dim);
                                    }
                                }
                                else
                                {
                                    if(m_modeleCut->nbFils < m_modeleCut->nbBlocs)
                                    {
                                        //IDEM cas 2
                                        dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0];
                                        dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1];
                                        dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2]/m_modeleCut->distance;
                                        for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                                        {

                                            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                            fils->setDimension(dim);
                                        }
                                        fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                                        dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
                                        fils->setDimension(dim);
                                    }
                                    else
                                    {
                                        dim[0] = controleurMain->m_modele->currentBloc->getDimension()[0];
                                        dim[1] = controleurMain->m_modele->currentBloc->getDimension()[1];
                                        dim[2] = m_modeleCut->distance;
                                        for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                                        {
                                            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                            fils->setDimension(dim);
                                        }
                                        fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                                        dim[2] = controleurMain->m_modele->currentBloc->getDimension()[2]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
                                        fils->setDimension(dim);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
