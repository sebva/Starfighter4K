#include "include/menu/MainDialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    if (translator.load(QLocale::system(), "starfighter", "_", ":/strings/", ".qm"))
    {
        app.installTranslator(&translator);
    }

    MainDialog md;
    md.show();

    return app.exec();
}
