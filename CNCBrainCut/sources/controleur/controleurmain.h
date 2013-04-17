#ifndef CONTROLEURMAIN_H
#define CONTROLEURMAIN_H

#include <QWidget>
#include <Ogre.h>

#include "../modele/bloc/bloc.h"

namespace OgreCNC {

    class VueMain;
    class ModeleMain;
    class ControleurBloc;
    class ControleurCut;
    class ModeleCut;
    class Bloc;
    class ControleurOgreWidget;
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

        void initControleurs();
        void initConnections();

    signals:
        void si_init_cut(ModeleCut* modeleCut);
        void si_select(Bloc * bloc);
        void si_updateOgreVue();

        void si_updateDimensionBloc(Bloc * bloc);
        void si_updatePostionBloc(Bloc * bloc);
        void si_updateCouleurBloc(Bloc* bloc);

    public slots:
        void sl_start_cut();
        void sl_update_cut();
        void sl_selectBloc(Bloc * bloc);
        void sl_abort_cut();
        void sl_vueEclate(double distance);
        Bloc * sl_blocFromOgreNode(Ogre::SceneNode * node);
        void sl_selectSegment(Ogre::ManualObject * segment);
        void sl_newNameForCurrentBloc(const QString &arg1);
        void sl_changeEtatForCurrentBloc(Bloc::Etat etat);
    };

}
#endif // CONTROLEURMAIN_H
