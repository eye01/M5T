#ifndef ITEMBORDERLABEL_H
#define ITEMBORDERLABEL_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class ItemBorderLabel;
}

namespace BorderType
{
  typedef enum
    {
        _none=0,
        _type_black=1,
        _type_whrite,
        _type_orange
    }_Type;

}

class ItemBorderLabel : public QWidget
{
    Q_OBJECT

public:
    explicit ItemBorderLabel(QWidget *parent = 0);

    ~ItemBorderLabel();

    void setBorder(BorderType::_Type type);

    void setBorder(QStringList listRes);

    void setText(QString st);

    QString text();

private:

    Ui::ItemBorderLabel *ui;

    QList<QWidget*> m_listBorder;
};

#endif // ITEMBORDERLABEL_H
