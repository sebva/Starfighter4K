#include "include/menu/MainDialog.h"
#include "include/config/Define.h"
#include "include/menu/ConnectDialog.h"
#include "include/menu/KinectWindow.h"
#include "include/engine/DisplayEngine.h"
#include "include/engine/GameEngine.h"


#include "include/engine/DemoEngine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    if (translator.load(QLocale::system(), "starfighter", "_", ":/strings/", ".qm"))
        app.installTranslator(&translator);

    //* Old keyboard/mouse menus
    MainDialog md;
    md.show();
    //*/

    QDir dir(SOUNDS_DIR);
    if(!dir.exists())
        QMessageBox::information(&md, QObject::tr("Sounds not found"), QObject::tr("The sounds directory was not found. The game will work as it should, but no sound will be played."));

    /* New Kinect menus
    WiimoteEngine we;
    ConnectDialog cd(&we);
    if(cd.exec() == QDialog::Accepted)
    {
       KinectWindow kw;
       kw.showFullScreen();
    }
    //*/

    return app.exec();
}
