#ifndef CFILEMANAGER_H
#define CFILEMANAGER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QDate>
#include <QSettings>
#include <QtSql>

//#include "../common/Common.h"
#include "../../common/Common.h"
//#include "../../../common/Common.h"

#define CR_LF "\r\n"




enum
{
    STMC_SID=0,
    STMC_UUID,
    STMC_INSERT_DATE,
    STMC_INSERT_TIME,
    STMC_TXDATA,
    STMC_SEND_DATE,
    STMC_AMOUNT,
    STMC_REPORT_DATE,
    STMC_MSG_TYPE,
    STMC_DEVICE_ID,
    STMC_TXN_DATE,
    STMC_PROCESSING_CODE,

};

enum
{
    TARC_SID=0,
    TARC_UUID,
    TARC_INSERT_DATE,
    TARC_INSERT_TIME,
    TARC_TXDATA,
    TARC_SEND_DATE,
    TARC_REPORT_DATE

};

enum
{
    TLRC_SID=0,
    TLRC_UUID,
    TLRC_INSERT_DATE,
    TLRC_INSERT_TIME,
    TLRC_TXDATA,
    TLRC_SEND_DATE,
    TLRC_REPORT_DATE

};


enum
{
    TM_LIST_TM_LOC_ID=0,
    TM_LIST_ChineseDescription,
    TM_LIST_TEL_1,
    TM_LIST_TEL_2,
    TM_LIST_FAX,
    TM_LIST_Address,
    TM_LIST_ZIPCode,
    TM_LIST_ValidFlag,
    TM_LIST_EnableDate,
    TM_LIST_DisableDate
};

struct CTRNC
{
    QString ProcessingCode;
    QString MsgType;
    QString DeviceId;
    QString TxnDate;
    QString EZCardCheckDate;
    QString AppropriationData;
};



class CFileManager : public QObject
{
    Q_OBJECT
public:
    explicit CFileManager(QObject *parent = 0);
    ~CFileManager();

    //------------------------------------------------------------------------------
    /**
     * @brief checkDir 確認資料夾是否存在
     */
    void checkDir();

    //------------------------------------------------------------------------------
    /**
     * @brief readFileToDb 從MS SQL 讀資料準備包檔
     */
    void readFileToDb();

    //------------------------------------------------------------------------------
    /**
     * @brief writeFileFromDb 從指定TABLE取出包檔資料
     * @param tb
     * @param sDate
     */
    void writeFileFromDb(QString tb,const QString &sDate="");


//    void checkAmount()
//    {
//       QString d="000000016241011840254130601000002540130428100000-20000000020000030000000280825799024059D2FE00FE9B04345408000140D1CD600000000232D2040001734CEFB5E1D62D5A00464F7900464F79012C0100180100020000B9100DFE0000FE00000000000000000000000000000000464F7900464F790000010000ECFFFF0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000004000000019201201410071519550019000001";
//       bool bNeedDecodeLeft=false;
//       bool bNeedDecodeRight=false;
//       for(int i=0;i<8;i++)
//       {
//           if(d.at(i)=="-")
//           {
//               d.at(43+i)="0";
//               bNeedDecodeLeft=true;
//           }

//           if(d[67+i]=="-1")
//           {
//               d[67+i]="0";
//               bNeedDecodeRight=true;
//           }

//           if(bNeedDecodeLeft)
//               d[43]=="-";

//           if(bNeedDecodeRight)
//               d[67]=="-";
//       }

//       qDebug()<<d;

//    }




    void decodeTRNC(QString sDate="")
    {
        if(sDate=="")
            sDate=getDate();

        QList<CTRNC> m_list;
        int iLine=0;

        QString sPath;
        QFile file("TRNC.74100000");

        file.open(QIODevice::ReadOnly);
        QTextStream streamread(&file);
        //讀
        //一次讀一行的寫法
        while(!streamread.atEnd())
        {
            if(iLine==0)
            {
                iLine++;
                //把這行qDebug拿掉程式就會嚴重資料錯亂喔!!
                qDebug()<<"funbox :: read file"<<streamread.readLine();
                continue;
            }

            QString sLineData=streamread.readLine().left(420);


            if(!streamread.atEnd())
            {

                CTRNC trnc;

                trnc.ProcessingCode=sLineData.mid(78,6);
                trnc.MsgType=sLineData.mid(84,2);
                trnc.DeviceId=sLineData.mid(88,8);
                trnc.TxnDate=sLineData.mid(98,8);
                trnc.EZCardCheckDate=sLineData.mid(402,8);
                trnc.AppropriationData=sLineData.mid(410,8);

                //                qDebug()<<"PROCESSING  :  "<<trnc.ProcessingCode;
                //                qDebug()<<"MSG : "<<trnc.MsgType;
                //                qDebug()<<"Device : "<<trnc.DeviceId;
                //                qDebug()<<"TxnDate : "<<trnc.TxnDate;
                //                qDebug()<<"EZCARDE CHECK : "<<trnc.EZCardCheckDate;
                //                qDebug()<<"Appropriation : "<<trnc.AppropriationData;
                m_list.append(trnc);

            }
            iLine++;
        }






    }



    //------------------------------------------------------------------------------
    /**
     * @brief getSpace 包檔所指定格式
     * @param iNum
     * @return
     */
    QString getSpace(int iNum);

    //------------------------------------------------------------------------------
    /**
     * @brief getDate 指定包檔所需日期格式
     * @param st
     * @return
     */
    QString getDate(QString st);

    //------------------------------------------------------------------------------
    QString getDate(bool bIsNowDay=true);

    //------------------------------------------------------------------------------
    QString getTime();


private:
    QFile m_file;
    QDir m_dir;
    QString m_sDirPath;
    QString m_sSourceId;
    QString m_packFileDate;
signals:

public slots:



};

#endif // CFILEMANAGER_H
