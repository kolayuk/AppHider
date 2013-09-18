import QtQuick 1.0
import com.nokia.symbian 1.1

Page{
    signal back;
    Rectangle{
        anchors.fill: parent
        color:"black"
    }

    Flickable {
        id: flickArea
        anchors.fill: parent
        //anchors.top: statusBar.bottom;
        //anchors.bottom: toolBar.top;
        //anchors.left: parent.left;
        //anchors.right: parent.right
        contentWidth: parent.width;
        contentHeight: c.height;
        flickableDirection: Flickable.VerticalFlick
        clip: true
        Column{
            id:c
            spacing: 10;
            anchors.top: parent.top//statusBar.bottom;
            //anchors.bottom: parent.bottom//toolBar.top;
            anchors.left: parent.left;
            anchors.right: parent.right
            anchors.topMargin: 20;
            anchors.verticalCenter: parent.verticalCenter
            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                id: logo
                source: "logo.png"
            }
            Text{
                text:"AppsHider 1.0";
                color:"white"
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter;
                anchors.left: parent.left;
                anchors.right: parent.right
                font.pixelSize: 35;
                wrapMode: Text.WordWrap
            }

            Text{
                text:strings[0];
                color:"white"
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter;
                anchors.left: parent.left;
                anchors.right: parent.right
                font.pixelSize: 20;
                wrapMode: Text.WordWrap

            }
        }
}
/*
        StatusBar {
            id: statusBar
            y:0
            x:0
            Text {
                id: pagetitle
                text: "About"
                anchors.fill: statusBar
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                color:"white"
                font.pixelSize: 0.7*statusBar.height
            }
        }
        */
            tools: ToolBarLayout {
                id: toolBarLayout
                ToolButton {
                    flat: true
                    id:backbtn;
                    iconSource: "toolbar-back.png"
                    onClicked: {back();}
                }
                ToolButton {
                    flat: true
                    iconSource: "ovi.png"
                    onClicked: {Qt.openUrlExternally("http://store.ovi.com/publisher/Alexander+Fokin/");}
            }
                ToolButton {
                    flat: true
                    iconSource: ""
                    onClicked: {}
                }
            }

    }

