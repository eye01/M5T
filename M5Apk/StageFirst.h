#ifndef STAGEFIRST_H
#define STAGEFIRST_H

#include <QWidget>
#include <QResizeEvent>
#include <QShowEvent>
#include "Global.h"
#include "CScrollWidgetV.h"
#include <QMouseEvent>
#include <QTimerEvent>
#include "ItemButton.h"
namespace Ui {
class StageFirst;
}

class StageFirst : public QWidget
{
    Q_OBJECT

public:
    explicit StageFirst(QWidget *parent = 0);

    ~StageFirst();

    void setAd();

private:
    Ui::StageFirst *ui;

    CScrollWidgetV *m_wScrollV;

    void showEvent(QShowEvent *);

    void keyPressEvent(QKeyEvent *e);

    ItemButton *m_btnTest;

    void getImage(QString sUrl, QLabel *lb);

    QList<QLabel*> m_listImage;


signals:

private slots:

    void btnClicked(int iIdx);

    void slotShowOption();

    void slotTest();
};

#endif // STAGEFIRST_H
