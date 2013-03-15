#ifndef MODELEMAIN_H
#define MODELEMAIN_H

#include <QObject>

namespace OgreCNC{
    class ControleurMain;
    class VueMain;
    class NodeBloc;

    class ModeleMain : public QObject
    {
        Q_OBJECT
    public:
        explicit ModeleMain(QObject *parent = 0);
        ~ModeleMain();

        inline void setVue(VueMain * vue){
            m_vue = vue;
        }

        inline void setControleur(ControleurMain * controleur){
            m_controleur = controleur;
        }

        inline NodeBloc * getTravailBoc(){
            return m_RootTravailBlocs;
        }

    private:
        ControleurMain * m_controleur;
        VueMain * m_vue;

        NodeBloc * m_RootTravailBlocs;


    signals:

    public slots:

    };
}
#endif // MODELEMAIN_H
