#ifndef VUEMAIN_H
#define VUEMAIN_H

#include <QMainWindow>
#include <QMdiArea>

namespace Ui {
class VueMain;
}

namespace OgreCNC {

    class vue3d;
    class ControleurMain;
    class ModeleMain;
    class OgreWidget;
    class Bloc;

    class VueMain : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit VueMain(QWidget *parent = 0);
        ~VueMain();

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
        OgreWidget * m_Ogre3d;

        Ui::VueMain *ui;

        bool event(QEvent * e);

        void initConnections();

    signals:
        void si_select(int id);

    public slots:
        void sl_createBloc(Bloc * bloc);
        void sl_selectBloc(Bloc * bloc);
    };
}
#endif // VUEMAIN_H
