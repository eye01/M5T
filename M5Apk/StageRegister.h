#ifndef STAGEREGISTER_H
#define STAGEREGISTER_H

#include <QWidget>
#include "Global.h"
#include <QEvent>
#include <QJsonObject>
namespace Ui {
class StageRegister;
}

class StageRegister : public QWidget
{
    Q_OBJECT

public:
    explicit StageRegister(QWidget *parent = 0);

    ~StageRegister();


private:

    Ui::StageRegister *ui;

    void keyPressEvent(QKeyEvent *e);


private slots:

    void slotClickedLeft();

    void slotClickedSend();
};

#endif // STAGEREGISTER_H
