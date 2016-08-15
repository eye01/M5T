#include "CSqlServer.h"

CSqlServer *CSqlServer::m_pInstance = 0;


CSqlServer::CSqlServer(QObject *parent):QThread(parent)
{

}


bool CSqlServer::openDb()
{
    bool bRe=false;
        
    m_db = QSqlDatabase::addDatabase("QMYSQL",Global().g_config.sMsSqlDbName);
    connect(this,SIGNAL(signalLog(QString)),&Global(),SIGNAL(signalLog(QString)));
    m_db.setDatabaseName("M5");

    m_db.setPort(Global().g_config.sMsSqlPort.toInt());
    qDebug()<<"db prot "<<Global().g_config.sMsSqlPort.toInt();
    m_db.setHostName(Global().g_config.sMsSqlIp);
    qDebug()<<"host name"<<Global().g_config.sMsSqlIp;
    m_db.setUserName(Global().g_config.sMsSqlDbUserName);
    qDebug()<<"db name"<<Global().g_config.sMsSqlDbUserName;
    m_db.setPassword(Global().g_config.sMsSqlPassword);

    emit signalLog("db host name: "+Global().g_config.sMsSqlIp);

    emit signalLog("db port: "+Global().g_config.sMsSqlPort);


    emit signalLog("db User name: "+Global().g_config.sMsSqlDbUserName);
    bRe=m_db.open();
    
    if(!bRe)
    {
        emit signalLog("ERROR: "+QSqlError(m_db.lastError()).text());
        qDebug()<<"ERROR: "+QSqlError(m_db.lastError()).text();
    }
    else
    {
        emit signalLog("sql open Ok");
    }

    qDebug()<<"open db is "<<bRe;
        
    QSqlQuery query(m_db);
    QString dbCmd="SELECT  * FROM table1";
    query.exec(dbCmd);

    QString sRe;

    while(query.next())
    {
        sRe+=query.value(1).toString();
        sRe+=CLIP_M;
        sRe+=query.value(2).toString();
        sRe+=CLIP_E;
    }
    
    qDebug()<<sRe;
    
    return bRe;
}

QString CSqlServer::returnClient(QString sTable, QString sColunm)
{
    QSqlQuery query(m_db);
    QString dbCmd="SELECT  * FROM table1";
    query.exec(dbCmd);
    
    QString sRe;
    sRe=ACTION_GET_TABLE1;
    sRe+=CLIP_FN;


    while(query.next())
    {
        sRe+=query.value(1).toString();
        sRe+=CLIP_M;
        sRe+=query.value(2).toString();
        sRe+=CLIP_E;
    }
    
    return sRe;
    
}

