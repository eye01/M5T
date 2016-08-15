#ifndef INTERFACEVIEW_H
#define INTERFACEVIEW_H

#include <QWidget>


class InterfaceView : public QWidget
{
    Q_OBJECT
public:
    explicit InterfaceView(QWidget *parent = 0);

    virtual void setBackground(QString){}

    virtual void setOption(QWidget *){}

    virtual void setItemWidget(QList<QWidget *>, int = 0 , int = -1 , int = -1 ){}

    virtual void setItemWidget(QStringList,QStringList){}

    virtual void goIdx(int){}

    virtual void setSlice(int,QString ,QString){}

    virtual int length(){return -1;}

signals:

    void clicked(int iIdx);

    void changeIdx(int iIdx);
public slots:
};

#endif // INTERFACEVIEW_H
