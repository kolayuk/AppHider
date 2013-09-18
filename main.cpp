#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include <QDeclarativeContext>
#include <application.h>
#include <localizer.h>
#include <QDeclarativeEngine>
#include <iconprovider.h>


Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());
    QCoreApplication::setAttribute(Qt::AA_S60DisablePartialScreenInputMode, false);
    Application* myapp=new Application(*viewer.data());
    //app->installEventFilter(myapp);
    viewer->engine()->addImageProvider(QLatin1String("icons"), new IconProvider);
    viewer->rootContext()->setContextProperty("changed",0);
    viewer->rootContext()->setContextProperty("application",myapp);
    viewer->rootContext()->setContextProperty("appModel",myapp->appModel);
    viewer->rootContext()->setContextProperty("uidsModel",myapp->uidsModel);
    viewer->rootContext()->setContextProperty("launches",myapp->launches);
    //viewer->rootContext()->setContextProperty("selected",myapp->selected);
    viewer->rootContext()->setContextProperty("strings",myapp->loc->GetStringsAsList());
    viewer->setMainQmlFile(QLatin1String("qml/AppHider/main.qml"));
    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationLockPortrait);
    viewer->showExpanded();

    return app->exec();
}
