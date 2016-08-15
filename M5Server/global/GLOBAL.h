#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QSettings>
#include <QObject>
#include <QHostInfo>
#include <QDebug>
#include <QApplication>

#define Global GLOBAL::Instance

#define INI_PATH QApplication::applicationDirPath() +"/M5Server.ini"


namespace M5TcpServer {
struct Config
{
    QString sVersion;
    QString sTcpListenPort;
    QString sMsSqlIp;
    QString sMsSqlDbName;
    QString sMsSqlPort;
    QString sMsSqlDbUserName;
    QString sMsSqlPassword;

};}


using namespace M5TcpServer;

class GLOBAL :public QObject
{
    Q_OBJECT
public:
    static GLOBAL& Instance( )
    {
        if(m_pInstance==0)
            m_pInstance=new GLOBAL();
        return *m_pInstance;
    }

    Config g_config;

    void loadConfig(QString sConfigPath=INI_PATH);

    QString getLocalIp();

private:
    GLOBAL( );

    static GLOBAL* m_pInstance;
public :
    void log(QString st);
signals:

    void signalLog(QString st);

    void signalDebug(QString st);
};

#endif // GLOBAL_H
