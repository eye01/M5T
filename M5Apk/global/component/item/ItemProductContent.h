#ifndef ITEMPRODUCTCONTENT_H
#define ITEMPRODUCTCONTENT_H

#include <QWidget>
#include <QResizeEvent>
namespace Ui {
class ItemProductContent;
}


class ItemProductContent : public QWidget
{
    Q_OBJECT

public:
    explicit ItemProductContent(QWidget *parent = 0);
    ~ItemProductContent();
    void setItemData(QString sUrl, QString sLbTitle, QString sLb0="", QString sLb1="", QString sLb2="");
    void resizeEvent(QResizeEvent *);

private:
    Ui::ItemProductContent *ui;
};

#endif // ITEMPRODUCTCONTENT_H
