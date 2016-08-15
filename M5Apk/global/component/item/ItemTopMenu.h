#ifndef ITEMTOPMENU_H
#define ITEMTOPMENU_H

#include <QWidget>

#include <QEvent>
#include "Global.h"

#include <QStackedWidget>
#include "ItemButton.h"
namespace Ui {
class ItemTopMenu;
}


enum STACK_CENT{_HAS_ICON=0,_NO_ICON};

enum STACK_ICON{_TO_DOWN=0,_TO_UP=1,_HIDE=2};


class ItemTopMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ItemTopMenu(QWidget *parent = 0);
    ~ItemTopMenu();
    ItemButton *m_btnLeft;
    ItemButton *m_btnRight;
    ItemButton *m_btn;
    void setTitleName(QString sName);
    QString titleName();
    void setIconFlag(STACK_ICON iType);
    STACK_ICON getIconFlag();
    void setCentFlag(STACK_CENT iType);
    STACK_CENT getCentFlag();

private:
    void showEvent(QShowEvent *);
signals:
    void signalClickedLeft();
    void signalClickedCent();
    void signalClickedRight();
private slots:
  //  void slotOpen();


private:
    Ui::ItemTopMenu *ui;


};

#endif // ITEMTOPMENU_H
