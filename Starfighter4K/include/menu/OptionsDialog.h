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
    
private slots:
    void on_btnBack_clicked();
    void on_btnSave_clicked();

private:
    Ui::OptionsDialog *ui;
    void showKeys();
    int inSetting;
};

#endif // OPTIONSDIALOG_H
