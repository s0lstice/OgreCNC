#ifndef CONTROLEURMAIN_H
#define CONTROLEURMAIN_H

#include <QWidget>

namespace OgreCNC {

    class VueMain;
    class ModeleMain;
    class ControleurBloc;
    class ControleurCut;
    class ModeleCut;
    class Bloc;

    class ControleurMain : public QWidget
    {
        Q_OBJECT
    public:
        explicit ControleurMain(QWidget *parent = 0);

        inline ControleurBloc * getModeleBlocs(){
            return m_gestionBloc;
        }

    private:
        VueMain * m_vue;
        ModeleMain * m_modele;

        ControleurBloc * m_gestionBloc;

        ControleurCut * m_controleurCut;

        void initControleur();
        void initConnections();

    signals:
        void si_init_cut(ModeleCut* modeleCut);
        void si_select(Bloc * bloc);

    public slots:
        void sl_start_cut();
        void sl_update_cut();
        void sl_select(int id);
        void sl_abort_cut();

    };

}
#endif // CONTROLEURMAIN_H
