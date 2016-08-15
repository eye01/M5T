#ifndef LAYERBLOCK_H
#define LAYERBLOCK_H

#include <QWidget>
#include "Global.h"
#include <QMovie>
#include <QShowEvent>
#include "ItemLoadingBarA.h"
namespace Ui {
class LayerBlock;
}

class LayerBlock : public QWidget
{
    Q_OBJECT

public:
    explicit LayerBlock(QWidget *parent = 0);

    ~LayerBlock();

    void setCanView(bool bIsCan);

private:
    Ui::LayerBlock *ui;

    void showEvent(QShowEvent *);

    void hideEvent(QHideEvent *);

    void timerEvent(QTimerEvent *);

    int m_iSec;
public slots:

    void slotBlockFlag(bool bIsBlock,bool bIsCanView=true);
};

#endif // LAYERBLOCK_H
