#include "CFileManager.h"

static const QString sUpdata="UPDATE %1 SET SendDate='%2' WHERE Uuid='%3'";

CFileManager::CFileManager(QObject *parent) :
    QObject(parent)
{
    //../config/DongleK2Server.ini
    QSettings *configIniRead = new QSettings("../config/DongleK2Server.ini", QSettings::IniFormat);
    QString tmp=configIniRead->value("StoreNo","00000000").toString();
    m_sSourceId=COMMON().encodeData(tmp,8,"0",false);
    delete configIniRead;

    m_sDirPath=QApplication::applicationDirPath();
    m_sDirPath+="/ftp_files";
    if(!m_dir.exists(m_sDirPath))
    {
       m_dir.mkdir(m_sDirPath);
    }

}





CFileManager::~CFileManager()
{

}


void CFileManager::checkDir()
{
    m_sDirPath=QApplication::applicationDirPath();
    m_sDirPath+="/ftp_files/"+getDate();
    //確認是否存在
    if(!m_dir.exists(m_sDirPath))
    {
        m_dir.mkdir(m_sDirPath);
    }

    if(!m_dir.exists(m_sDirPath+"/in"))
    {
        m_dir.mkdir(m_sDirPath+"/in");
    }

    if(!m_dir.exists(m_sDirPath+"/out"))
    {
        m_dir.mkdir(m_sDirPath+"/out");
    }

    if(!m_dir.exists(m_sDirPath+"/report"))
    {
        m_dir.mkdir(m_sDirPath+"/report");
    }


}





void CFileManager::readFileToDb()
{

    checkDir();

}

void CFileManager::writeFileFromDb(QString tb,const QString &sDate)
{

    if(sDate=="")
        m_packFileDate=getDate(false);
    else
        m_packFileDate=COMMON().encodeData(sDate,8,"0");

    checkDir();

    QString sFileName(m_sDirPath+"/in/"+tb+"."+m_sSourceId+"."+getDate(true)+"01");
    m_file.setFileName(sFileName);
    m_file.open(QIODevice::WriteOnly);
    QByteArray sHead;
    QByteArray sEnd;

    QSqlQuery query;
    QStringList listUuid;
    QString sCmd="select * from %1 where InsertDate = '%2' and SendDate = '0'";
    int iCount=0;
    if(tb==_TableName::tableTxRecord)
    {

        QString tmp="HSTMC"+m_sSourceId+getDate(true)+getTime()+getSpace(403)+CR_LF;
        sHead.append(tmp);
        m_file.write(sHead);

        int iAmount=0;


        if(query.exec(sCmd.arg(tb).arg(m_packFileDate)))
        {
            QByteArray arrData;
            while(query.next())
            {
                listUuid.append(query.value(STMC_UUID).toString());
                arrData.append("D01");
                arrData.append(query.value(STMC_TXDATA).toString().replace(" ","0"));
                iAmount+=query.value(STMC_AMOUNT).toInt();

                arrData.append(getSpace(28));
                arrData.append(CR_LF);


                iCount++;
            }
            if(iCount>0)
                m_file.write(arrData);

        }



        sEnd.append("T");
        QString sCount=QString::number(iCount);
        sEnd.append(COMMON().encodeData(sCount,8,"0"));
        QString sAmount=QString::number(iAmount);
        sEnd.append(COMMON().encodeData(sAmount,15,"0"));
        sEnd.append(getSpace(406));
        sEnd.append(CR_LF);
        m_file.write(sEnd);


        for(int i=0;i<listUuid.length();i++)
        {
              query.exec(sUpdata.arg(tb).arg(getDate(true)).arg(listUuid.at(i)));
        }


    }

    else if(tb==_TableName::tableAddValueResend)
    {
        QString tmp="HTARC"+m_sSourceId+getDate(true)+getTime()+getSpace(115)+CR_LF;
        sHead.append(tmp);
        m_file.write(sHead);

        if(query.exec(sCmd.arg(tb).arg(m_packFileDate)))
        {
            QByteArray arrData;
            while(query.next())
            {
                listUuid.append(query.value(TARC_UUID).toString());
                arrData.append("D01");
                arrData.append(query.value(TARC_TXDATA).toString().replace(" ","0"));
                arrData.append(getSpace(9));
                arrData.append(CR_LF);
                iCount++;
            }
            if(iCount>0)
                m_file.write(arrData);

        }

        sEnd.append("T");
        QString sCount=QString::number(iCount);
        sEnd.append(COMMON().encodeData(sCount,8,"0"));
        sEnd.append(getSpace(133));
        sEnd.append(CR_LF);
        m_file.write(sEnd);

        for(int i=0;i<listUuid.length();i++)
        {
              query.exec(sUpdata.arg(tb).arg(getDate(true)).arg(listUuid.at(i)));
        }
    }

    else if(tb==_TableName::tableLockCard)
    {


            QString tmp="HTLRC"+m_sSourceId+getDate(true)+getTime()+getSpace(187)+CR_LF;
            sHead.append(tmp);
            m_file.write(sHead);

            if(query.exec(sCmd.arg(tb).arg(m_packFileDate)))
            {
                QByteArray arrData;
                while(query.next())
                {
                    listUuid.append(query.value(TARC_UUID).toString());
                    arrData.append("D01");
                    arrData.append(query.value(TLRC_TXDATA).toString().replace(" ","0"));
                    arrData.append(getSpace(14));
                    arrData.append(CR_LF);
                    iCount++;
                }
                if(iCount>0)
                    m_file.write(arrData);

            }

            sEnd.append("T");
            QString sCount=QString::number(iCount);
            sEnd.append(COMMON().encodeData(sCount,8,"0"));
            sEnd.append(getSpace(205));
            sEnd.append(CR_LF);
            m_file.write(sEnd);

            for(int i=0;i<listUuid.length();i++)
            {
                  query.exec(sUpdata.arg(tb).arg(getDate(true)).arg(listUuid.at(0)));
            }

    }


    else if(tb==_TableName::tmList)
    {
        QString tmp="HMRHT"+m_sSourceId+getDate(true)+getTime()+getSpace(239)+CR_LF;
        sHead.append(tmp);
        m_file.write(sHead);

        if(query.exec("select * from TMList"))
        {
            QByteArray arrData;
            while(query.next())
            {
                arrData.append("D01");
                arrData.append(COMMON().encodeData(query.value(TM_LIST_TM_LOC_ID).toString(),10,"0"));
                arrData.append(COMMON().encodeData(query.value(TM_LIST_ChineseDescription).toString(),20," ",false));
                arrData.append(COMMON().encodeData(query.value(TM_LIST_TEL_1).toString(),20," ",false));
                arrData.append(COMMON().encodeData(query.value(TM_LIST_TEL_2).toString(),20," ",false));
                arrData.append(COMMON().encodeData(query.value(TM_LIST_FAX).toString(),20," ",false));
                arrData.append(COMMON().encodeData(query.value(TM_LIST_Address).toString(),80," ",false));
                arrData.append(COMMON().encodeData(query.value(TM_LIST_ZIPCode).toString(),5," ",false));
                arrData.append(COMMON().encodeData(query.value(TM_LIST_ValidFlag).toString(),1,"0"));
                arrData.append(COMMON().encodeData(query.value(TM_LIST_EnableDate).toString(),8," "));
                arrData.append(COMMON().encodeData(query.value(TM_LIST_DisableDate).toString(),8," "));
                arrData.append(getSpace(71));
                arrData.append(CR_LF);
                iCount++;
            }
            if(iCount>0)
                m_file.write(arrData);

        }


        sEnd.append("T");
        QString sCount=QString::number(iCount);
        sEnd.append(COMMON().encodeData(sCount,8,"0"));
        sEnd.append(getSpace(257));
        sEnd.append(CR_LF);
        m_file.write(sEnd);
    }

    else
    {
        qDebug()<<"DGK2Server :: What's this ?  your table  : "<<tb;
    }
    m_file.close();

    qDebug()<<"DGK2Server :: page file : "<<tb<<"  OK !";
}









QString CFileManager::getSpace(int iNum)
{
    QString sRe;

    for(int i=0;i<iNum;i++)
    {
        sRe.append(" ");
    }

    return sRe;
}

QString CFileManager::getDate(QString st)
{
    return st;
}


QString CFileManager::getDate(bool bIsNowDay)
{
    QString sRe;
    QString sNowDay;
    QString sPreDay;

    QDateTime dt;
    QDate date;
    dt.setDate(date.currentDate());
    sNowDay=dt.toString("yyyyMMdd");
    sPreDay=dt.addDays(-1).toString("yyyyMMdd");

    if(bIsNowDay)
        sRe=sNowDay;
    else
        sRe=sPreDay;
    return sRe;
}


QString CFileManager::getTime()
{
    QString sRe;
    QDateTime dt;
    QDate date;
    QTime time;
    dt.setDate(date.currentDate());
    dt.setTime(time.currentTime());
    sRe=dt.toString("hhmmss");

    return sRe;
}
