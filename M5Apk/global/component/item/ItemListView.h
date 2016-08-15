#ifndef ITEMLISTVIEW_H
#define ITEMLISTVIEW_H

#include <QWidget>
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>
class ItemListView : public QWidget
{
    Q_OBJECT
public:

    explicit ItemListView(QWidget *parent = 0);

    ~ItemListView();

    void setListWidget(QList<QWidget*> list,int iLineH=0);

    void setBorderStyleSheet(const QString& styleSheet);

private:

       QWidget *m_wBg;

       QWidget *m_wContent;

       void resizeEvent(QResizeEvent *);

       void mousePressEvent(QMouseEvent *e);

       void mouseReleaseEvent(QMouseEvent *);

       void mouseMoveEvent(QMouseEvent *e);

       QPoint m_posPress;

       QPoint m_posOldContent;

signals:

public slots:
};

#endif // ITEMLISTVIEW_H
