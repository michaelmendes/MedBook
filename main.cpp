#include "database_admin.hpp"
#include "clinician_ui.hpp"
#include "clinician.hpp"
#include "family_physician_ui.hpp"
#include "family_physician.hpp"
#include "med_book.hpp"

#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    cout << "App path : " << a.applicationDirPath().toStdString() << endl;

    //Add this to create/initialize db :=)
    //DatabaseAdmin admin;

    MedBook medBook; // This should be the only main window
    medBook.show();

    return a.exec();
}

