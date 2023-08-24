HEADERS += \
    adddiary.h \
    db_service.hpp \
    patient.hpp \
    patientServer.hpp \
    patientuitwo.h \
#    patientview.h \
    viewrecord.h \
    sqlite3.h

SOURCES += \
    adddiary.cpp \
    db_service.cpp \
    mainp.cpp \
    patientServer.cpp \
    patientuitwo.cpp \
#    patientview.cpp \
#    viewdiary.cpp \
    viewrecord.cpp \
    sqlite3.c

QT += widgets quick sql

FORMS += \
    AddDiary.ui \
    PatientUiTwo.ui \
#    PatientView.ui \
#    ViewDiary.ui \
    ViewRecord.ui
