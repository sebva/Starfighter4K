#include "include/menu/MainDialog.h"
#include "include/config/Define.h"


#include "include/engine/DemoEngine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    if (translator.load(QLocale::system(), "starfighter", "_", ":/strings/", ".qm"))
    {
        app.installTranslator(&translator);
    }

    MainDialog md;

    QDir dir(SOUNDS_DIR);
    if(!dir.exists())
        QMessageBox::information(&md, QObject::tr("Sounds not found"), QObject::tr("The sounds directory was not found. The game will work as it should, but no sound will be played."));

    md.show();

    return app.exec();
}
