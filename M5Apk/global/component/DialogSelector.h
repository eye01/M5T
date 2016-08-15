#ifndef DIALOGSELECTOR_H
#define DIALOGSELECTOR_H

#include <QWidget>
#include <QDebug>
#include <QResizeEvent>
#include "ItemButton.h"
#include "Global.h"
namespace Ui {
class DialogSelector;
}
enum{_typeColor,_typeSize};
class DialogSelector : public QWidget
{
    Q_OBJECT

public:
    explicit DialogSelector(QWidget *parent = 0);
    ~DialogSelector();
    void showDialog(int iType, QString sTitleName, int iNowIdx, QList<QWidget *> &listContent,QList<bool> isEndable);
private:
    Ui::DialogSelector *ui;
    void visiableCheckIcon(int iIdx);
    QList<QWidget*> m_listCheck;
    QList<ItemButton*> m_listBtn;
    QList<QWidget*> m_listContent;
    void resizeEvent(QResizeEvent *);
    int m_iType;
    int m_iIdx;
signals:
    void signalClose(int iType,int iIdxSelect);
private slots:
    void slotClicked();
};

#endif // DIALOGSELECTOR_H
