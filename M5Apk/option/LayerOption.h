#ifndef LAYEROPTION_H
#define LAYEROPTION_H

#include <QWidget>
#include "ItemOption.h"
#include <QResizeEvent>
#include <QDebug>
#include "Global.h"


class LayerOption : public QWidget
{
    Q_OBJECT

public:

    explicit LayerOption(QWidget *parent = 0);

    ~LayerOption();

    int m_iCount;

    int m_iIdx;

    void setTitleIcon(QStringList listUrl);

    void setText(QStringList listText);

    void setKeyValue(QStringList listKey, QStringList listValue);

    QString getCurrentKey();

    void setIcon(int iIdx,int iIconType=1);

    void cutHeight();


    QList<ItemOption*> m_listItem;

private:

    QStringList m_listKey;

    QStringList m_listValue;

    void resizeEvent(QResizeEvent *);

signals:

    void sendClick(int iIdx);

    void sendClick(QString sText);

    void sendClickedKey(QString);

    void sendClickedValue(QString);

private slots:

    void slotClicked();
};

#endif // LAYEROPTION_H
