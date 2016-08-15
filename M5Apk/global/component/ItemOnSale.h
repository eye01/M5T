#ifndef ITEMONSALE_H
#define ITEMONSALE_H

#include <QWidget>

namespace Ui {
class ItemOnSale;
}

class ItemOnSale : public QWidget
{
    Q_OBJECT

public:
    explicit ItemOnSale(QWidget *parent = 0);
    ~ItemOnSale();
    void setCost(QString sCost,QString sOnSale);
    QString cost();
private:
    Ui::ItemOnSale *ui;
};

#endif // ITEMONSALE_H
