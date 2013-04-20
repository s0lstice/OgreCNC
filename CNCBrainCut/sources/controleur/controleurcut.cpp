#include "controleurcut.h"
#include "../modele/modelecut.h"
#include "controleurmain.h"
#include "../modele/modelemain.h"
#include "controleurbloc.h"
#include "../modele/bloc/nodebloc.h"
#include <ui_vuemain.h>


using namespace OgreCNC;
ControleurCut::ControleurCut(ModeleCut* modele, QObject *parent) : QObject(parent)
{
    m_modeleCut = modele;
    noeud = NULL;
    controleurMain = qobject_cast<ControleurMain *>(parent);
}


void ControleurCut::deleteBlocsCrees(){
    if(noeud != NULL)
    {
        /*détruire le noeud et tous ses fils*/
        Bloc* bloc = controleurMain->modeleMain->getModeleBloc()->deleteNodeBloc(noeud);
        controleurMain->modeleMain->getModeleBloc()->setBlocCheck(bloc, Qt::Checked);
    }
}

void ControleurCut::update_cut(){
    /*On met à jour des blocs créés pour la découpe en fonction du modèle*/
    //On doit supprimer les blocs créés et les refaire

    if(m_modeleCut != NULL)
    {
        /*On repositionne le bloc courant*/
        if(noeud!=NULL)
            controleurMain->modeleMain->getModeleBloc()->setBlocCheck(noeud->getInitialBloc(),Qt::Checked);

        /*Suppression des noeuds déjà présents*/
        deleteBlocsCrees();

        /*Création du noeud correspondant au bloc courant*/
        if(m_modeleCut->nbFils != 0)
            noeud = controleurMain->modeleMain->getModeleBloc()->creatNodeBloc(controleurMain->modeleMain->currentBloc,controleurMain->modeleMain->currentBloc->getParent());

        /*Création du nombre de blocs fils nécessaires*/
        Bloc* blocFils = NULL;
        Ogre::Vector3 dimFils(controleurMain->modeleMain->currentBloc->getDimension()/m_modeleCut->nbFils);
        for(int i = 0; i < m_modeleCut->nbFils; i++)
        {
            blocFils = controleurMain->modeleMain->getModeleBloc()->creatBloc(dimFils,controleurMain->modeleMain->currentBloc->getPosition(),noeud);
        }

        /*------------------------------*/

        Bloc* fils;

        Ogre::Vector3 dim;

        if(m_modeleCut->decoupeCM == ModeleCut::CLASSIQUE) //on n'a que 2 blocs fils à modifier
        {
            if(controleurMain->getVue()->getVue()->distance_text->text().toDouble() == 0.0)
                m_modeleCut->distance = 1.0;

            //Premier fils
            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(0);

            if(m_modeleCut->direction == ModeleCut::X)
            {
                dim[0] = m_modeleCut->distance;
                dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1];
                dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2];
                fils->setDimension(dim);
            }
            else
            {
                if(m_modeleCut->direction == ModeleCut::Y)
                {
                    dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0];
                    dim[1] = m_modeleCut->distance;
                    dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2];
                    fils->setDimension(dim);
                }
                else
                {
                    dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0];
                    dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1];
                    dim[2] = m_modeleCut->distance;
                    fils->setDimension(dim);
                }
            }

            //Deuxième fils
            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(1);
            if(m_modeleCut->direction == ModeleCut::X)
            {
                dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0]-m_modeleCut->distance;
                dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1];
                dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2];
                fils->setDimension(dim);
            }
            else
            {
                if(m_modeleCut->direction == ModeleCut::Y)
                {
                    dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0];
                    dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1]-m_modeleCut->distance;
                    dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2];
                    fils->setDimension(dim);
                }
                else
                {
                    dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0];
                    dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1];
                    dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2]-m_modeleCut->distance;
                    fils->setDimension(dim);
                }
            }
        }
        else //découpe multiple
        {
            if(controleurMain->getVue()->getVue()->distance_text->text().toDouble() == 0.0)
                m_modeleCut->distance = 0.0;

            if(m_modeleCut->nbBlocs != 0 && m_modeleCut->distance == 0)//découpe multiple par définition du nombre de blocs
            {
                if(m_modeleCut->direction == ModeleCut::X)
                {
                    dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0]/m_modeleCut->nbFils;
                    dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1];
                    dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2];
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
                        dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0];
                        dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1]/m_modeleCut->nbFils;
                        dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2];
                        for(int i = 0; i < m_modeleCut->nbFils; i++)
                        {
                            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                            fils->setDimension(dim);
                        }
                    }
                    else
                    {
                        dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0];
                        dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1];
                        dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2]/m_modeleCut->nbFils;
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
                        if(m_modeleCut->nbFils == controleurMain->modeleMain->currentBloc->getDimension()[0]/m_modeleCut->distance)
                        {
                            //IDEM cas 1
                            dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0]/m_modeleCut->nbFils;
                            dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1];
                            dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2];
                            for(int i = 0; i < m_modeleCut->nbFils; i++)
                            {
                                fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                fils->setDimension(dim);
                            }
                        }
                        else
                        {
                            dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0]/m_modeleCut->distance;
                            dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1];
                            dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2];
                            for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                            {
                                fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                fils->setDimension(dim);
                            }
                            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                            dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
                            fils->setDimension(dim);
                        }
                    }
                    else
                    {
                        if(m_modeleCut->direction == ModeleCut::Y)
                        {
                            if(m_modeleCut->nbFils == controleurMain->modeleMain->currentBloc->getDimension()[1]/m_modeleCut->distance)
                            {
                                //IDEM cas 1
                                dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0];
                                dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1]/m_modeleCut->nbFils;
                                dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2];
                                for(int i = 0; i < m_modeleCut->nbFils; i++)
                                {
                                    fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                    fils->setDimension(dim);
                                }
                            }
                            else
                            {
                                dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0];
                                dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1]/m_modeleCut->distance;
                                dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2];
                                for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                                {
                                    fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                    fils->setDimension(dim);
                                }
                                fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                                dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
                                fils->setDimension(dim);
                            }
                        }
                        else
                        {
                            if(m_modeleCut->nbFils == controleurMain->modeleMain->currentBloc->getDimension()[2]/m_modeleCut->distance)
                            {
                                //IDEM cas 1
                                dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0];
                                dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1];
                                dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2]/m_modeleCut->nbFils;
                                for(int i = 0; i < m_modeleCut->nbFils; i++)
                                {
                                    fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                    fils->setDimension(dim);
                                }
                            }
                            else
                            {
                                dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0];
                                dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1];
                                dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2]/m_modeleCut->distance;
                                for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                                {
                                    fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                    fils->setDimension(dim);
                                }
                                fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                                dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
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
                                dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0]/m_modeleCut->nbFils;
                                dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1];
                                dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2];
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
                                    dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0]/m_modeleCut->distance;
                                    dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1];
                                    dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2];
                                    for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                                    {
                                        fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                        fils->setDimension(dim);
                                    }
                                    fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                                    dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
                                    fils->setDimension(dim);
                                }
                                else
                                {
                                    dim[0] = m_modeleCut->distance;
                                    dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1];
                                    dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2];
                                    for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                                    {
                                        fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                        fils->setDimension(dim);
                                    }
                                    fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                                    dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
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
                                    dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0];
                                    dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1]/m_modeleCut->nbFils;
                                    dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2];
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
                                        dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0];
                                        dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1]/m_modeleCut->distance;
                                        dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2];
                                        for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                                        {
                                            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                            fils->setDimension(dim);
                                        }
                                        fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                                        dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
                                        fils->setDimension(dim);
                                    }
                                    else
                                    {
                                        dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0];
                                        dim[1] = m_modeleCut->distance;
                                        dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2];
                                        for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                                        {
                                            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                            fils->setDimension(dim);
                                        }
                                        fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                                        dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
                                        fils->setDimension(dim);
                                    }
                                }
                            }
                            else
                            {
                                if(m_modeleCut->nbFils == m_modeleCut->nbBlocs)
                                {
                                    //IDEM cas 1
                                    dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0];
                                    dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1];
                                    dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2]/m_modeleCut->nbFils;
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
                                        dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0];
                                        dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1];
                                        dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2]/m_modeleCut->distance;
                                        for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                                        {

                                            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                            fils->setDimension(dim);
                                        }
                                        fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                                        dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
                                        fils->setDimension(dim);
                                    }
                                    else
                                    {
                                        dim[0] = controleurMain->modeleMain->currentBloc->getDimension()[0];
                                        dim[1] = controleurMain->modeleMain->currentBloc->getDimension()[1];
                                        dim[2] = m_modeleCut->distance;
                                        for(int i = 0; i < m_modeleCut->nbFils-1; i++)
                                        {
                                            fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(i);
                                            fils->setDimension(dim);
                                        }
                                        fils = controleurMain->getControleurCut()->noeud->getListeFils()->at(m_modeleCut->nbFils-1);
                                        dim[2] = controleurMain->modeleMain->currentBloc->getDimension()[2]-(m_modeleCut->distance*(m_modeleCut->nbFils-1));
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
