#ifndef LAYERLISTVIEW_H
#define LAYERLISTVIEW_H

#include <QWidget>
#include <QMouseEvent>
#include <QResizeEvent>


class LayerListView : public QWidget
{
    Q_OBJECT
public:
    explicit LayerListView(QWidget *parent = 0);
    void setBg(QString sStyleSheet);
    void addWidget(QWidget *w);
private:
    QWidget *m_wBg;
    QWidget *m_wContent;


    void resizeEvent(QResizeEvent *);

    int m_iOldPressY;
    int m_iOldContentY;
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

signals:

public slots:
};

#endif // LAYERLISTVIEW_H
