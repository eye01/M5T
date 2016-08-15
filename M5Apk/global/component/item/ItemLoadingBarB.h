#ifndef ITEMLOADINGBARB_H
#define ITEMLOADINGBARB_H

#include <QWidget>
#include <QShowEvent>
namespace Ui {
class ItemLoadingBarB;
}

class ItemLoadingBarB : public QWidget
{
    Q_OBJECT

public:
    explicit ItemLoadingBarB(QWidget *parent = 0);
    
    ~ItemLoadingBarB();
    
    int value();
    
public slots:
    
    void setValue(int i);
    
private:
    
    void showEvent(QShowEvent *);
    
    int m_iBarWidthMax;
    
    int m_iNowValue;
    
private:
    Ui::ItemLoadingBarB *ui;
};

#endif // ITEMLOADINGBARB_H
