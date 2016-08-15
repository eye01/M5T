#ifndef ITEMZOOMING_H
#define ITEMZOOMING_H

#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QResizeEvent>
#include "Global.h"
#include <QMouseEvent>

#include "ItemImage.h"

class ItemZooming : public QWidget
{
    Q_OBJECT

public:
    explicit ItemZooming(QWidget *parent = 0);

    ~ItemZooming();

    void setHeightInit(int iMinH, int iMaxH=-1);

    void setItemText(QString sText);

    void setItemImage(QString sUrl);

    QString m_sUrl;

    QLabel  *m_lbTitle;

    QWidget *m_wSlice2;
    // QLabel *m_lbBg;
    ItemImage *m_wContent;

    int m_iMinH;

    int m_iMaxH;

private:

    QPoint m_wOldP;

    QWidget *m_wSlice;

    QWidget *m_wBorder;
    void resizeEvent(QResizeEvent *);

};

#endif // ITEMZOOMING_H
