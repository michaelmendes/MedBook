QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clinician_server.cpp \
    clinician.cpp \
    clinician_ui.cpp \
    database_admin.cpp \
    db_service.cpp \
    family_physician_server.cpp \
    family_physician_ui.cpp \
    family_physician.cpp \
    login_server.cpp \
    login_ui.cpp \
    add_diary.cpp \
    view_record.cpp \
    patient_ui_two.cpp \
    main.cpp \
    med_book.cpp \
    medical_record.cpp \
    patient.cpp \
    patient_server.cpp \
    physician_ui_tester.cpp \
    record_editor.cpp \
    registration.cpp \
    request_system.cpp \
    user.cpp \
    #sqlite3.c \
    #test_record_editor.cpp \
    #test.cpp \

HEADERS += \
    clinician_server.hpp \
    clinician.hpp \
    clinician_ui.hpp \
    database_admin.hpp \
    db_service.hpp \
    family_physician_server.hpp \
    family_physician_ui.hpp \
    family_physician.hpp \
    login_server.hpp \
    login_ui.hpp \
    add_diary.hpp \
    view_record.hpp \
    patient_ui_two.h \
    med_book.hpp \
    medical_record.hpp \
    patient.hpp \
    patient_server.hpp \
    physician_ui_tester.hpp \
    record_editor.hpp \
    registration.hpp \
    request_system.hpp \
    user.hpp \
    sqlite3.h \

FORMS += \
    clinician.ui \
    family_physician.ui \
    login.ui \
    add_diary.ui \
    view_record.ui \
    patient_ui_two.ui \
    med_book.ui \
    registration.ui \

LIBS += -lsqlite3

# Default rules for deployment.

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    MedBook.pro.user \
    medBook.db \
    test
