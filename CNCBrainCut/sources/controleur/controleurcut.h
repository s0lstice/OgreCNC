#ifndef CONTROLEURCUT_H
#define CONTROLEURCUT_H

#include <QObject>

namespace OgreCNC {

    class ModeleCut;
    class ControleurMain;
    class NodeBloc;
    class Bloc;

    class ControleurCut : public QObject
    {
        Q_OBJECT
    private:
        ModeleCut* m_modeleCut;
        ControleurMain* controleurMain;
        NodeBloc* noeud;
    public:
        ControleurCut(ModeleCut* modele, QObject *parent = 0);
        void update_cut();
        void deleteBlocsCrees();

    };
}

#endif // CONTROLEURCUT_H
