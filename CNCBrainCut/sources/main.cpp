#include <QtGui>

#include "controleur/controleurmain.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    OgreCNC::ControleurMain controleur;

    /*vue3d window3d;
    window3d.show();*/

    return app.exec();
}
