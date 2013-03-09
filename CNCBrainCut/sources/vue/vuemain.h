#ifndef VUEMAIN_H
#define VUEMAIN_H

#include <QMainWindow>
#include <QMdiArea>

class vue3d;
class ControleurMain;
class ModeleMain;

class VueMain : public QMainWindow
{
    Q_OBJECT
public:
    explicit VueMain(QWidget *parent = 0);

    inline void setModele(ModeleMain * modele){
        modele = modele;
    }

    inline void setControleur(ControleurMain * controleur){
        controleur = controleur;
    }

private:
    ControleurMain * controleur;
    ModeleMain * modele;

    QMdiArea * mdi;
    vue3d * window3d;
    
signals:
    
public slots:
    
};

#endif // VUEMAIN_H
