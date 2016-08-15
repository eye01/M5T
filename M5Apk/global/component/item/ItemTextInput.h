#ifndef ITEMTEXTINPUT_H
#define ITEMTEXTINPUT_H

#include <QWidget>
#include "ItemLineEdit.h"

namespace Ui {
class ItemTextInput;
}

class ItemTextInput : public QWidget
{
    Q_OBJECT

public:

    explicit ItemTextInput(QWidget *parent = 0);

    ~ItemTextInput();

    void setTitleName(QString sText);

    void setErrorText(QString sText);

    void setPlaceholderText(QString sText);

    void setOnlyRead(bool bOnlyRead=true);

    QLineEdit *g_lineEidt;

    void setText(QString sText);

    QString text();

private:

    Ui::ItemTextInput *ui;

};

#endif // ITEMTEXTINPUT_H
