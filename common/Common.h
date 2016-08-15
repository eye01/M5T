#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QDebug>

#define CLIP_FN ":"

#define CLIP_M ","

#define CLIP_E ";"

#define ACTION_GET_TABLE1 "3001"

#define COMMON Common::Instance


class Common
{
public:

   static Common& Instance( )
   {
       if(m_pInstance==0)
           m_pInstance=new Common();
       return *m_pInstance;
   }

   QString encodeData(const QString &sData,int iSize,const QString sFill=" ",bool bIsAddLeft=true)
   {
       QString sRe;

       if(iSize<sData.length())
       {
           sRe=sRe.rightJustified(iSize,' ');
           return sRe;
       }

       if(bIsAddLeft)
           sRe=sData.rightJustified(iSize,*sFill.data());
       else
           sRe=sData.leftJustified(iSize,*sFill.data());
       return sRe;
   }


private:
   Common(){}
   static Common* m_pInstance;

};




#endif // COMMON_H
