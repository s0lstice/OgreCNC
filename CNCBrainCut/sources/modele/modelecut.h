#ifndef MODELECUT_H
#define MODELECUT_H

#include <QObject>
#include <QVector>

namespace OgreCNC {

class ModeleMain;

class ModeleCut : public QObject
{
    Q_OBJECT
public:
    ModeleMain * m_modeleMain;
    enum decoupe_CM {CLASSIQUE,MULTIPLE};
    enum directionDecoupe {X, Y, Z};
    enum positionPerte {GAUCHE, DROITE, CENTREE};
    bool isInUse;

    int nbFils; //nombre de blocs à créer

    /*Paramètres de la découpe*/
    decoupe_CM decoupeCM;
    directionDecoupe direction;
    positionPerte posPerte;
    qreal rayonChauffe;
    qreal distance;
    int nbBlocs;
private:

public:

    ModeleCut(QObject * parent);
    ModeleCut(decoupe_CM decCM,
                         directionDecoupe directionDec, positionPerte position,
                         qreal dist, int nombreBlocs, qreal rayon, QObject* parent);

};

}
#endif // MODELECUT_H
