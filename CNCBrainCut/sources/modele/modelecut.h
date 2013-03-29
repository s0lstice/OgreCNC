#ifndef MODELECUT_H
#define MODELECUT_H

#include <QObject>
#include <QVector>

namespace OgreCNC {

class ModeleCut : public QObject
{
    Q_OBJECT
public:
    enum decoupe_HV {HORIZONTALE,VERTICALE};
    enum decoupe_CM {CLASSIQUE,MULTIPLE};
    enum directionDecoupe {X, Y, Z};
    enum positionPerte {GAUCHE, DROITE, CENTREE};
    bool isInUse;
    /*Paramètres de la découpe*/
    decoupe_HV decoupeHV;
    decoupe_CM decoupeCM;
    directionDecoupe direction;
    positionPerte posPerte;
    QVector<qreal> origineDecoupe;
    qreal distance;
    int nbBlocs;
private:

public:
    ModeleCut();
    ModeleCut(decoupe_HV decHV, decoupe_CM decCM,
                         directionDecoupe directionDec, positionPerte position,
                         QVector<qreal> origine, qreal dist, int nombreBlocs);
};

}
#endif // MODELECUT_H
