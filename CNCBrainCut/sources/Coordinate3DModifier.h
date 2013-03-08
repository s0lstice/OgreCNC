#ifndef COORDINATE3DMODIFIER_H
#define COORDINATE3DMODIFIER_H

#include <QWidget>
#include <Ogre.h>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QHBoxLayout>

class Coordinate3DModifier : public QWidget
{
Q_OBJECT

public:
    Coordinate3DModifier(QWidget *parent=0)
    :QWidget(parent)
    {
        QLabel *lx = new QLabel("X:");
        sbx = new QDoubleSpinBox;
        sbx->setRange(-500, 500);

        QLabel *ly = new QLabel("Y:");
        sby = new QDoubleSpinBox;
        sby->setRange(-500, 500);

        QLabel *lz = new QLabel("Z:");
        sbz = new QDoubleSpinBox;
        sbz->setRange(-500, 500);

        QHBoxLayout *hblayout = new QHBoxLayout;
        hblayout->addWidget(lx);
        hblayout->addWidget(sbx);
        hblayout->addWidget(ly);
        hblayout->addWidget(sby);
        hblayout->addWidget(lz);
        hblayout->addWidget(sbz);
        hblayout->addStretch();

        setLayout(hblayout);

        connect(sbx, SIGNAL(valueChanged(double)), this, SLOT(onCoordinateChanged()));
        connect(sby, SIGNAL(valueChanged(double)), this, SLOT(onCoordinateChanged()));
        connect(sbz, SIGNAL(valueChanged(double)), this, SLOT(onCoordinateChanged()));
    }

public slots:
    void setNewCoordinate(const Ogre::Vector3 &coordinate)
    {
        blockSignals(true);
        sbx->setValue(coordinate.x);
        sby->setValue(coordinate.y);
        sbz->setValue(coordinate.z);
        blockSignals(false);
    }

signals:
    void coordinateChanged(const Ogre::Vector3 &coordinate);

private slots:
    void onCoordinateChanged()
    {
        Ogre::Vector3 newCoord(sbx->value(),
                               sby->value(),
                               sbz->value());
        emit coordinateChanged(newCoord);
    }

private:
    QDoubleSpinBox *sbx, *sby, *sbz;
};



#endif // COORDINATE3DMODIFIER_H
