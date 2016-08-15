#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    m_socket=NULL;

    this->connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(sendMesg()));

}

Widget::~Widget()
{
    delete ui;
}


int Widget::connectHost(QByteArray arrInput,QByteArray &arrOutput)
{
    int iRe=0;
    if(m_socket!=NULL)
    {
        this->disconnect(m_socket);
        delete m_socket;
    }
    m_socket = new QTcpSocket(this);
    m_socket->connectToHost("192.168.0.113",60000);
   //m_socket->connectToHost("61.251.126.94",60000);
    if(m_socket->waitForConnected(10000))
    {

        qDebug() << "Connected!";
        m_socket->write(arrInput);
        //   m_socket->bytesWritten(inBuffer);
        m_socket->waitForBytesWritten(10000);
        qDebug()<<"socket written ok";
        m_socket->waitForReadyRead(10000);
        qDebug() << "Reading length: " << m_socket->bytesAvailable();
        arrOutput=m_socket->readAll();
        qDebug()<<"read out "<<arrOutput;
        m_socket->close();
    }
    else
    {
        qDebug() << "Not connected!";
        iRe= 999;
    }

    return iRe;
}



void Widget::sendMesg()
{
    qDebug()<<"clicked send msg";
    QByteArray in;
    in.append(ui->lineEdit->text());
    QByteArray out;
    connectHost(in,out);
    QString re=out;
    ui->textEdit->append(out);

}




