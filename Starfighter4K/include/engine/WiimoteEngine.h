#ifndef WIIMOTE_H
#define WIIMOTE_H

#include <QThread>

#include <array>
#include <QQueue>

class wiimote_t;

class WiimoteEngine : public QThread
{
    Q_OBJECT

public:
    WiimoteEngine(QObject * parent = 0);
    ~WiimoteEngine();

    int findWiimotes();
    bool connectWiimotes();
    void reconnectWiimotes();
    void disconnect();

    void rumble(int wiimote, int msec);
    void unrumble(int wiimote);

    void startAccel();
    void stopAccel();

    void run();
    void stop();

    qreal getBattery(int wiimote) const;

protected:
    void timerEvent(QTimerEvent *event);

signals:
    void button_pressed(int button, int wiimote);
    void button_released(int button, int wiimote);
    void orientation(int wiimote, qreal pitch);
    void wiimotes_disconnected();

private slots:
    void unrumble();

private:
    static const int kNbWiimotes = 2;
    static const int kTimeout = 5;
    static const std::array<int, 13> kWiimotesButtons;
    bool isRunning;

    wiimote_t** wiimotes;
    QQueue<int> rumble_order;//Only enough for little sound seq (with 200ms it's perfect). For more, use an array of QQueue/QStack

};

#endif // WIIMOTE_H
