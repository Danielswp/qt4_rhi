QT += core gui opengl widgets sql network xml
win32: LIBS += -lopengl32 -lglu32


CONFIG += qtc_runnable
TEMPLATE = app
TARGET = GUI

SOURCES += main.cpp \
    mainui.cpp

HEADERS += \
    glwidget.h \
    mainui.h

SOURCES += \
    glwidget.cpp

INCLUDEPATH += $$PWD/../Math

# ===== 链接 Math 库 =====
win32-msvc* {
    CONFIG(debug, debug|release) {
        # Debug 模式：指向 debug 子目录
        LIBS += -L$$OUT_PWD/../Math/debug -lMath
    } else {
        # Release 模式
        LIBS += -L$$OUT_PWD/../Math/release -lMath
    }
} else {
    # MinGW 兜底
    LIBS += -L$$OUT_PWD/../Math -lMath
}

RESOURCES += \
    resources/gui_resource.qrc

FORMS += \
    mainui.ui


