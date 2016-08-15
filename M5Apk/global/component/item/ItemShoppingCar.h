#ifndef ITEMSHOPPINGCAR_H
#define ITEMSHOPPINGCAR_H

#include <QWidget>
#include "Global.h"

namespace Ui {
class ItemShoppingCar;
}



class ItemShoppingCar : public QWidget
{
    Q_OBJECT

public:
    explicit ItemShoppingCar(QWidget *parent = 0);
    ~ItemShoppingCar();
   // void setCarItem(DataShoppingCar cData);
    void setCarItem(DataGetCar cData);
    int cost();

private:
    Ui::ItemShoppingCar *ui;
    QString m_sId;
    QString m_sCarItemId;
    int  m_iCost;
    int m_iNowCount;
    int m_iMaxCount;

signals:
    void signalGetCar();
    void signalChange(int i);
private slots:
    void slotClickedAdd();
    void slotClickedSub();
};

#endif // ITEMSHOPPINGCAR_H
