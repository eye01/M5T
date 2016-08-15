#ifndef ITEMIMAGE_H
#define ITEMIMAGE_H

#include <QWidget>
#include <QLabel>
#include <QResizeEvent>
#include "CThread.h"
class ItemImage : public QWidget
{
    Q_OBJECT
public:

    explicit ItemImage(QWidget *parent = 0);

    ~ItemImage();

    void setImageUrl(QString sUrl);

private:

    QLabel *m_lbBg;

    QLabel *m_lb;

    CThread *m_thread;

    void resizeEvent(QResizeEvent *);

signals:

public slots:
};

#endif // ITEMIMAGE_H
