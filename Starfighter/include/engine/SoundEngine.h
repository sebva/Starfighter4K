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
    QMediaPlayer *satMediaPlayer;
    QMediaPlayer *shootMediaPlayer;
    QMediaPlayer *snovaMediaPlayer;
    QMediaPlayer *musicMediaPlayer;

private slots:
    void musicChangedStatus(QMediaPlayer::MediaStatus status);
    
public slots:
    void playSound(Sounds);
    
};

#endif // SOUNDENGINE_H
