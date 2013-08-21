#include "include/engine/SoundEngine.h"

SoundEngine::SoundEngine(int soundEffectsVolume, int musicVolume, QObject *parent) :
    QObject(parent)
{
    shootMediaPlayer = new QMediaPlayer(this, QMediaPlayer::LowLatency);
    shootMediaPlayer->setVolume(soundEffectsVolume);
    shootMediaPlayer->setMedia(QMediaContent(QUrl("qrc:///sounds/laser")));

    satMediaPlayer = new QMediaPlayer(this, QMediaPlayer::LowLatency);
    satMediaPlayer->setVolume(soundEffectsVolume);
    satMediaPlayer->setMedia(QMediaContent(QUrl("qrc:///sounds/sat")));

    snovaMediaPlayer = new QMediaPlayer(this, QMediaPlayer::LowLatency);
    snovaMediaPlayer->setVolume(soundEffectsVolume);
    snovaMediaPlayer->setMedia(QMediaContent(QUrl("qrc:///sounds/supernova")));

    musicMediaPlayer = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
    musicMediaPlayer->setVolume(musicVolume);
    musicMediaPlayer->setMedia(QMediaContent(QUrl("qrc:///sounds/bgmusic")));

    connect(musicMediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(musicChangedStatus(QMediaPlayer::MediaStatus)));
    musicMediaPlayer->play();
}

void SoundEngine::playSound(Sounds toPlay)
{
    if(toPlay == SatelliteSound)
    {
        satMediaPlayer->setPosition(0);
        satMediaPlayer->play();
    }
    else if(toPlay == ShootSound)
    {
        shootMediaPlayer->setPosition(0);
        shootMediaPlayer->play();
    }
    else if(toPlay == SupernovaSound)
    {
        snovaMediaPlayer->setPosition(0);
        snovaMediaPlayer->play();
    }
}

void SoundEngine::musicChangedStatus(QMediaPlayer::MediaStatus status)
{
    if(status == QMediaPlayer::EndOfMedia)
    {
        musicMediaPlayer->setPosition(0);
        musicMediaPlayer->play();
    }
}
