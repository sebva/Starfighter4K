#include "include/engine/SoundEngine.h"

SoundEngine::SoundEngine(int soundEffectsVolume, int musicVolume, QObject *parent) :
    QObject(parent)
{
    Phonon::AudioOutput *shootOutput = new Phonon::AudioOutput(Phonon::GameCategory, this);
    shootOutput->setVolume(soundEffectsVolume / 100.0);
    Phonon::AudioOutput *satOutput = new Phonon::AudioOutput(Phonon::GameCategory, this);
    satOutput->setVolume(soundEffectsVolume / 100.0);
    Phonon::AudioOutput *snovaOutput = new Phonon::AudioOutput(Phonon::GameCategory, this);
    snovaOutput->setVolume(soundEffectsVolume / 100.0);

    Phonon::AudioOutput *musicOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    musicOutput->setVolume(musicVolume / 100.0);

    shootMediaObject = new Phonon::MediaObject(this);
    shootMediaObject->setCurrentSource(Phonon::MediaSource(":/sounds/laser"));
    Phonon::createPath(shootMediaObject, shootOutput);

    satMediaObject = new Phonon::MediaObject(this);
    satMediaObject->setCurrentSource(Phonon::MediaSource(":/sounds/sat"));
    Phonon::createPath(satMediaObject, satOutput);

    snovaMediaObject = new Phonon::MediaObject(this);
    snovaMediaObject->setCurrentSource(Phonon::MediaSource(":/sounds/supernova"));
    Phonon::createPath(snovaMediaObject, snovaOutput);

    musicMediaObject = new Phonon::MediaObject(this);
    musicMediaObject->setCurrentSource(Phonon::MediaSource(":/sounds/bgmusic"));
    Phonon::createPath(musicMediaObject, musicOutput);
    connect(musicMediaObject, SIGNAL(aboutToFinish()), this, SLOT(musicFinished()));
    musicMediaObject->play();
}

void SoundEngine::playSound(Sounds toPlay)
{
    if(toPlay == SatelliteSound)
    {
        satMediaObject->seek(0);
        satMediaObject->play();
    }
    else if(toPlay == ShootSound)
    {
        shootMediaObject->seek(0);
        shootMediaObject->play();
    }
    else if(toPlay == SupernovaSound)
    {
        snovaMediaObject->seek(0);
        snovaMediaObject->play();
    }
}

void SoundEngine::musicFinished()
{
    musicMediaObject->enqueue(Phonon::MediaSource(":/sounds/bgmusic"));
}
