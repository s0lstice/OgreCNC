#include <QtGui>

#include "controleur/controleurmain.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    OgreCNC::ControleurMain controleur;

    return app.exec();
}
