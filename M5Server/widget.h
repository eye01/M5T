#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QDebug>
#include "CListenClient.h"
#include "CSqlServer.h"
#include "CFileManager.h"
#include "../../common/Common.h"
#include "../global/GLOBAL.h"
#include <QApplication>

#include <QTimer>
namespace Ui {
class Widget;
}
#if(QT_VER_MAJ<=4)
    //Qt4  shit.. C++的限制 函數指標實体， 只好static 或擺全域
    void customMessageHandlerQt4(QtMsgType type, const char *msg);
#else
    //Qt5
    void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);
#endif

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void ini(){}

    void appendDebugMsg(const QString &msg);

private:
    void setting();
    QTimer *m_timer;
 //   CFileManager m_fileManager;
CListenClient *listenClient;
CSqlServer *m_sql;
public slots:
    void slotTest(QString st);
    void slotDebug(QString st);

    void slotSchedule();
    void on_checkTargetDate_clicked();
    void on_btnClear_clicked();
    void on_btnSendFile_clicked();
    void on_btnGetFile_clicked();
    void on_btnPackFile_clicked();

    //防手殘 動到Server
    void on_checkBoxLock_clicked();
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
