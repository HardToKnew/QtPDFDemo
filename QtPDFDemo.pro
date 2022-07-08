QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#就是下面这行用来设置运行文件附带调试输出窗口CONFIG      += console
win32 {
    contains(QT_ARCH, i386) {
        TARGET= QtPdfDemo0.0.1x86
        message("32-bit")
    }else {
        TARGET= QtPdfDemo0.0.1x64
        message("64-bit")
    }
}
#指定编译生成的可执行文件到bin目录
DESTDIR += $$PWD/bin
#程序版本
VERSION = 0.0.1
#程序图标
RC_FILE = source/ico.rc
#RC_ICONS = app.ico
#公司名称
QMAKE_TARGET_COMPANY ="HardToKnew"
#程序说明
QMAKE_TARGET_DESCRIPTION = "QtPdfDemo0.0.1"
#版权信息
QMAKE_TARGET_COPYRIGHT = "Copyright(C) 2022"
#程序名称
QMAKE_TARGET_PRODUCT = "QtPdfDemo"
#程序语言
#0x0800代表和系统当前语言一致
RC_LANG = 0x0800
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/aboutdlg.cpp \
    source/lockedandunlockeddlg.cpp \
    source/main.cpp \
    source/mainw.cpp \
    source/helpdlg.cpp \
    source/splitfiledlg.cpp

HEADERS += \
    source/aboutdlg.h \
    source/lockedandunlockeddlg.h \
    source/mainw.h \
    source/helpdlg.h \
    source/splitfiledlg.h

FORMS += \
    source/aboutdlg.ui \
    source/lockedandunlockeddlg.ui \
    source/mainw.ui \
    source/helpdlg.ui \
    source/splitfiledlg.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    source/images.qrc

DISTFILES += \
    source/ico.rc

