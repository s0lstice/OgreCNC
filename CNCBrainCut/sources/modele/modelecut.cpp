#include "modelecut.h"
#include "modelemain.h"
using namespace OgreCNC;
ModeleCut::ModeleCut(QObject * parent) : QObject(parent)
{
    m_modeleMain = qobject_cast<ModeleMain *>(parent);
    isInUse = false;
    origineDecoupe = QVector<qreal>();
    origineDecoupe.append(0.0);
    origineDecoupe.append(0.0);
    origineDecoupe.append(0.0);
    distance = 0.0;
    nbBlocs = 0;
    decoupeHV = HORIZONTALE;
    decoupeCM = CLASSIQUE;
    direction = X;
    posPerte = CENTREE;
}


ModeleCut::ModeleCut(decoupe_HV decHV, decoupe_CM decCM,
                     directionDecoupe directionDec, positionPerte position,
                     QVector<qreal> origine, qreal dist, int nombreBlocs, QObject *parent) : QObject(parent)
{
    m_modeleMain = qobject_cast<ModeleMain *>(parent);
    isInUse = false;
    decoupeHV = decHV;
    decoupeCM = decCM;
    direction = directionDec;
    posPerte = position;
    origineDecoupe = origine;
    distance = dist;
    nbBlocs = nombreBlocs;
}
