#ifndef DIALOGMSG_H
#define DIALOGMSG_H

#include <QWidget>
#include "Global.h"
namespace Ui {
class DialogMsg;
}

class DialogMsg : public QWidget
{
    Q_OBJECT

public:
    explicit DialogMsg(QWidget *parent = 0);
    ~DialogMsg();

private:
    Ui::DialogMsg *ui;
    int m_iAfterCloseGoStage;
private slots:
    void on_btnBottom_clicked();
public slots:
    void slotShowMsg(bool bIsShow, QString st, int iStageIdx);
};

#endif // DIALOGMSG_H
