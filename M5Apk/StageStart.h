#ifndef STAGESTART_H
#define STAGESTART_H

#include <QWidget>
#include <QResizeEvent>
#include <QTimerEvent>
#include <QShowEvent>
#include <QDebug>
#include "Global.h"
#include "LayerLoading.h"
#include <QLabel>
#define INTO_USE_MSEC 2000

namespace Ui {
class StageStart;
}

class StageStart : public QWidget
{
    Q_OBJECT

public:
    explicit StageStart(QWidget *parent = 0);

    ~StageStart();

    void ini();

private:
    Ui::StageStart *ui;

    QWidget *m_wLogoBg;

    QWidget *m_wLogo;

    int m_iTimeFlag;

    LayerLoading *m_layeyLoading;

    void timerEvent(QTimerEvent *);

    void showEvent(QShowEvent *);

    void checkNetworkAndVer();

signals:

    void signalIntoFinish();

};

#endif // STAGESTART_H
