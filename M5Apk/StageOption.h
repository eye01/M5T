#ifndef STAGEOPTION_H
#define STAGEOPTION_H

#include <QWidget>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include "CScrollWidgetV.h"
#include "ItemTopMenu.h"
#include "Global.h"
#include "ItemButton.h"
#include "LayerOption.h"
#include <QEventLoop>


#define HEADER1_KEY_INDEX_PAGE "999"
#define HEADER1_KEY_MEMBER "998"
#define HEADER1_KEY_ABOUT "997"

#define HEADER1_VALUE_INDEX_PAGE "近期活動"
#define HEADER1_VALUE_MEMBER "會員專區"
#define HEADER1_VALUE_ABOUT "關於"

class StageOption :public QWidget
{
    Q_OBJECT
public:
    explicit StageOption(QWidget *parent = 0);

    ~StageOption();

    void setMenu();

    void ini();

    void leaveStage();

    QLabel *m_lbTitle;

private:

    int m_iOldPressY;

    int m_iOldContentY;

    QString m_sTitleKey;

    ItemButton *m_btnLeft;

    QString m_sKey;

    LayerOption *m_layer0;

    LayerOption *m_layer1;

    QWidget *m_wTitle;

    QWidget *m_wContent;

    QPropertyAnimation m_ani;

    void keyPressEvent(QKeyEvent *e);

    void mousePressEvent(QMouseEvent *e);

    void mouseMoveEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *);

private slots:

    void slotClickedKey(QString sKey);

    void changeLayer(int iIdx=0);
};

#endif // STAGEOPTION_H
