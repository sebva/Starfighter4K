#include "include/engine/SoundEngine.h"
#include "include/config/Define.h"

SoundEngine::SoundEngine(int soundEffectsVolume, int musicVolume, QObject *parent) :
    QObject(parent)
{
    QString sndDir(SOUNDS_DIR);

    shootMediaPlayer = new QMediaPlayer(this, QMediaPlayer::LowLatency);
    shootMediaPlayer->setVolume(soundEffectsVolume);
    shootMediaPlayer->setMedia(QMediaContent(QUrl::fromLocalFile(sndDir + SHOOT_SOUND)));

    satMediaPlayer = new QMediaPlayer(this, QMediaPlayer::LowLatency);
    satMediaPlayer->setVolume(soundEffectsVolume);
    satMediaPlayer->setMedia(QMediaContent(QUrl::fromLocalFile(sndDir + SAT_SOUND)));

    snovaMediaPlayer = new QMediaPlayer(this, QMediaPlayer::LowLatency);
    snovaMediaPlayer->setVolume(soundEffectsVolume);
    snovaMediaPlayer->setMedia(QMediaContent(QUrl::fromLocalFile(sndDir + SUPERNOVA_SOUND)));

	antigravityMediaPlayer = new QMediaPlayer(this, QMediaPlayer::LowLatency);
	antigravityMediaPlayer->setVolume(soundEffectsVolume);
	antigravityMediaPlayer->setMedia(QMediaContent(QUrl::fromLocalFile(sndDir + ANTIGRAVITY_SOUND)));
	
	freezeMediaPlayer = new QMediaPlayer(this, QMediaPlayer::LowLatency);
	freezeMediaPlayer->setVolume(soundEffectsVolume);
	freezeMediaPlayer->setMedia(QMediaContent(QUrl::fromLocalFile(sndDir + FREEZE_SOUND)));

	trackingMediaPlayer = new QMediaPlayer(this, QMediaPlayer::LowLatency);
	trackingMediaPlayer->setVolume(soundEffectsVolume);
	trackingMediaPlayer->setMedia(QMediaContent(QUrl::fromLocalFile(sndDir + TRACKING_SOUND)));

    musicMediaPlayer = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
    musicMediaPlayer->setVolume(musicVolume);
    QMediaPlaylist* pl = new QMediaPlaylist(this);
    pl->addMedia(QMediaContent(QUrl::fromLocalFile(sndDir + GAME_MUSIC)));
    pl->setPlaybackMode(QMediaPlaylist::Loop);
    musicMediaPlayer->setPlaylist(pl);
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
	else if(toPlay == TrackingSound)
	{
		trackingMediaPlayer->setPosition(0);
		trackingMediaPlayer->play();
	}
	else if(toPlay == AntiGravitySound)
	{
		antigravityMediaPlayer->setPosition(0);
		antigravityMediaPlayer->play();
	}
	else if(toPlay == FreezeSound)
	{
		freezeMediaPlayer->setPosition(0);
		freezeMediaPlayer->play();
	}
}

void SoundEngine::stopSound(Sounds toPlay)
{
	if(toPlay == SatelliteSound)
		satMediaPlayer->stop();
	else if(toPlay == ShootSound)
		shootMediaPlayer->stop();
	else if(toPlay == SupernovaSound)
		snovaMediaPlayer->stop();
	else if(toPlay == TrackingSound)
		trackingMediaPlayer->stop();
	else if(toPlay == AntiGravitySound)
		antigravityMediaPlayer->stop();
	else if(toPlay == FreezeSound)
		freezeMediaPlayer->stop();
}