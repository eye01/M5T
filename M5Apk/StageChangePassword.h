#ifndef STAGECHANGEPASSWORD_H
#define STAGECHANGEPASSWORD_H

#include <QWidget>
#include "Global.h"
namespace Ui {
class StageChangePassword;
}

class StageChangePassword : public QWidget
{
    Q_OBJECT

public:

    explicit StageChangePassword(QWidget *parent = 0);

    ~StageChangePassword();

private:

    Ui::StageChangePassword *ui;

    void showEvent(QShowEvent *);

    void keyPressEvent(QKeyEvent *e);
private slots:

    void slotClickedLeft();

    void slotCheck();

};

#endif // STAGECHANGEPASSWORD_H
