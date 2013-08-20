#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include "include/enum/Enum.h"

class MainDialog;
class QLabel;

namespace Ui {
class NewGameDialog;
}

class NewGameDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewGameDialog(QWidget *parent = 0);
    ~NewGameDialog();

private slots:
    void on_btnBack_clicked();
    void on_btnStart_clicked();

    void on_cbbGametype_currentIndexChanged(int index);

    void on_cbbP1ship_currentIndexChanged(int index);
    void on_cbbP2ship_currentIndexChanged(int index);

private:
    Ui::NewGameDialog *ui;
    MainDialog *md;
    void setPixmapForLabelWithSpaceshipType(SpaceshipType sType, QLabel *lbl);
    void updateSpaceshipsStats();

    int resMax;
    int speedMax;
};

#endif // NEWGAMEDIALOG_H
