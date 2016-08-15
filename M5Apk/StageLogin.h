#ifndef STAGELOGIN_H
#define STAGELOGIN_H

#include <QWidget>
#include "Global.h"
#include "DialogForgetPassword.h"
namespace Ui {
class StageLogin;
}

class StageLogin : public QWidget
{
    Q_OBJECT

public:
    explicit StageLogin(QWidget *parent = 0);

    ~StageLogin();

private:

    Ui::StageLogin *ui;

    DialogForgetPassword *m_layerForgetPassword;

    void keyPressEvent(QKeyEvent *e);

private slots:

    void slotClickedLeft();

    void slotClickedJoin();

    void slotClickedLogin();

    void slotForget();
};

#endif // STAGELOGIN_H
