#include "iconprovider.h"
#include <qDebug>
#include <avkon.mbg>
#include <QBitmap>
#include <QFile>
#include <QDir>

#include <eikenv.h>
IconProvider::IconProvider() :
    QDeclarativeImageProvider(QDeclarativeImageProvider::Image)
{

}

QImage IconProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    bool ok;
    iSize=new QSize(50,50);
    qDebug()<<"requestImage"<<id<<iSize->width()<<iSize->height();
    CGulIcon* icon;
    TUid uid=TUid::Uid((TUint32)id.toULong(&ok,16));
    if (!ok)
    {
        qDebug()<<"invalid uid";
        uid=TUid::Uid(0x0);
    }
    TRAPD(erreasy,icon=LoadAppIconEasy(uid));
    if (erreasy==KErrNotFound)
    {
        qDebug()<<"icon not found";
        CFbsBitmap*	AppIcon(NULL);
        CFbsBitmap*	AppIconMsk(NULL);
        qDebug()<<1;
        AknIconUtils::CreateIconL(AppIcon,AppIconMsk,AknIconUtils::AvkonIconFileName(), EMbmAvkonQgn_indi_no_signal, EMbmAvkonQgn_indi_no_signal_mask);
        qDebug()<<2;
        AknIconUtils::SetSize(AppIconMsk,TSize(iSize->width(),iSize->height()));
        qDebug()<<3;
        qDebug()<<"around"<<AppIcon->Handle();
        qDebug()<<4;
        icon=CGulIcon::NewL(AppIcon,AppIconMsk);
    }
    else if (erreasy!=KErrNone){TRAPD(errhard,icon=LoadAppIconHard(uid));}
    //QPixmap* pix=new QPixmap(*iSize);
    QPixmap pix=QPixmap::fromSymbianCFbsBitmap(icon->Bitmap());
    QImage mask=QBitmap::fromSymbianCFbsBitmap(icon->Mask()).toImage();
    mask.invertPixels();
    pix.setMask(QBitmap::fromImage(mask));
    QImage im=pix.toImage();
    QFile file(id+".png");
    if (!file.exists()) im.save(id+".png");
    return im;
}
CGulIcon* IconProvider::LoadAppIconEasy(TUid aUid)
        {
        qDebug()<<"try load easy";
        RApaLsSession ls;
        ls.Connect();
        TApaAppInfo info;
        User::LeaveIfError(ls.GetAppInfo(info,aUid));
        HBufC* path=HBufC::NewL(255);
        TInt err=ls.GetAppIcon(aUid,path);
        User::LeaveIfError(err);
        CFbsBitmap*	AppIcon(NULL);
        CFbsBitmap*	AppIconMsk(NULL);
        //MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        if ((err==KErrNone)&&(path->Length()!=0))
                {AknsUtils::CreateAppIconLC(AknsUtils::SkinInstance(),aUid, EAknsAppIconTypeContext,AppIcon,AppIconMsk);}
        else {User::Leave(KErrNotFound);}
        AknIconUtils::SetSize(AppIcon,TSize(iSize->width(),iSize->height()));
        AknIconUtils::SetSize(AppIconMsk,TSize(iSize->width(),iSize->height()));
        CleanupStack::Pop(2);
        qDebug()<<"easy"<<AppIcon->Handle();
        CGulIcon* icon=CGulIcon::NewL(AppIcon,AppIconMsk);
        ls.Close();
        return icon;
        }

CGulIcon* IconProvider::LoadAppIconHard(TUid aUid)
        {
        qDebug()<<"hard";
        RApaLsSession ls;
        ls.Connect();
        CGulIcon *retval = NULL;
        CArrayFixFlat<TSize> *array = new CArrayFixFlat<TSize>(3);
        CleanupStack::PushL(array);
        qDebug()<<"0"<<array;
        TInt err = ls.GetAppIconSizes(aUid, *array);
        if(err == KErrNone && array->Count() > 0)
                {
                qDebug()<<1;
                CApaMaskedBitmap *bitmap = CApaMaskedBitmap::NewLC();
                err = ls.GetAppIcon(aUid, (*array)[0], *bitmap);
                if(err == KErrNone)
                        {
                        qDebug()<<2;
                        CFbsBitmap* bmp = new (ELeave) CFbsBitmap();
                        CleanupStack::PushL(bmp);
                        CFbsBitmap* bmp_mask = new (ELeave) CFbsBitmap();
                        CleanupStack::PushL(bmp_mask);
                        qDebug()<<3;
                        User::LeaveIfError(bmp->Create(bitmap->SizeInPixels(), bitmap->DisplayMode()));
                        User::LeaveIfError(bmp_mask->Create(bitmap->Mask()->SizeInPixels(), bitmap->Mask()->DisplayMode()));
                        qDebug()<<4;
                        CopyBitmapL(bitmap, bmp);
                        CopyBitmapL(bitmap->Mask(), bmp_mask);
                        qDebug()<<"hard"<<bmp->Handle();
                        retval = CGulIcon::NewL(bmp, bmp_mask);
                        CleanupStack::Pop(2); // bmp, bmp_mask
                        }
                        CleanupStack::PopAndDestroy(bitmap);
                }
                CleanupStack::PopAndDestroy(array);
                ls.Close();
                qDebug()<<"err"<<err;
                return retval;
        }

void IconProvider::CopyBitmapL(CFbsBitmap *aSource, CFbsBitmap *aTarget)
        {
        qDebug()<<"CopyBitmapL";
        if(aSource != NULL && aTarget != NULL)
                {
                if(aSource->SizeInPixels() != aTarget->SizeInPixels() || aSource->DisplayMode() != aTarget->DisplayMode())
                        {User::Leave(KErrArgument);}
                CFbsBitmapDevice* device = CFbsBitmapDevice::NewL(aTarget);
                CleanupStack::PushL(device);
                CFbsBitGc* gc = NULL;
                User::LeaveIfError(device->CreateContext(gc));
                CleanupStack::PushL(gc);
                gc->BitBlt(TPoint(0, 0), aSource);
                CleanupStack::PopAndDestroy(gc);
                CleanupStack::PopAndDestroy(device);
                }
        }
