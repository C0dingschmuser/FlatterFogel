#include "frmmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*QSurfaceFormat f;
    f.setSwapInterval(0);
    QSurfaceFormat::setDefaultFormat(f);*/
    FrmMain w;
    w.show();
    w.showFullScreen();
    #ifdef QT_DEBUG
        w.showNormal();
    #endif
    return a.exec();
}
