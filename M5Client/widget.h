#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QDebug>




namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    QTcpSocket *m_socket;
    int connectHost(QByteArray arrInput,QByteArray &arrOutput);


private:
    Ui::Widget *ui;

private slots:

    void sendMesg();


};

#endif // WIDGET_H
