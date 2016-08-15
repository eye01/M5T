#ifndef STAGEPRODUCTLIST_H
#define STAGEPRODUCTLIST_H

#include <QWidget>
#include <QShowEvent>
#include "Global.h"
#include "LayerOption.h"
#include <QPropertyAnimation>
#include "LayerZoomView.h"
#include "ItemZooming.h"
#include <QKeyEvent>
#include <QEventLoop>
#include "Layer4View.h"
#include "ItemButton.h"
#include "ItemChangeBtn.h"

namespace Ui {
class StageProductList;
}

class StageProductList : public QWidget
{
    Q_OBJECT

public:
    explicit StageProductList(QWidget *parent = 0);

    ~StageProductList();

    void ini(int iKeyIdx=0);

    bool m_bIsBanner;

    InterfaceView* currentView();

private:

    Ui::StageProductList *ui;

    enum{_zoomView=0,_4View};

    int m_viewMode ;

    int m_preViewMode;

    int m_iSec;

    QString m_sKey;

    QStringList m_listPid;

    QStringList m_listType;

    QStringList m_listName;

    QStringList m_listImageUrl;

    InterfaceView *m_view[2];

    LayerOption *m_LayerTitleOption;

    QPropertyAnimation m_ani;

    QPropertyAnimation m_aniBtnTop;

    QPropertyAnimation m_aniSubMenu;

    ItemButton *m_btnTop;

    ItemChangeBtn *m_btnChangeView;

    ItemButton *m_btnOptionMask;

    QList<ItemZooming*> m_listItemZoom;

    void getViewData();

    QList<QStringList> m_dData;

    void keyPressEvent(QKeyEvent *e);

    void timerEvent(QTimerEvent *);

    void setItemData(QStringList listName, QStringList listUrl);

    void setSubMenuView(bool bIsView);

signals:

private slots:
    void slotChangeView(bool bIsEnable=-1);
    //title left is option
    void slotClickedLeft();
    //title right is shopping car
    void slotClickedRight();
    //title cent is title opiton
    void slotClickedCent();
    //title option select
    void slotTitleOptionClickedKey(QString);
    //zoom mode clicked item
    void slotItemZoomClicked(int iIdx);
    //to top button clicked
    void slotBtnTopClicked();
    //view idx change
    void slotBtnTopAniShow(int iIdx);

};

#endif // STAGEPRODUCTLIST_H
