#ifndef SETKEYDIALOG_H
#define SETKEYDIALOG_H

class SetKeyDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SetKeyDialog(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *);

signals:
    void keySelected(Qt::Key key);
    
};

#endif // SETKEYDIALOG_H
