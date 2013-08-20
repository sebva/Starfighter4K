#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include "include/enum/Enum.h"

#define SAT_INTERVAL 1500

class SoundEngine : public QObject
{
    Q_OBJECT
public:
    explicit SoundEngine(int soundEffectsVolume, int musicVolume, QObject *parent = 0);
    
signals:

private:
    Phonon::MediaObject *satMediaObject;
    Phonon::MediaObject *shootMediaObject;
    Phonon::MediaObject *snovaMediaObject;
    Phonon::MediaObject *musicMediaObject;

private slots:
    void musicFinished();
    
public slots:
    void playSound(Sounds);
    
};

#endif // SOUNDENGINE_H
