#include "GLOBAL.h"

GLOBAL *GLOBAL::m_pInstance = 0;
GLOBAL::GLOBAL()
{
    loadConfig();

}

void GLOBAL::log(QString st)
{
    signalLog(st);
}

void GLOBAL::loadConfig(QString sConfigPath)
{

    qDebug()<<sConfigPath;

    QSettings *configIniRead = new QSettings(sConfigPath, QSettings::IniFormat);

    g_config.sVersion=configIniRead->value("Version").toString();

    g_config.sTcpListenPort=configIniRead->value("TcpListenPort").toString();

    g_config.sMsSqlIp=configIniRead->value("DbIP").toString();

    g_config.sMsSqlPort=configIniRead->value("DbPort").toString();

    g_config.sMsSqlDbName=configIniRead->value("DbName").toString();

    g_config.sMsSqlDbUserName =configIniRead->value("DbUserName").toString();

    g_config.sMsSqlPassword=configIniRead->value("DbPassword").toString();

    QString sVer="M5Server Verison : %1";

    emit signalLog(sVer.arg(g_config.sVersion));

    emit signalLog("tpc listen port : "+g_config.sTcpListenPort);

    emit signalLog("db ip ::"+g_config.sMsSqlIp);

    emit signalLog("db port ::"+g_config.sMsSqlPort);

    emit signalLog("db name ::"+g_config.sMsSqlDbName);

    emit signalLog("db userName :: "+g_config.sMsSqlDbName);

    emit signalLog("db password :: "+g_config.sMsSqlPassword);

    delete configIniRead;

}

QString GLOBAL::getLocalIp()
{
    QString ip;

    QHostInfo host = QHostInfo::fromName(QHostInfo::localHostName());

    foreach (QHostAddress address, host.addresses())
        ip = address.toString();

    emit signalLog("local ip :: "+ip);

    return ip;
}
