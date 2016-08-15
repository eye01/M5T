#ifndef ITEMLINEEDIT_H
#define ITEMLINEEDIT_H


#include <QWidget>
#include <QDebug>
#include <QEvent>
#include <QLineEdit>
#include <QMouseEvent>
namespace Ui {
class ItemLineEdit;
}


namespace ItemLineComponent {

class CLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    CLineEdit(QWidget* parent=0);

    ~CLineEdit(){}
    void focusInEvent(QFocusEvent *e);



    void focusOutEvent(QFocusEvent *e);


    void mousePressEvent(QMouseEvent *e);

    void mouseMoveEvent(QMouseEvent *e);


    void mouseReleaseEvent(QMouseEvent *e);

    bool m_bOnlyRead;

private :

signals:

    void signalFocus(bool bIsFocus);
};

}


namespace LineEdit
{
enum _IconType{_nono=0,_normal,_password};
}

using namespace LineEdit;

class ItemLineEdit : public QWidget
{
    Q_OBJECT

public:

    explicit ItemLineEdit(QWidget *parent = 0);

    ~ItemLineEdit();

    ItemLineComponent::CLineEdit *m_cLineEdit;

    void setText(QString sText);

    QString text();

    void setIconImage(QString sUrl, QString sFocusUrl,_IconType nType);

    void setPlaceholderText(const QString &text);

    QLineEdit *g_edit;

private:

    Ui::ItemLineEdit *ui;

    _IconType m_nContype;

    void showEvent(QShowEvent *);

    QString m_sUrl;

    QString m_sFocusUrl;

private slots:

    void slotFocus(bool bIsFocusIn);

};








#endif // ITEMLINEEDIT_H
