#include "include/menu/SetKeyDialog.h"
#include "include/stable.h"

SetKeyDialog::SetKeyDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint)
{
    QLabel *label = new QLabel(tr("Please press the key now"), this);
    label->setStyleSheet("font-size:13pt;");

    label->setAlignment(Qt::AlignCenter);
    setFixedSize(400,30);
}

void SetKeyDialog::keyPressEvent(QKeyEvent *event)
{
    Qt::Key key = (Qt::Key)event->key();
    if(key != Qt::Key_Escape && key != Qt::Key_F12)
    {
        emit keySelected(key);
        close();
    }
}
