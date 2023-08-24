#include <QApplication>
#include <QLabel>
#include <patientuitwo.h>
//#include <patientview.h>
//#include "adddiary.h"
//#include "viewdiary.h"
//#include "viewrecord.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PatientUiTwo homep;
    homep.show();
    return app.exec();
}
