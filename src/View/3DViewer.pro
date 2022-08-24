QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += GL_SILENCE_DEPRECATION    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    Render.cpp \
    View.cpp \
    ../Controller/Controller.cpp \
    ../Model/Model.cpp


HEADERS += \
    Render.h \
    View.h \
    ../Controller/Controller.h \
    ../Model/Model.h


FORMS += \
    View.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
