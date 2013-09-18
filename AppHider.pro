# Add more folders to ship with the application, here
folder_01.source = qml/AppHider
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

qt_components.pkg_prerules += "(0x200346DE), 1, 1, 0, {\"Qt Components\"}"
symbian:DEPLOYMENT += qt_components

locs.source=D:\Symbian\QtSDK\workspace\AppHider\lang
locs.target = C:\system\apps\AppHider
symbian:DEPLOYMENTFOLDERS+=locs

vendorinfo =  "%{\"Alexander Fokin\"}" \
    ":\"Alexander Fokin\""
vendor.pkg_prerules = vendorinfo
symbian:DEPLOYMENT += vendor

symbian:DEPLOYMENT.installer_header = "$${LITERAL_HASH}{\"AppsHider\"},(0x2002CCCF),1,0,0"
packageheader = "$${LITERAL_HASH}{\"AppsHider\"}, (0x20067B0E), 1, 0, 0, TYPE=SA"
info.pkg_prerules=packageheader
symbian:DEPLOYMENT+=info

symbian:INCLUDEPATH+=D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/include/mw
symbian:INCLUDEPATH+=D:\Symbian\QtSDK112\Symbian\SDKs\Symbian3Qt473\epoc32\include

symbian:TARGET.EPOCSTACKSIZE = 0x14000
symbian:TARGET.UID3 = 0x20067B0E
symbian:TARGET.CAPABILITY += NetworkServices ReadDeviceData WriteDeviceData PowerMgmt
symbian:LIBS+=-leuser
symbian:LIBS+=-lapparc
symbian:LIBS+=-lapgrfx
symbian:LIBS+=-lcentralrepository
symbian:LIBS+=-lgdi
symbian:LIBS+=-lbitgdi
symbian:LIBS+=-laknskins
symbian:LIBS+=-lfbscli
symbian:LIBS+=-legul
symbian:LIBS+=-laknicon
symbian:LIBS+=-leikcore
symbian:LIBS+=-lavkon
symbian:LIBS+=-leiksrv
symbian:LIBS+=-lcone
symbian:LIBS+=-lapparc
symbian:LIBS+=-lws32
symbian:LIBS+=-lstarterclient

CONFIG += qt-components
DEPLOYMENT.display_name = "AppsHider"
# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    application.cpp \
    localizer.cpp \
    iconprovider.cpp \
    Utils.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    application.h \
    const.h \
    localizer.h \
    iconprovider.h \
    Utils.h


