#include <QtGui>

#include "vue3d.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    vue3d window;

    window.show();

    return app.exec();
}
