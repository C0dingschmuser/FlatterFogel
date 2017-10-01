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
    return a.exec();
}
