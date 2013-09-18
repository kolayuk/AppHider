import QtQuick 1.0
import com.nokia.symbian 1.1

PageStackWindow {
    id: pgs
    //platformSoftwareInputPanelEnabled: true
    initialPage: mainPage

    showStatusBar: true
    showToolBar: true
    MainPage{
        id: mainPage
        onAbout:{pgs.pageStack.replace(aboutPage);}
    }
    AboutPage{
        id: aboutPage
        onBack:pgs.pageStack.replace(mainPage);
    }
}
