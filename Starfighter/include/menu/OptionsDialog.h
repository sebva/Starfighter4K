#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include "include/enum/Enum.h"

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit OptionsDialog(QWidget *parent = 0);
    ~OptionsDialog();

public slots:
    void setKey(Qt::Key);
    
private slots:
    void on_btnBack_clicked();
    void on_btnSave_clicked();
    void keyChange(int);

private:
    Ui::OptionsDialog *ui;
    QButtonGroup *btgKeys;
    QMap<Action, Qt::Key> *controls;
    void showKeys();
    int inSetting;
};

#endif // OPTIONSDIALOG_H
