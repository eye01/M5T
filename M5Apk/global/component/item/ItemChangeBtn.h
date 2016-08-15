#ifndef ITEMCHANGEBTN_H
#define ITEMCHANGEBTN_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QDebug>
class ItemChangeBtn : public QWidget
{
    Q_OBJECT
public:
    explicit ItemChangeBtn(QWidget *parent = 0);

    void setIconRes(QSize sz,QStringList listRes);

    void setIdxEnable(bool bIsEnable=true);

private :
    int m_iSec;

    int m_bIsEnable;

    bool m_bLock;

    QLabel *m_lb;

    QStringList m_listRes;

    void mouseReleaseEvent(QMouseEvent *);

    void timerEvent(QTimerEvent *);


signals:

    void clicked(bool bIsEnable);

public slots:
};

#endif // ITEMCHANGEBTN_H
