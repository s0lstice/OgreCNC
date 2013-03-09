#ifndef MODELEMAIN_H
#define MODELEMAIN_H

#include <QObject>

class ControleurMain;
class VueMain;

class ModeleMain : public QObject
{
    Q_OBJECT
public:
    explicit ModeleMain(QObject *parent = 0);
    
    inline void setVue(VueMain * vue){
        vue = vue;
    }

    inline void setControleur(ControleurMain * controleur){
        controleur = controleur;
    }

private:
    ControleurMain * controleur;
    VueMain * vue;

signals:
    
public slots:
    
};

#endif // MODELEMAIN_H
