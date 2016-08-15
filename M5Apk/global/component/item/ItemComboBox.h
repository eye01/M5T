#ifndef ITEMCOMBOBOX_H
#define ITEMCOMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include "Global.h"
#include <QListView>
#include <QStyledItemDelegate>
namespace Ui {
class ItemComboBox;
}

class ItemComboBox : public QWidget
{
    Q_OBJECT

public:
    explicit ItemComboBox(QWidget *parent = 0);

    ~ItemComboBox();

    void setTitleName(QString sText);

    QString text();

    QComboBox *m_cb;

private:
    Ui::ItemComboBox *ui;
};

#endif // ITEMCOMBOBOX_H
