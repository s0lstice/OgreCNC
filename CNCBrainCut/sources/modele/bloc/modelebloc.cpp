#include "modelebloc.h"

#include "../modelemain.h"
#include "nodebloc.h"
#include "QDebug"

using namespace OgreCNC;

ModeleBloc::ModeleBloc(NodeBloc *rootBloc, QObject *parent) :
    QAbstractItemModel(parent)
{
    m_modeleMain = qobject_cast<ModeleMain *>(parent);
    m_root = rootBloc;
    setRootNode(m_root);
}

ModeleBloc::ModeleBloc(QObject *parent) :
    QAbstractItemModel(parent)
{
    m_modeleMain = qobject_cast<ModeleMain *>(parent);
    m_root = NULL;
}

void ModeleBloc::setRootNode(NodeBloc *rootBloc){
    if(m_root != NULL)
    {
        disconnect(m_root, 0,0,0);
    }
    m_root = rootBloc;
    connect(m_root, SIGNAL(updateDimensionBloc(Bloc*)), this, SIGNAL(si_updateDimensionBloc(Bloc*)));
    connect(m_root, SIGNAL(updatePostionBloc(Bloc*)), this, SIGNAL(si_updatePostionBloc(Bloc*)));
    connect(m_root, SIGNAL(updateCouleurBloc(Bloc*)), this, SIGNAL(si_updateCouleurBloc(Bloc*)));
}

QModelIndex ModeleBloc::index(int row, int column, const QModelIndex &parent) const{
    if(!m_root || row < 0 || column < 0)
        return QModelIndex();

    NodeBloc *parentNode = nodeFromIndex(parent);
    Bloc *childNode = parentNode->getListeFils()->value(row);

    if(!childNode)
        return QModelIndex();
    return createIndex(row, column, childNode);
}

NodeBloc * ModeleBloc::nodeFromIndex(const QModelIndex &index) const {
    if(index.isValid())
        return static_cast<NodeBloc *>(index.internalPointer());
    else
        return m_root;
}

Bloc * ModeleBloc::blocFromOgreNode(Ogre::SceneNode * node, NodeBloc * racine){
    Bloc * bloc = NULL;

    if(node != NULL)
    {
        if(racine == NULL)
            racine = m_root;

        if(racine->getInitialBloc() != NULL) //teste si la NodeBloc possaide un bloc initiale, "on ne sais jamais"
        if(node == racine->getInitialBloc()->getNodeBloc3d()){
            bloc = racine->getInitialBloc();
            return bloc;
        }

        QVector<Bloc*> * fils = racine->getListeFils();

        for(int i = 0; i < fils->count() ; ++i)
        {
            if(node == fils->at(i)->getNodeBloc3d())
            {
                bloc = fils->at(i);
                return bloc;
            }

            if(fils->at(i)->getType() == Bloc::NODE)
            {

                bloc = blocFromOgreNode(node,(NodeBloc *)fils->at(i));

                if(bloc != NULL)
                    return bloc;
            }
        }
    }

    return bloc;
}

int ModeleBloc::rowCount(const QModelIndex &parent) const{
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

int ModeleBloc::columnCount(const QModelIndex &parent) const{
    return 1; //une seul colonne pour l'affichage
}

QModelIndex ModeleBloc::parent(const QModelIndex &child) const{
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

QVariant ModeleBloc::data(const QModelIndex &index, int role) const{
    if(role == Qt::CheckStateRole)
    {
      return nodeFromIndex(index)->getCheck();
    }

    if(role != Qt::DisplayRole)
        return QVariant();

    Bloc *bloc = nodeFromIndex(index);
    if(!bloc)
        return QVariant();

    return bloc->getName();
}

void ModeleBloc::add(Bloc * bloc, const QModelIndex  &index){
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

    if(bloc->getType() == Bloc::BLOC)
        emit si_selectBloc(bloc);
}

Bloc* ModeleBloc::creatBloc(const QModelIndex  &index){
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

    emit si_ogreDrawBloc(bloc);

    setBlocCheck(bloc, Qt::Checked);

    return bloc;
}

Bloc * ModeleBloc::creatBloc(Ogre::Vector3 dimension, Ogre::Vector3 position, NodeBloc * node){

    emit beginResetModel();
    Bloc * bloc = new Bloc(dimension, position, node);
    node->append(bloc);

    qDebug() << QObject::tr("[Gestion des blocs] creation du blocs : %1").arg(bloc->getName());
    emit endResetModel();

    emit si_createBloc(bloc);
    setBlocCheck(bloc, Qt::Checked);

    return bloc;
}

Bloc* ModeleBloc::creatBloc(Ogre::Vector3 dimension, Ogre::Vector3 position, const QModelIndex  &index){
    NodeBloc *groupe;

    if(index == QModelIndex())
        groupe = m_root;
    else
        groupe = nodeFromIndex(index);

    if(groupe->getType() != Bloc::NODE)
        groupe = groupe->getParent();

    emit beginResetModel();
    Bloc * bloc = new Bloc(dimension, position, groupe);
    groupe->append(bloc);

    qDebug() << QObject::tr("[Gestion des blocs] creation du blocs : %1").arg(bloc->getName());
    emit endResetModel();

    emit si_createBloc(bloc);
    setBlocCheck(bloc, Qt::Checked);

    return bloc;
}

NodeBloc * ModeleBloc::creatNodeBloc(Bloc * bloc, NodeBloc * parent){
    emit beginResetModel();

    NodeBloc * oldParent = bloc->getParent();
    oldParent->remove(bloc);

    NodeBloc * nodeBloc = new NodeBloc(bloc, parent);
    parent->append(nodeBloc);
    qDebug() << QObject::tr("[Gestion des blocs] creation du NodeBloc : %1 et ajour au NodeBloc : %2").arg(nodeBloc->getName()).arg(parent->getName());

    emit endResetModel();
    emit si_delete3Dbloc(bloc);

    return nodeBloc;
}

Bloc* ModeleBloc::deleteNodeBloc(NodeBloc* node){

    if(node != NULL && node != m_root)
    {
        emit beginResetModel();

        Bloc* bloc = node->getInitialBloc();

        node->getParent()->getListeFils()->append(bloc);
        bloc->setParent(node->getParent());

        int i = node->getListeFils()->count()-1;

        while((!node->getListeFils()->isEmpty()) && i>=0)
        {
            if(node->getListeFils()->at(i)->getType() == Bloc::NODE)
            {
                deleteNodeBloc((NodeBloc*)node->getListeFils()->at(i));
            }
            else
            {
                deleteBloc(node->getListeFils()->at(i));
            }

            i--;
        }

        delete node;

        emit endResetModel();

        //DEMANDER L'AFFICHAGE DU BLOC

        return bloc;
    }
}

void ModeleBloc::deleteBloc(Bloc* bloc){
    if(bloc != NULL)
    {
        int i = 0;

        while( (bloc->getParent()->getListeFils()->at(i) != bloc) && (i < bloc->getParent()->getListeFils()->count()) )
        {
            i++;
        }

        if(i < bloc->getParent()->getListeFils()->count())
        {
            bloc->getParent()->getListeFils()->remove(i);

            delete bloc;
         }
    }
}

Qt::ItemFlags ModeleBloc::flags (const QModelIndex  &index ) const{
    //return Qt::ItemIsUserCheckable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    return Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
}

void ModeleBloc::SetBlocName(Bloc * bloc, const QString name)
{
    bloc->setName(name);
    if(bloc == m_modeleMain->currentBloc)
        emit dataChanged(m_modeleMain->currentIndex, m_modeleMain->currentIndex);
}

bool ModeleBloc::setData (const QModelIndex &index, const QVariant &value, int role){
    Bloc *bloc = nodeFromIndex(index);

    if(role == Qt::EditRole){
        qDebug() << QObject::tr("[Gestion des blocs] changement du nom du bloc \"%1\" en \"%2\"").arg(bloc->getName()).arg(value.toString());
        bloc->setName(value.toString());
    }

    if(role == Qt::CheckStateRole)
    {
        //selectBloc(bloc, index);
        setBlocCheck(bloc, Qt::Checked);
    }
    return true;
}

void ModeleBloc::setBlocCheck(Bloc * bloc, Qt::CheckState state)
{
    if(state == Qt::Checked)
    {
        if(bloc != m_modeleMain->currentBloc)
        {
            if(m_modeleMain->currentBloc != NULL)
                m_modeleMain->currentBloc->setCheck(Qt::Unchecked);
            m_modeleMain->currentBloc = bloc;
            m_modeleMain->currentBloc->setCheck(Qt::Checked);

            emit dataChanged(m_modeleMain->currentIndex, m_modeleMain->currentIndex);

            emit si_selectBloc(bloc);
        }
    }
}

void ModeleBloc::setBlocEtat(Bloc * bloc, Bloc::Etat etat)
{
    bloc->setEtat(etat);
}
