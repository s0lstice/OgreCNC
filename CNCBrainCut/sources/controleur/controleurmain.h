#ifndef CONTROLEURMAIN_H
#define CONTROLEURMAIN_H

#include <QWidget>

class VueMain;
class ModeleMain;

class ControleurMain : public QWidget
{
    Q_OBJECT
public:
    explicit ControleurMain(QWidget *parent = 0);
    
private:
    VueMain * vue;
    ModeleMain * modele;

signals:

public slots:
    
};

#endif // CONTROLEURMAIN_H
