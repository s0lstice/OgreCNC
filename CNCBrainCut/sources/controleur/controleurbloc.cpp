#include "controleurbloc.h"

#include <QObject>
#include <QDebug>
#include <QString>

#include "../modele/bloc/nodebloc.h"
#include "../modele/bloc/bloc.h"
#include "controleurmain.h"

using namespace OgreCNC;
ControleurBloc::ControleurBloc(NodeBloc *rootBloc, QObject *parent) :
    QAbstractItemModel(parent)
{
    m_controleur = qobject_cast<ControleurMain *>(parent);
    m_root = rootBloc;
}

ControleurBloc::ControleurBloc(QObject *parent) :
    QAbstractItemModel(parent)
{
    m_controleur = qobject_cast<ControleurMain *>(parent);
    m_root = NULL;
}

void ControleurBloc::setRootNode(NodeBloc *rootBloc){
    m_root = rootBloc;
}

QModelIndex ControleurBloc::index(int row, int column, const QModelIndex &parent) const{
    if(!m_root || row < 0 || column < 0)
        return QModelIndex();
    NodeBloc *parentNode = nodeFromIndex(parent);
    Bloc *childNode = parentNode->getListeFils()->value(row);

    if(!childNode)
        return QModelIndex();
    return createIndex(row, column, childNode);
}

NodeBloc * ControleurBloc::nodeFromIndex(const QModelIndex &index) const {
    if(index.isValid())
        return static_cast<NodeBloc *>(index.internalPointer());
    else
        return m_root;
}

int ControleurBloc::rowCount(const QModelIndex &parent) const{
    if(parent.column() > 0)
        return 0;
    NodeBloc *parentNode = nodeFromIndex(parent);

    //s'il n'y a pas de parent, il n'y a pas de feres
    if(parentNode == NULL){
        return 0;
    }

    //si ce n'est pas un NodeBloc, il n'y a pas de fils
    if(parentNode->getType() != Bloc::NODE)
        return 0;

    return parentNode->getListeFils()->count();
}

int ControleurBloc::columnCount(const QModelIndex &parent) const{
    return 1; //une seul colonne pour l'affichage
}

QModelIndex ControleurBloc::parent(const QModelIndex &child) const{
    NodeBloc *childNode = nodeFromIndex(child);
    if(childNode == NULL)
        return QModelIndex();

    NodeBloc *parentNode = childNode->getParent();
    if(!parentNode)
        return QModelIndex();

    NodeBloc *grandParentNode = parentNode->getParent();
    if(!grandParentNode)
        return QModelIndex();

    int row = grandParentNode->getListeFils()->indexOf(parentNode);
    return createIndex(row, 0, grandParentNode);
}

QVariant ControleurBloc::data(const QModelIndex &index, int role) const{
    if(role == Qt::CheckStateRole)
    {
      return nodeFromIndex(index)->getVisibilite();
    }

    if(role != Qt::DisplayRole)
        return QVariant();

    Bloc *bloc = nodeFromIndex(index);
    if(!bloc)
        return QVariant();

    return bloc->getName();
}

void ControleurBloc::add(Bloc * bloc, const QModelIndex  &index){
    NodeBloc *groupe;

    if(index.isValid() == false)
        groupe = m_root;
    else
        groupe = nodeFromIndex(index);

    if(groupe->getType() != Bloc::NODE)
        groupe = groupe->getParent();

    emit beginResetModel();
    groupe->append(bloc);
    qDebug() << QObject::tr("[Gestion des blocs] ajout du bloc : %1").arg(groupe->getName());
    emit endResetModel();
}

void ControleurBloc::creatBloc(const QModelIndex  &index){
    NodeBloc *groupe;

    if(index.isValid() == false)
        groupe = m_root;
    else
        groupe = nodeFromIndex(index);

    if(groupe->getType() != Bloc::NODE)
        groupe = groupe->getParent();

    Bloc * bloc = new Bloc(groupe);

    emit beginResetModel();
    groupe->append(bloc);
    qDebug() << QObject::tr("[Gestion des blocs] creation du blocs : %1").arg(bloc->getName());
    emit endResetModel();

    emit ogreDrawBloc(bloc);
}

void ControleurBloc::creatBloc(Ogre::Vector3 dimention, Ogre::Vector3 position, const QModelIndex  &index){
    NodeBloc *groupe;

    if(index.isValid() == false)
        groupe = m_root;
    else
        groupe = nodeFromIndex(index);

    if(groupe->getType() != Bloc::NODE)
        groupe = groupe->getParent();

    emit beginResetModel();
    Bloc * bloc = new Bloc(dimention, position, groupe);
    bloc->updateBloc3d();
    groupe->append(bloc);
    qDebug() << QObject::tr("[Gestion des blocs] creation du blocs : %1").arg(bloc->getName());
    emit endResetModel();

    emit ogreDrawBloc(bloc);
}

void ControleurBloc::creatNodeBloc(const QModelIndex  &index){
    NodeBloc *groupe;

    if(index.isValid() == false)
        groupe = m_root;
    else
        groupe = nodeFromIndex(index);

    if(groupe->getType() != Bloc::NODE)
        groupe = groupe->getParent();

    emit beginResetModel();
    NodeBloc * nodeBloc = new NodeBloc(groupe);
    groupe->append(nodeBloc);
    qDebug() << QObject::tr("[Gestion des blocs] creation du blocs : %1").arg(groupe->getName());
    emit endResetModel();
}

Qt::ItemFlags ControleurBloc::flags (const QModelIndex  &index ) const{
    return Qt::ItemIsUserCheckable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool ControleurBloc::setData (const QModelIndex &index, const QVariant &value, int role){
    Bloc *bloc = nodeFromIndex(index);

    if(role == Qt::EditRole){
        qDebug() << QObject::tr("[Gestion des blocs] changement du nom du bloc \"%1\" en \"%2\"").arg(bloc->getName()).arg(value.toString());
        bloc->setName(value.toString());
    }

    if(role == Qt::CheckStateRole)
    {
        bloc->setVisibilite(static_cast<Qt::CheckState>(value.toUInt()));
        emit dataChanged(index, index);

        if(bloc->getType() == Bloc::NODE){
            switchEtat((NodeBloc *)bloc);
            emit layoutChanged();
        }
    }
    return true;
}

void ControleurBloc::switchEtat(Bloc *blocs){
    Bloc * child;
    QVector<Bloc*> * childs;

    if(blocs == NULL){
        qDebug() << tr("[Gestion des blocs] inversion de l'etat de touts les blocs");
        blocs = m_root;

        //permetre la recurance
        if(blocs->getVisibilite() == Qt::Checked)
            blocs->setVisibilite(Qt::Unchecked);
        else{
            blocs->setVisibilite(Qt::Checked);
        }
    }

    if(blocs->getType() == Bloc::NODE){
        qDebug() << tr("[Gestion des blocs] inversion de l'etat du groupe de blocs %1").arg(blocs->getName());
        childs = ((NodeBloc*)blocs)->getListeFils();

        foreach(child, *childs){
            qDebug() << tr("[Gestion des blocs] inversion de l'etat du membre %1 en fonction de l'etat parent").arg(child->getName());
            child->setVisibilite(child->getParent()->getVisibilite());

            if(child->getType() == Bloc::NODE){
                switchEtat((NodeBloc *)child);
            }

            emit layoutChanged();

        }
    }
    else{
        if(blocs->getVisibilite() == Qt::Checked){
            blocs->setVisibilite(Qt::Unchecked);
            qDebug() << tr("[Gestion des blocs] deselection du bloc %1").arg(blocs->getName());
        }
        else
        {
            blocs->setVisibilite(Qt::Checked);
            qDebug() << tr("[Gestion des blocs] selection du bloc %1").arg(blocs->getName());
        }
        emit layoutChanged();
    }

}
