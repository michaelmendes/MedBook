#include "family_physician_ui.hpp"
#include "family_physician.hpp"
#include "med_book.hpp"

#include "ui_med_book.h"

#include <iostream>

using namespace std;

MedBook::MedBook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MedBook)
{
    ui->setupUi(this);

    cout << "MedBook::MedBook before connect" << endl;
    connect(&loginUI, &LoginUI::loggedIn, this, &MedBook::on_loggedIn);
    // connect(&loginUI, &LoginUI::registerRequired, this, &MedBook::on_registerRequired);
    // connect(&registration, &Registration::userRegistered, this, &MedBook::on_userRegistered);

    cout << "MedBook::MedBook before add widgets" << endl;

    ui->stackedWidget->addWidget(&loginUI);
    // ui->stackedWidget->addWidget(&registration);
    ui->stackedWidget->addWidget(&clinicianUI);
    ui->stackedWidget->addWidget(&familyPhysicianUI);
    ui->stackedWidget->addWidget(&patientUI);

    cout << "MedBook::MedBook before setCurrentWidget" << endl;
    ui->stackedWidget->setCurrentWidget(&loginUI);
}

MedBook::~MedBook()
{
    delete ui;
}


/******************************
 * slots
 ******************************/
void MedBook::on_loggedIn(User* user)
{
    cout << "This is from MedBook::on_loggedIn userName:" << user->getName() << " userType:" << user->getType() << " logged in successful !" << endl;

    if (user->getType() == "Patient") {
        cout << "show patientUI" << endl;
        patientUI.init((Patient *)user);
        ui->stackedWidget->setCurrentWidget(&patientUI);
    } else if (user->getType() == "Family Physician") {
        cout << "show familyPhysicianUI" << endl;
        familyPhysicianUI.init((FamilyPhysician *)user);
        ui->stackedWidget->setCurrentWidget(&familyPhysicianUI);
    } else { // Clinician
        cout << "show clinicianUI" << endl;
        clinicianUI.init((Clinician *)user);
        ui->stackedWidget->setCurrentWidget(&clinicianUI);
    }
}

void MedBook::on_registerRequired()
{
    cout << "This is from MedBook::on_registerRequired" << endl;
    ui->stackedWidget->setCurrentWidget(&registration);
}

void MedBook::on_userRegistered()
{
    cout << "This is from MedBook::on_userRegistered" << endl;
    ui->stackedWidget->setCurrentWidget(&loginUI);
}
