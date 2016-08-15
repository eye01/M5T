#ifndef DIALOGFORGETPASSWORD_H
#define DIALOGFORGETPASSWORD_H

#include <QWidget>
#include "Global.h"
namespace Ui {
class DialogForgetPassword;
}

class DialogForgetPassword : public QWidget
{
    Q_OBJECT

public:
    explicit DialogForgetPassword(QWidget *parent = 0);
    ~DialogForgetPassword();

private:
    Ui::DialogForgetPassword *ui;
private slots:
    void slotCheck();
    void slotCancel();
};

#endif // DIALOGFORGETPASSWORD_H
