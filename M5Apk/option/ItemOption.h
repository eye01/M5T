#ifndef ITEMOPTION_H
#define ITEMOPTION_H

#include <QWidget>
#include <QMouseEvent>
#include "Global.h"
#include "QVBoxLayout"
#include <QTimerEvent>
namespace Ui {
class ItemOption;
}

enum _OPTION_ICON_TYPE
{
    OPTION_ICON_NONE=0,
    OPTION_ICON_NEXT,
    OPTION_ICON_HOME,
    OPTION_ICON_CHECK
};

class ItemTouchCanvas : public QWidget
{
    // friend class ItemOption;
    Q_OBJECT
public:

    explicit ItemTouchCanvas(QWidget *parent = 0 );

private:

    QWidget *m_wBg;

    int m_iSec;

    void mousePressEvent(QMouseEvent *);

    void mouseReleaseEvent(QMouseEvent *);

    void timerEvent(QTimerEvent *);



};


class ItemOption : public QWidget
{
    friend class ItemTochVans;
    Q_OBJECT

public:
    explicit ItemOption(QWidget *parent = 0);
    ~ItemOption();
    int m_iIdx;
    ItemTouchCanvas *m_touch;
    void press();
    void release();
    void setText(QString sText);
    QString text();
    void setUse(bool bIsUse);
    void setIcon(int iEnum);
    void setTitleIcon(QString sUrl);
private:
    Ui::ItemOption *ui;
    QWidget *m_wDisable;
    QWidget *m_wBg;
    void resizeEvent(QResizeEvent *);

signals:

    void signalClicked();

};

#endif // ITEMOPTION_H
