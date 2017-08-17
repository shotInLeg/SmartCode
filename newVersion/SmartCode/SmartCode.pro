#-------------------------------------------------
#
# Project created by QtCreator 2017-07-28T23:20:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartCode
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        smartcode.cpp \
    dialogs/s_create_new_entry/s_create_new_entry.cpp \
    dialogs/s_create_new_project/s_create_new_project.cpp \
    dialogs/s_check_unsave_changes/s_check_unsave_changes.cpp \
    dialogs/s_confirm_remove/s_confirm_remove.cpp \
    dialogs/s_add_new_entry/s_add_new_entry.cpp \
    dialogs/s_git_commit/s_git_commit.cpp \
    menu.cpp \
    toolbar.cpp \
    project_toolbar.cpp \
    codeeditor_toolbar.cpp \
    workbar.cpp \
    leftbar.cpp \
    widgets/s_code_editor/s_code_editor.cpp \
    widgets/s_highlighter/s_highlighter.cpp \
    widgets/s_code_editor/code_area.cpp

HEADERS += \
        smartcode.h \
    dialogs/s_create_new_entry/s_create_new_entry.h \
    dialogs/s_create_new_project/s_create_new_project.h \
    dialogs/s_check_unsave_changes/s_check_unsave_changes.h \
    dialogs/s_confirm_remove/s_confirm_remove.h \
    dialogs/s_add_new_entry/s_add_new_entry.h \
    dialogs/s_git_commit/s_git_commit.h \
    widgets/s_code_editor/s_code_editor.h \
    widgets/s_highlighter/s_highlighter.h \
    resources/highlighter/lgc.hp

FORMS += \
        smartcode.ui \
    dialogs/s_create_new_entry/s_create_new_entry.ui \
    dialogs/s_create_new_project/s_create_new_project.ui \
    dialogs/s_check_unsave_changes/s_check_unsave_changes.ui \
    dialogs/s_confirm_remove/s_confirm_remove.ui \
    dialogs/s_add_new_entry/s_add_new_entry.ui \
    dialogs/s_git_commit/s_git_commit.ui

RESOURCES += \
    resources.qrc
