/*============================================================================
 Name        : Utils.cpp
 Author      : Fokin Alexander -=- ICQ : 285271527 -=- E-mail : alexander_fokin@symdeveloper.ru
 Version     : 1.0
 Copyright   :
 Description : Common utils
 ============================================================================*/
//SYSTEM INCLUDES
#include <f32file.h>
#include <utf.h>
#include <hash.h>
#include <SysUtil.h>
#include <EZGzip.h>
#include <CHARCONV.H>
#include <BAUTILS.H>
#include <APAID.H>
#include <APGCLI.H>
#include <APGTASK.H>
#include <eikenv.h>

//USER INCLUDES
#include "Utils.h"

enum TUidValidateStatus
{
	EUidValid = 0,
	EUidNotValid = 1
};

namespace Utils
{
        static const TInt uids_list[] =
        {
                //это УИДЫ которые не нужно показывать в списке
                0x2000afcc,	//Z:\sys\bin\HsBrowser.exe
                0x101f8681, //video call
                //0x10281893, //Video services | Z:\sys\bin\VideoServices.exe
                0x20026f2f, //Video editor | Z:\sys\bin\VideoEditor.exe
                0x10282391,	//Video sharing | Z:\sys\bin\musui.exe
                0x2001843a, //Installer | Z:\sys\bin\javainstaller.exe
                0x100058b3, //telephone
                0x2004423c,	//swipeUnlockSrv
                0x2005fc7f, //swipeUnlockSrv
                0x2002F81A,	//CutMyCalls client
                0x2002F819, //CutMyCalls server
                0x20036F80, //CutMyCalls advisor
                0x2002F819,	//TactileCalls server
                0x2002F81A, //TactileCalls client
                0x2002F819, //RndTones server
                0x2002F81A, //RndTones client
                0x20031EF0,	//RndTones Demo server
                0x20031EF1, //RndTones Demo client
                0x100056cf,	//screensaver | Z:\sys\bin\screensaver.exe
                0x10204375, //CfmwLauncher
                //0x101f4cce,	//Z:\sys\bin\Phonebook2.exe
                0x102072c4,	//Загрузить | Z:\sys\bin\fotaserver.exe
                0x102750f0,	//Home screen | Z:\sys\bin\homescreen.exe
                0x101f875a, //Installer | Z:\sys\bin\SWInstSvrUI.exe
                0x2001843a,	//Installer
                0x200348d2, //listenServerapp
                0x101f4ce4, //E-mail | Z:\sys\bin\MsgMailViewer.exe
                0x101f4cd6, //E-mail | Z:\sys\bin\MsgMailEditor.exe
                0x10201b00,	//Msg. reader | Z:\sys\bin\messagereaderapplication.exe
                0x102072d8,	//Z:\sys\bin\UniEditor.exe
                0x100058df, //Multimedia | Z:\sys\bin\mmsviewer.exe
                0x100058de, //Multimedia | Z:\sys\bin\mmseditor.exe
                0x10275458,	//Net settings
                0x2001cc11, // New alarm
                0x101f86a0, //NOT | Z:\sys\bin\notviewer.exe
                0x10207277,	//Z:\sys\bin\Pbk2ServerApp.exe
                0x20026fc2,	//Phonebook 2 | Z:\sys\bin\NewContactLauncher.exe
                0x101f874a, //SVGT Viewer App | Z:\sys\bin\SVGTViewerApp.exe
                0x10005a3f, //MediaSettings | Z:\sys\bin\MediaSettings.exe
                0x2000e5f7, //E-mail setup | C:\sys\bin\ODSEmailSetup.exe
                0x20029c40, //Share my location settings
                0x200348bc,	//Sharing
                0x20022ebd,	//Signal boost
                0x200269a0,	//Social installer
                0x2000dcc5,	//SSOUI
                0x2000dcb2,	//SSOUsernameWidget
                0x200348cc, // contacts widget
                0x200104e7, //gallery
                0x101f8543, // voice control
                0x1000599d, // notes
                0x1020745a, // voice message
                0x200348cb, // contact card
                0x2000f85a, // updater
                0x101f85c1, // landmarks
                0x100058bd, //  sms message
                0x101f4cd3, // operators message
                0x101f8532, // wap browser
                0x101f5ce0, // operators services
                0x101f4ce0,  //the same
                0x101fd693, // flash player
                0x2000dbcc,		//Ovi Store (хрен пойми, что это такое, но точно не основное приложение OviStore)
                0x10281861,		//Positioning
                0x2001f3a9,		//Search
                0x20032db3,		//2Gis (не основное приложение)
                0x2000cd7f,		//Adobe Reader (не основное приложение)
                0x20029b6a,		//Maps
                0x20029b6c,		//Maps
                0x2000745e,		//QuickOffice (pdf?)
                0x2001f7b1,		//QuickOffice (не основное приложение)
                0x2002699f,		//Social (не основное приложение)
                0x200269a2,		//Social (не основное приложение)
                0x20067b0e, // AppsHider
                0x200122a4, // setup phone
                0x10281c96, // setup email
                0x2000259a  // encrypt
        };

	bool IsUidInList(const TUid aUid)
	{
		for (TUint i = 0; i < sizeof(uids_list) / sizeof(uids_list[0]); i++) 
		{
			if (uids_list[i] == aUid.iUid)
			{
                                return 0;
			}
		}
                return 1;
	}
}

// End of File
