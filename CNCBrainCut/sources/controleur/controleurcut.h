#ifndef CONTROLEURCUT_H
#define CONTROLEURCUT_H

#include <QObject>

namespace OgreCNC {

class ModeleCut;
class ControleurMain;

class ControleurCut : public QObject
{
    Q_OBJECT
private:
    ModeleCut* m_modeleCut;
    ControleurMain* controleurMain;
public:
    ControleurCut(ModeleCut* modele, QObject *parent = 0);
    void update_cut();

};
}

#endif // CONTROLEURCUT_H
