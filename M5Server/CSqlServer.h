#ifndef CSQLSERVER_H
#define CSQLSERVER_H

#include <QThread>
#include <QtSql/QtSql>
#include "global/GLOBAL.h"
#include "../../common/Common.h"

//#define M5SqlServer CSqlServer::Instance

class CSqlServer : public QThread
{
        Q_OBJECT
public:
        CSqlServer(QObject *parent = 0);
    ~CSqlServer(){m_db.close();}

    static CSqlServer& Instance()
    {
        if(m_pInstance==0)
            m_pInstance=new CSqlServer();
        return *m_pInstance;
    }

  void run(){}

  bool openDb();

  QString returnClient(QString sTable="tbale1",QString sColunm="aa");

   void closeDB(){m_db.close();}


signals:
   void signalLog(QString sLog);

  //QString test(){}
private:
    QSqlDatabase m_db;



    static CSqlServer* m_pInstance;
};

#endif // CSQLSERVER_H
