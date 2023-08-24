/**
 * @file patient_ui_two.cpp
 * @brief Methods in this file takes the patient to the page that shows record or the page that lets the patient add entry to diary
 *
 * @author Amreen Anbar
 * @bug No known bugs
*/
#include "patient_ui_two.h"
#include "ui_patient_ui_two.h"
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QStringList>

//#include "patient_server.hpp"

using namespace std;

//PatientUiTwo::PatientUiTwo(QWidget *parent, Patient* newpatient) :
//    QDialog(parent),
//    ui(new Ui::PatientUiTwo),
//    patient(newpatient)
//{
//    ui->setupUi(this);
//    init(newpatient);

//    //patientServer obj2;
//}

PatientUiTwo::PatientUiTwo(QWidget *parent, Patient* myself) :
    QDialog(parent),
    ui(new Ui::PatientUiTwo)

{
    //the ui is set to be for this file
    ui->setupUi(this);
    init(myself);
}

PatientUiTwo::~PatientUiTwo()
{
    delete ui;
}

void PatientUiTwo::init(Patient* myself)
{
    patient = myself;
}


void PatientUiTwo::on_pushButton_clicked() //Patient requests to view his/her/their record
{
    //takes to the ui that shows record
    hide();
    viewrecord = new ViewRecord(this, patient);
    viewrecord->show();
    //complete_report();
}


void PatientUiTwo::on_pushButton_2_clicked() //Patient requests to update diary/ write to diary
{
   //takes to the ui that lets one add to diary
   //upon proceeding to second window the first window will be close automatically for this hide function
    hide();
    adddiary = new AddDiary(this, patient);
    adddiary->show();
}
