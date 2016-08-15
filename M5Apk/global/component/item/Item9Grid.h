#ifndef ITEM9GRID_H
#define ITEM9GRID_H

#include <QWidget>
#include "ItemButton.h"
#include <QEvent>
namespace Ui {
class Item9Grid;
}

class Item9Grid : public ItemButton
{
    Q_OBJECT

public:
    explicit Item9Grid(QWidget *parent = 0);
    ~Item9Grid();

private:
    Ui::Item9Grid *ui;

    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

    void showEvent(QShowEvent *);

    void resizeEvent(QResizeEvent *);

};

#endif // ITEM9GRID_H
