#ifndef CONTROLEURMAIN_H
#define CONTROLEURMAIN_H

#include <QWidget>

namespace OgreCNC {

    class VueMain;
    class ModeleMain;
    class ControleurBloc;

    class ControleurMain : public QWidget
    {
        Q_OBJECT
    public:
        explicit ControleurMain(QWidget *parent = 0);

    private:
        VueMain * m_vue;
        ModeleMain * m_modele;

        ControleurBloc * m_gestionBloc;


        void initConnections();

    signals:

    public slots:

    };

}
#endif // CONTROLEURMAIN_H
