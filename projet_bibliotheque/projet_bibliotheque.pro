QT       += core gui sql charts printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    connexion_mysql.h \
    gestion_acceuil.h \
    gestion_emprunter.h \
    gestion_lecteur.h \
    gestion_livre.h \
    gestion_login.h \
    gestion_remise.h \
    gestion_sanction.h \
    gestion_stat.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image_login.qrc \
    img.qrc \
    ressource.qrc
