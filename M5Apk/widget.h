#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QUrl>
#include <QResizeEvent>

//#include "Message.h"
#include <QPropertyAnimation>
#include "ItemButton.h"
#include "RNavigationWidget.h"
#include "LayerBlock.h"
#include "DialogMsg.h"
#include "QtCustomAndroidWebView.h"
#include <QMouseEvent>
#include <QResizeEvent>

namespace Ui {
class Widget;
}


namespace WidgetItem
{
    class BtnMask:public QWidget
    {
        Q_OBJECT
    public :
        explicit BtnMask(QWidget *parent =0 );

        void mouseReleaseEvent(QMouseEvent *);

        void resizeEvent(QResizeEvent *);

    private:

        QWidget *m_wBg;

    signals:

        void clicked();

    };
}


using namespace WidgetItem;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    typedef enum m_pageStatus{_stage,_option,_shoppingCar}_PageStatus;// ,m_pageStatus;
    _PageStatus m_pageStatus;

    bool m_bNeedNavigation;

    LayerBlock *m_layerBlock;

    BtnMask *m_wMask;

    DialogMsg *m_msg;

    QPropertyAnimation m_ani;

    void setSize();

    void slotOption(bool bIsShow=true);

    void slotCar(bool bIsShow=true);

private slots:

    void slotNavigationFinish();

    void slotFinish();

    void slotBacktoStage();

    void slotToStage(int iPage, int iItem);

public slots:

    void slotAniFinished();

    void slotNavigationClicked(int iIdx);

};

#endif // WIDGET_H
