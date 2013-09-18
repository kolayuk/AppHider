/*============================================================================
 Name        : Utils from Utils.h
 Author      : Fokin Alexander -=- ICQ : 285271527 -=- E-mail : alexander_fokin@symdeveloper.ru
 Version     : 1.0
 Copyright   :
 Description : Declares common utils
 ============================================================================*/
#ifndef UTILS_H
#define UTILS_H

#include <e32base.h>
#include <c32comm.h>
#include <e32math.h>
#include <BADESCA.H>


namespace Utils
{
	bool IsUidInList(const TUid aUid);
	bool IsUidIsInstaller(const TUid aUid);
}

#endif // UTILS_H
// End of File
