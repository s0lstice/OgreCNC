#-------------------------------------------------
#
# Project created by QtCreator 2013-03-08T09:40:26
#
#-------------------------------------------------

QT += core gui
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CNCBrainCut
TEMPLATE = app

INCLUDEPATH += $$$(PWD)/QJson

unix {
    # You may need to change this include directory
    INCLUDEPATH += /usr/share/OGRE
    CONFIG += link_pkgconfig
    PKGCONFIG += OGRE
}

win32 {
    LIBS *= user32.lib
    LIBS += -L$(OGRE_HOME)\\boost\\lib

    INCLUDEPATH += $(OGRE_HOME)\\include
    INCLUDEPATH += $(OGRE_HOME)\\include\\OIS
    INCLUDEPATH += $(OGRE_HOME)\\include\\OGRE
    INCLUDEPATH += $(OGRE_HOME)\\include\\OGRE\\Terrain
    INCLUDEPATH += $(OGRE_HOME)\\boost

    debug {
        LIBS += -L$(OGRE_HOME)\\lib\\debug
        TARGET = $$join(TARGET,,,d)
        LIBS += -lOgreMain_d
        LIBS += -lOgrePaging_d
        LIBS += -lOgreProperty_d
        LIBS += -lOgreRTShaderSystem_d
        LIBS += -lOgreTerrain_d
        LIBS += -lOIS_d
        LIBS += -lboost_chrono-mgw47-mt-d-1_51
        LIBS += -lboost_date_time-mgw47-mt-d-1_51
        LIBS += -lboost_system-mgw47-mt-d-1_51
        LIBS += -lboost_thread-mgw47-mt-d-1_51
    }

    release {
        LIBS += -L$(OGRE_HOME)\\lib\\release
        LIBS += -lOgreMain
        LIBS += -lOgrePaging
        LIBS += -lOgreProperty
        LIBS += -lOgreRTShaderSystem
        LIBS += -lOgreTerrain
        LIBS += -lOIS
        LIBS += -lboost_chrono-mgw47-mt-1_51
        LIBS += -lboost_date_time-mgw47-mt-1_51
        LIBS += -lboost_system-mgw47-mt-1_51
        LIBS += -lboost_thread-mgw47-mt-1_51
    }
}

HEADERS += \
    sources/vue/OgreWidget/ogrewidget.h \
    sources/modele/bloc/nodebloc.h \
    sources/modele/bloc/bloc.h \
    sources/controleur/controleurbloc.h \
    sources/controleur/controleurmain.h \
    sources/modele/modelemain.h \
    sources/vue/vuemain.h \
    sources/controleur/controleurcut.h \
    sources/modele/modelecut.h \
    sources/vue/OgreWidget/controleurogrewidget.h \
    sources/modele/constantesapplication.h \
    sources/modele/bloc/modelebloc.h

SOURCES += \
    sources/vue/OgreWidget/ogrewidget.cpp \
    sources/main.cpp \
    sources/modele/bloc/nodebloc.cpp \
    sources/modele/bloc/bloc.cpp \
    sources/controleur/controleurbloc.cpp \
    sources/controleur/controleurmain.cpp \
    sources/modele/modelemain.cpp \
    sources/vue/vuemain.cpp \
    sources/controleur/controleurcut.cpp \
    sources/modele/modelecut.cpp \
    sources/vue/OgreWidget/controleurogrewidget.cpp \
    sources/modele/bloc/modelebloc.cpp

FORMS += \
    sources/vue/vuemain.ui
