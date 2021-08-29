#include "frmmain.h"
#include <QApplication>
#include <QMessageBox>

class FlatterfogelApp : public QApplication {
public:
    FlatterfogelApp( int &argc, char *argv[] ) :
        QApplication( argc, argv)
    {};
    virtual ~FlatterfogelApp() {};
    bool notify( QObject *receiver, QEvent *e) {
        bool result = true;
        try {
            if( receiver && e )
                result = QApplication::notify( receiver, e );
            }
        catch ( int param ) {
            QMessageBox::warning( NULL, "Fehler",
                                QString("Fehler %1 ").arg(param) );
        }
        catch ( ... ) {
            QMessageBox::warning( NULL, "Fehler",
                                QString("Unbekannter Fehler aufgetreten ") );
        }
        return result;
    }
};

int main(int argc, char *argv[])
{
    FlatterfogelApp a(argc, argv);
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
