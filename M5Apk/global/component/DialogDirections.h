#ifndef DIALOGDIRECTIONS_H
#define DIALOGDIRECTIONS_H

#include <QWidget>
#include "Global.h"
#include "ItemButton.h"
#include <QStandardItemModel>
#include <QHeaderView>
namespace Ui {
class DialogDirections;
}


class Cmodel :public QStandardItemModel
{
    Q_OBJECT
public :
    Cmodel(){}
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole )
    {
             if (role == Qt::TextAlignmentRole )
                 return Qt::AlignCenter ;
             else
                 return QAbstractItemModel::data(index, role);
    }
};


class DialogDirections : public QWidget
{
    Q_OBJECT

public:
    explicit DialogDirections(QWidget *parent = 0);
    ~DialogDirections();
    void showDialog(QString sInfo, QList<QStringList> dSIzeTable);
private:
    Ui::DialogDirections *ui;
    QList<QWidget*> m_listIcon;
    QList<ItemButton*> m_listBtn;
    void changePage(int iIdx);
    QStringList m_listTableColHeader;
    QStringList m_listTableRowHeader;
    QList<QStringList> m_dTableData;
private slots:
    void slotClicked();
public slots:
    void slotClose();
};

#endif // DIALOGDIRECTIONS_H
