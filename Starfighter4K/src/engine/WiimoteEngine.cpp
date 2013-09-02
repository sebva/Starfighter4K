#include "include/engine/WiimoteEngine.h"
#include "include/config/Define.h"

#include <lib/wiiuse/wiiuse.h>

const std::array<int, 13> WiimoteEngine::kWiimotesButtons = {WIIMOTE_BUTTON_A,
        WIIMOTE_BUTTON_B,
        WIIMOTE_BUTTON_MINUS,
        WIIMOTE_BUTTON_PLUS,
        WIIMOTE_BUTTON_HOME,
        WIIMOTE_BUTTON_ALL,
        WIIMOTE_BUTTON_DOWN,
        WIIMOTE_BUTTON_LEFT,
        WIIMOTE_BUTTON_ONE,
        WIIMOTE_BUTTON_RIGHT,
        WIIMOTE_BUTTON_TWO,
        WIIMOTE_BUTTON_UNKNOWN,
        WIIMOTE_BUTTON_UP};

WiimoteEngine::WiimoteEngine(QObject *parent):QThread(parent),isRunning(true)
{
    wiimotes = wiiuse_init(kNbWiimotes);
    startTimer(REFRESH);
}

WiimoteEngine::~WiimoteEngine()
{
    quit();
    wait();
    disconnect();
}

int WiimoteEngine::findWiimotes()
{
    return wiiuse_find(wiimotes, kNbWiimotes, kTimeout);
}

bool WiimoteEngine::connectWiimotes()
{
    if (wiiuse_connect(wiimotes, kNbWiimotes))
    {
        wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_1);
        wiiuse_set_leds(wiimotes[1], WIIMOTE_LED_2);
        return true;
    }
    else
    {
        qWarning() << "No wiimotes are connected";
        return false;
    }
}

void WiimoteEngine::reconnectWiimotes()
{
    connectWiimotes();
    startAccel();
}

void WiimoteEngine::disconnect()
{
    isRunning = false;
    wiiuse_cleanup(wiimotes, kNbWiimotes);
}

void WiimoteEngine::rumble(int wiimote, int msec)
{
    wiiuse_rumble(wiimotes[wiimote], 1);
    rumble_order.enqueue(wiimote);
    QTimer::singleShot(msec, this, SLOT(unrumble()));
}

void WiimoteEngine::unrumble(int wiimote)
{
    wiiuse_rumble(wiimotes[wiimote], 0);
}

void WiimoteEngine::startAccel()
{
    for(int i = 0; i < kNbWiimotes; ++i)
        wiiuse_motion_sensing(wiimotes[i], 1);
}

void WiimoteEngine::stopAccel()
{
    for(int i = 0; i < kNbWiimotes; ++i)
        wiiuse_motion_sensing(wiimotes[i], 0);
}

void WiimoteEngine::unrumble()
{
    wiiuse_rumble(wiimotes[rumble_order.dequeue()], 0);
}

void WiimoteEngine::timerEvent(QTimerEvent *)
{
    for(int i = 0; i < kNbWiimotes; ++i)
        emit orientation(i,-atan2((wiimotes[i]->gforce.y) ,sqrt(pow(wiimotes[i]->gforce.x,2) + pow(wiimotes[i]->gforce.z,2)))*180.0/M_PI);
}

void WiimoteEngine::run()
{
    while (isRunning) {
            if (wiiuse_poll(wiimotes, kNbWiimotes)) {
                for (int i = 0; i < kNbWiimotes; ++i)
                {
                    wiimote_t* wm = wiimotes[i];
                    switch (wm->event)
                    {
                        case WIIUSE_EVENT:
                            for(auto it = kWiimotesButtons.begin(); it != kWiimotesButtons.end(); ++it)
                                if(IS_JUST_PRESSED(wm, *it))
                                    emit button_pressed(*it, i);
                                else if(*it == WIIMOTE_BUTTON_UP || *it == WIIMOTE_BUTTON_DOWN)
                                    if(IS_RELEASED(wm, *it))
                                        emit button_released(*it, i);

                            break;

                        case WIIUSE_STATUS:
                            break;

                        case WIIUSE_DISCONNECT:
                        case WIIUSE_UNEXPECTED_DISCONNECT:
                            emit wiimotes_disconnected();
                            break;

                        case WIIUSE_READ_DATA:
                            break;

                        case WIIUSE_CLASSIC_CTRL_INSERTED:
                            break;

                        case WIIUSE_NUNCHUK_REMOVED:
                        case WIIUSE_CLASSIC_CTRL_REMOVED:
                        case WIIUSE_GUITAR_HERO_3_CTRL_REMOVED:
                            break;

                        default:
                            break;
                    }
                }
            }
    }
}

void WiimoteEngine::stop()
{
    isRunning = false;
}

qreal WiimoteEngine::getBattery(int wiimote) const
{
    return wiimotes[wiimote]->battery_level*100.0;
}
