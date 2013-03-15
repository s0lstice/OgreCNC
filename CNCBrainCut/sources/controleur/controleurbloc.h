#ifndef CONTROLEURBLOC_H
#define CONTROLEURBLOC_H

#include <QAbstractItemModel>
#include <Ogre.h>

namespace OgreCNC {

    class NodeBloc;
    class ControleurMain;
    class Bloc;

    class ControleurBloc : public QAbstractItemModel
    {
        Q_OBJECT
    private:
        NodeBloc * m_root;
        ControleurMain * m_controleur;

    public:
        explicit ControleurBloc(NodeBloc *rootBloc, QObject *parent = 0);
        ControleurBloc(QObject *parent = 0);

        void setRootNode(NodeBloc *rootBloc);
        QModelIndex index(int row, int column, const QModelIndex &parent) const;
        NodeBloc * nodeFromIndex(const QModelIndex &index) const;
        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QModelIndex parent(const QModelIndex &child) const;
        QVariant data(const QModelIndex &index, int role) const;
        void add(Bloc * bloc, const QModelIndex  &index);
        void creatBloc(const QModelIndex  &index = QModelIndex());
        void creatBloc(Ogre::Vector3 dimention, Ogre::Vector3 position, const QModelIndex  &index = QModelIndex());
        void creatNodeBloc(const QModelIndex  &index = QModelIndex());
        Qt::ItemFlags flags (const QModelIndex  &index ) const;
        bool setData (const QModelIndex &index, const QVariant &value, int role);
        void switchEtat(Bloc *blocs);

    signals:
        void ogreDrawBloc(Bloc * bloc);
    public slots:

    };
}
#endif // CONTROLEURBLOC_H
