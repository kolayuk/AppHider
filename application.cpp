#include "application.h"
#include <localizer.h>
#include <QDeclarativeContext>
#include <QStringList>
#include <QDebug>
#include <const.h>
#include <apparc.h>
#include <APACMDLN.H>
#include <apgtask.h>
#include <eikenv.h>
#include <Utils.h>
#ifdef Q_OS_SYMBIAN
#include <apgcli.h>
#include <centralrepository.h>
#endif
#include <QDir>
#include <starterclient.h>

Application::Application(QmlApplicationViewer& v,QObject *parent) :
    QObject(parent), viewer(v)
{
    CEikonEnv::Static()->SetSystem(ETrue);
   int lang=16;
#ifdef Q_OS_SYMBIAN
   lang=User::Language();
#endif
   loc=new Localizer(lang,this);

   QFile file("launches");
    if (file.exists())
    {
        file.open (QFile::ReadOnly);
        QTextStream stream ( &file );
        stream.setCodec("UTF-16");
        launches=stream.readLine().toInt();
        file.close(); // when your done.
    }
    else launches=0;
   qDebug()<<"launches"<<launches;
   qDebug()<<"main thread: "<<RThread().Id().Id();
   CRepository* paramcr=CRepository::NewL(TUid::Uid(0x101F8847));
   TBuf<1024> uidsinparams;
   paramcr->Get(10,uidsinparams);
   delete paramcr;
   uidsinparams.UpperCase();
#ifdef Q_OS_SYMBIAN
   RApaLsSession AppSession;
   AppSession.Connect();
   TApaAppInfo appInfo;
   AppSession.GetAllApps();
   TBuf<255> UidTxt;
   while (AppSession.GetNextApp(appInfo)==KErrNone)
   {
       HBufC* fn;
       if (AppSession.GetAppIcon(appInfo.iUid,fn)!=KErrNone){continue;}
       if (fn){delete fn;}
       if (appInfo.iCaption.Length()<2){continue;}
       if (!Utils::IsUidInList(appInfo.iUid)){continue;}
       TApplicationInfo info;
       info.iCaption=appInfo.iCaption;
       info.iUid=appInfo.iUid;
       UidTxt.Num((TUint)info.iUid.iUid,EHex);
       UidTxt.UpperCase();
       if (uidsinparams.Find(UidTxt)!=-1){RDebug::Print(_L("Skip %S"),&UidTxt);continue;}
       apps.Append(info);
       fullApps.Append(info);
   }
   AppSession.Close();
   TLinearOrder<TApplicationInfo> sortOrder(TApplicationInfo::Compare);
   fullApps.Sort(sortOrder);
   apps.Sort(sortOrder);
   for (int i=0; i<fullApps.Count();i++)
   {
       appModel<<QString::fromRawData(reinterpret_cast<const QChar*>(apps[i].iCaption.Ptr()),apps[i].iCaption.Length());
       uidsModel<<QString::number((TUint)fullApps[i].iUid.iUid,16);
   }
#else
   for (int i=0; i<20;i++)
   {
       appModel<<QString::number(i);
   }
#endif
   //viewer->rootContext()->setContextProperty("appModel",appModel);




#ifdef Q_OS_SYMBIAN
   CRepository* cr=CRepository::NewL(TUid::Uid(0x101F8847));
   TBuf<1024> tdesval;
   cr->Get(0x8,tdesval);
   delete cr;

   selected=QString::fromRawData(reinterpret_cast<const QChar*>(tdesval.Ptr()),tdesval.Length()).split(",");
   qDebug()<<selected;
#endif
}

void Application::SortApps(QString filter)
{
#ifdef Q_OS_SYMBIAN
    apps.Reset();
    appModel.clear();
    uidsModel.clear();
    QString name;
    for (int i=0;i<fullApps.Count();i++)
    {
        name=QString::fromRawData(reinterpret_cast<const QChar*>(fullApps[i].iCaption.Ptr()),fullApps[i].iCaption.Length());
        if (name.toLower().startsWith(filter.toLower()))
        {
            apps.Append(fullApps[i]);
            appModel.append(name);
            uidsModel.append(QString::number((TUint)fullApps[i].iUid.iUid,16));
        }
    }
    viewer.rootContext()->setContextProperty("appModel",appModel);
    viewer.rootContext()->setContextProperty("uidsModel",uidsModel);
#endif
}

int Application::isChecked(int i)
{
   if (selected.contains(QString::number((TUint)apps[i].iUid.iUid,16).toUpper()))return 1;
   else return 0;
}

void Application::changeSetting(int index)
{
    QString additionalVal=QString::number((TUint)apps[index].iUid.iUid,16).toUpper();
    qDebug()<<"change setting"<<additionalVal;
    if (selected.contains(additionalVal)){qDebug()<<"remove"; selected.removeOne(additionalVal);}
    else if (selected.count()<100) {qDebug()<<"add";selected.append(additionalVal);}
    else emit {tooManyApps();qDebug()<<"too many"; return;}
    TBuf<1024> val;
    //TPtrC temp;
    for (int i=0;i<selected.count();i++)
    {
        TPtrC temp(static_cast<const TUint16*>(selected[i].utf16()), selected[i].length());
        val.Append(temp);
        if (i!=selected.count()-1) val.Append(_L(","));
    }
    CRepository* cr=CRepository::NewL(TUid::Uid(0x101F8847));
    cr->Set(0x8,val);
    delete cr;
    viewer.rootContext()->setContextProperty("changed",1);
    launches+=1;
    QFile file("launches");
    file.open (QIODevice::WriteOnly);
    QTextStream stream ( &file );
    stream.setCodec("UTF-16");
    stream << launches << "\n";
    file.close(); // when your done

}

bool Application::eventFilter(QObject *obj, QEvent * event)
{
   if (event->type() == QEvent::ApplicationDeactivate)
   {
      Restart();
      qDebug()<<"app goes background";
      return true; // The event is handled
   }
   if (event->type() == QEvent::Quit)
   {
      Restart();
      qDebug()<<"app goes exit";
      return true; // The event is handled
   }
   if (event->type() == QEvent::ApplicationActivate)
   {
      qDebug()<<"app goes foreground";
      return true;
   }
   return QObject::eventFilter(obj, event); // Unhandled events are passed to the base class
}

void Application::Restart()
{
    /*
    qDebug()<<"Application::Restart";
    RStarterSession starter;
    qDebug()<<starter.Connect();
    starter.Reset(starter.ELanguageSwitchReset);
    starter.Close();
    */
    /*
    TUid aUid=TUid::Uid(0x102750F0);
    TApaTaskList lst=TApaTaskList(CEikonEnv::Static()->WsSession());
    TApaTask tsk=lst.FindApp(aUid);
    if (tsk.Exists()) tsk.EndTask();
    RApaLsSession apaLsSession;
    User::LeaveIfError(apaLsSession.Connect());
    CleanupClosePushL(apaLsSession);
    TApaAppInfo appInfo;
    TInt retVal = apaLsSession.GetAppInfo(appInfo, aUid);

    if(retVal == KErrNone)
        {
        CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
        cmdLine->SetExecutableNameL(appInfo.iFullName);
        cmdLine->SetCommandL(EApaCommandRun);
        cmdLine->SetCommandL(EApaCommandBackground);
        User::LeaveIfError( apaLsSession.StartApp(*cmdLine) );

        CleanupStack::PopAndDestroy(cmdLine);
        }
    else
        {
        // The application not found!
        }
    CleanupStack::PopAndDestroy(&apaLsSession);
    */
}

void Application::LoadIcons()
{
    //viewer.rootContext()->setContextProperty("appModel",appModel);
    //viewer.rootContext()->setContextProperty("uidsModel",uidsModel);
}
