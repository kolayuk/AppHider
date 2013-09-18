import QtQuick 1.1
import com.nokia.symbian 1.1

Page {
    id: root
    signal back;
    signal about;
    onAbout: {search.text=""; forceActiveFocus();}
    HelpDialog{
        id:wrn;
    }

    Connections{
        target: application
        onTooManyApps:{wrn.open();}
    }

    Text {
        id: header
        text: strings[3];
        color:"white"
        font.pixelSize: 16;
        horizontalAlignment: Text.AlignJustify
        wrapMode: Text.WordWrap;
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 5;
        anchors.rightMargin: 5;
        anchors.top: parent.top;
        anchors.topMargin: 5;

    }
    ListView{
        id:flick
        anchors.top: header.bottom;
        anchors.bottom: search.top;
        anchors.bottomMargin: 5
        anchors.topMargin: 5;
        anchors.left: parent.left;
        anchors.right: parent.right
        clip: true
        model:appModel
        delegate: Component{
            Item{
                id:delegate
                width: flick.width
                height: icon.height+20
                Image {
                    id: icon
                    height: 50
                    width: height
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10;
                    source: "image://icons/"+uidsModel[index];
                }
                Text {
                    id: apptxt
                    anchors.left: icon.right
                    anchors.right: parent.right
                    anchors.leftMargin: 10
                    color:"white"
                    text: modelData
                    font.pixelSize: sw.height*0.5
                    anchors.verticalCenter: icon.verticalCenter

                }
                Switch{
                    id:sw
                    property int click: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 10;
                    anchors.verticalCenter: icon.verticalCenter
                    checked: application.isChecked(index)==0;
                    onClicked: {application.changeSetting(index);}

                }
            }
        }
            }
    MouseArea{
        anchors.fill: flick
        onPressed: {forceActiveFocus();mouse.accepted=false;}
    }
    ScrollBar {
         flickableItem: flick
         anchors { right: flick.right; top: flick.top }
         interactive: true;
     }

    TextField{
            id: search;
            placeholderText:strings[1];
            width: parent.width-10
            anchors.horizontalCenter: parent.horizontalCenter
            onTextChanged: {application.SortApps(text);}
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5;

            onActiveFocusChanged: {
               if (activeFocus){root.height=root.height-inputContext.height+root.pageStack.toolBar.height;}
                else {root.height=root.height+inputContext.height-root.pageStack.toolBar.height;}
            }

            //anchors.bottomMargin: 5;

        }
    /*
    StatusBar {
            id: statusBar
            anchors.top: root.top
            Text {
                id: pagetitle
                text: "AppHider"
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
                    onClicked: {application.Restart(); Qt.quit();}
                }
                ToolButton {
                    flat: true
                    iconSource: "ovi.png"
                    onClicked: {Qt.openUrlExternally("http://store.ovi.com/publisher/Alexander+Fokin/");}
                }
                ToolButton {
                    flat: true
                    id:aboutbtn;
                    iconSource: "toolbar-menu.png"
                    onClicked: {about();}
                }
            }

}
