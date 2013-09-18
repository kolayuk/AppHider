#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <qmlapplicationviewer.h>
#include <localizer.h>

#ifdef Q_OS_SYMBIAN
#include <e32base.h>

struct TApplicationInfo
{
        TFileName iCaption;
        TUid iUid;
        static TInt Compare(const TApplicationInfo& aInfo1, const TApplicationInfo& aInfo2)
        {
                return aInfo1.iCaption.CompareC(aInfo2.iCaption);
        }
};
#endif


class Application : public QObject
{
    Q_OBJECT
public:
    explicit Application(QmlApplicationViewer& v,QObject *parent = 0);
    QmlApplicationViewer& viewer;
    Localizer* loc;
    QStringList appModel;
    QStringList selected;
    QStringList uidsModel;
    bool eventFilter(QObject *, QEvent *);
    int launches;
#ifdef Q_OS_SYMBIAN
    RArray<TApplicationInfo> apps;
    RArray<TApplicationInfo> fullApps;
#endif
signals:
    void tooManyApps();
public slots:
    void Restart();
    void LoadIcons();
    void SortApps(QString filter);
    int isChecked(int index);
    void changeSetting(int index);
};

#endif // APPLICATION_H
