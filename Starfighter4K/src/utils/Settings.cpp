#include "include/utils/Settings.h"

#ifdef Q_WS_MAC
    #define ORGANIZATION "ch.hearc"
#else
    #define ORGANIZATION "HE-Arc"
#endif

#define APPLICATION "Starfighter"

#define P1_NAME "p1n"
#define P2_NAME "p2n"
#define PLAYERS_CONTROLS "controls"
#define MUSIC_VOLUME "mvol"
#define SOUNDEFFECTS_VOLUME "sevol"

const int kDefaultMusicVolume = 50;
const int kDefaultSoundEffectsVolume = 50;
QString kDefaultPlayerOneName = QObject::tr("Player 1");
QString kDefaultPlayerTwoName = QObject::tr("Player 2");

Settings::Settings()
{
    qse = new QSettings(ORGANIZATION, APPLICATION);
}

Settings::~Settings()
{
    delete qse;
}

Settings& Settings::getGlobalSettings()
{
    static Settings globalSettings;

    return globalSettings;
}

int Settings::musicVolume()
{
    bool ok;
    int volume = qse->value(MUSIC_VOLUME, kDefaultMusicVolume).toInt(&ok);
    return ok ? volume : kDefaultMusicVolume;
}

int Settings::soundEffectsVolume()
{
    bool ok;
    int volume = qse->value(SOUNDEFFECTS_VOLUME, kDefaultSoundEffectsVolume).toInt(&ok);
    return ok ? volume : kDefaultSoundEffectsVolume;
}

QString Settings::playerOneName()
{
    return qse->value(P1_NAME, kDefaultPlayerOneName).toString();
}

QString Settings::playerTwoName()
{
    return qse->value(P2_NAME, kDefaultPlayerTwoName).toString();
}

void Settings::setMusicVolume(int volume)
{
    qse->setValue(MUSIC_VOLUME, volume);
}

void Settings::setSoundEffectsVolume(int volume)
{
    qse->setValue(SOUNDEFFECTS_VOLUME, volume);
}

void Settings::setPlayerOneName(QString name)
{
    qse->setValue(P1_NAME, name);
}

void Settings::setPlayerTwoName(QString name)
{
    qse->setValue(P2_NAME, name);
}
