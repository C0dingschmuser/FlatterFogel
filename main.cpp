#include "frmmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*QSurfaceFormat f;
    f.setSwapInterval(0);
    QSurfaceFormat::setDefaultFormat(f);*/
    //qputenv("QT_USE_ANDROID_NATIVE_DIALOGS", "0");
    FrmMain w;
    w.showFullScreen();
    #ifdef QT_DEBUG
        w.showNormal();
    #endif
    return a.exec();
}
