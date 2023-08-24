/**
 * @file clinician_ui.cpp
 * @brief Methods in this file takes the clinician to the page that shows patient record or the page that lets the clinician to submit request for patients
 * 
 * @author Jessica Liu 
 * @bug No known bugs
*/  
#include <ctype.h>

#include "clinician.hpp"
#include "clinician_server.hpp"
#include "clinician_ui.hpp"
#include "patient.hpp"

#include "ui_clinician.h"

using namespace std;


ClinicianUI::ClinicianUI(QWidget *parent, Clinician* myself)
    : QWidget(parent)
    , ui(new Ui::ClinicianUI)
{ 
    //initialize the ui to be this 
    ui->setupUi(this);
    //initialize clinician 
    init(myself);
}

ClinicianUI::~ClinicianUI()
{
    delete ui;
}

void ClinicianUI::init(Clinician* myself) {
    cout << "ClinicianUI::init" << endl;
    clinician = myself;

    if (myself != nullptr) {
        cout << "ClinicianUI::init setClinician" << endl;
        clinicianServer.setClinician(clinician);

        refreshMain();

        ui->stackedWidget->setCurrentWidget(ui->main_page);
        cout << clinician->getId() << "  " << clinician->getName() << endl;
    }
}

void ClinicianUI::refreshMain()
{ 
  	//to load the table again or refresh 
    cout << "ClinicianUI::refreshMain" << endl;
    ui->clinicianNameLabel->setText(QString::fromStdString(clinician->getName()));
    patientList = clinicianServer.getPatients();

    QStringList horizontalHeader;
    QStringList verticalHeader;

    // NOW just populate the table with these values
    horizontalHeader.append("Patient ID");
    horizontalHeader.append("Patient Name");

    QStandardItemModel *model = new QStandardItemModel();

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    ui->patientTable->setModel(model);
    ui->patientTable->verticalHeader()->setVisible(false);
    ui->patientTable->verticalHeader()->setDefaultSectionSize(10);
    ui->patientTable->setShowGrid(false);

    for (Patient patient : patientList) {
        QStandardItem *col1 = new QStandardItem(to_string(patient.getId()).c_str());
        QStandardItem *col2 = new QStandardItem(patient.getName().c_str());
        QList<QStandardItem*> row;
        row.append(col1);
        row.append(col2);
        model->appendRow(row);
    }
}

// CLINICIAN MAIN UI BUTTONS

void ClinicianUI::on_viewRecordBtn_clicked()
{	 
    //shows patiernt record 
    qDebug() << "User clicked view record";

    QItemSelectionModel *selection = ui->patientTable->selectionModel();
    if (selection->hasSelection() && selection->selectedRows().size() == 1)
    {
        int row = selection->selectedRows().at(0).row();

        QModelIndex idIndex = ui->patientTable->model()->index(row,0); // 0 is col
        int patientId;
        try {
            patientId = ui->patientTable->model()->data(idIndex).toString().toInt();
        }
        catch (const invalid_argument&) {
            QMessageBox::information(this, "Message", "Please enter a valid ID", QMessageBox::Ok);
        }
        for (Patient patient : patientList)
        {
            if (patient.getId() == patientId)
            {
                myPatient = patient;
                break;
            }
        }
        //QModelIndex nameIndex = ui->patientTable->model()->index(row,1); // 1 is col
        //string patientName = ui->patientTable->model()->data(nameIndex).toString().toStdString();

        cout << patientId << "  " << myPatient.getName() << myPatient.getBirth() << endl;

        //myPatient.setName(patientName);
        //myPatient.setId(patientId);

        ui->patientIdLabel->setText(QString::fromStdString(to_string(myPatient.getId())));
        ui->patientNameLabel->setText(QString::fromStdString(myPatient.getName()));
        ui->patientDateOfBirthLabel->setText(QString::fromStdString(myPatient.getBirth()));
        ui->patientSexLabel->setText(QString::fromStdString(myPatient.getSex()));

        ui->stackedWidget->setCurrentWidget(ui->patient_record);
    }
    else
    {
        QMessageBox::information(this, "Message", "No patient selected", QMessageBox::Ok);
    }
}

void ClinicianUI::on_transferBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->request_page);
}


// PATIENT RECORD BUTTONS
void ClinicianUI::on_recordBackBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main_page);
}


// INFO SCREEN BUTTONS
void ClinicianUI::on_infoBackBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->patient_record);
}



// TRANSFER REQUEST BUTTONS
void ClinicianUI::on_requestBackBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main_page);
}


void ClinicianUI::on_submitRequestBtn_clicked()
{
    qDebug() << "User clicked submit patient request";
    bool validRequest = true;
    int currPhysicianId = -1;
    string currPhysicianName;
    if (!ui->patientIdLine_2->text().isEmpty()) {
        try {
            int id = ui->patientIdLine_2->text().toInt();
            myPatient.setId(id);
        }
        catch (const invalid_argument&) {
            QMessageBox::information(this, "Message", "Please enter a valid patient ID", QMessageBox::Ok);
            validRequest = false;
        }
    }
    else {
        QMessageBox::information(this, "Message", "Missing patient ID", QMessageBox::Ok);
        validRequest = false;
    }
    if (!ui->patientNameLine_2->text().isEmpty()) {
        myPatient.setName(ui->patientNameLine_2->text().toStdString());
    }
    else {
        QMessageBox::information(this, "Message", "Missing patient name", QMessageBox::Ok);
        validRequest = false;
    }
    if (!ui->physicianIdLine->text().isEmpty()) {
        try {
            currPhysicianId = ui->physicianIdLine->text().toInt();
        }
        catch (const invalid_argument&) {
            QMessageBox::information(this, "Message", "Please enter a valid physician ID", QMessageBox::Ok);
            validRequest = false;
        }
    }
    else {
        QMessageBox::information(this, "Message", "Missing current physician ID", QMessageBox::Ok);
        validRequest = false;
    }
    if (!ui->physicianNameLine->text().isEmpty()) {
        currPhysicianName= ui->physicianNameLine->text().toStdString();
    }
    else {
        QMessageBox::information(this, "Message", "Missing current physician name", QMessageBox::Ok);
        validRequest = false;
    }
    if (validRequest == true)
    {
        clinicianServer.sendRequest("View Record", &myPatient, currPhysicianId);
        ui->patientIdLine_2->setText("");
        ui->patientNameLine_2->setText("");
        ui->physicianIdLine->setText("");
        ui->physicianNameLine->setText("");
        ui->stackedWidget->setCurrentWidget(ui->main_page);
    }
}


// MEDICAL RECORD BUTTONS

void ClinicianUI::refreshMedicalRecord(vector<string> entries, string col1)
{
    QStringList horizontalHeader;
    QStringList verticalHeader;

    horizontalHeader.append(col1.c_str());
    horizontalHeader.append("Date");

    QStandardItemModel *model = new QStandardItemModel();

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    ui->recordTable->setModel(model);
    ui->recordTable->verticalHeader()->setVisible(false);
    ui->recordTable->verticalHeader()->setDefaultSectionSize(10);
    ui->recordTable->setShowGrid(false);

    string delimiter = ",";
    string token;
    size_t position;
    for (string entry : entries) {
        position = entry.find(delimiter);
        token = entry.substr(0, position);
        QStandardItem *col1 = new QStandardItem(token.c_str());
        entry.erase(0, position+1);

        position = entry.find(delimiter);
        token = entry.substr(0, position);
        QStandardItem *col2 = new QStandardItem(token.c_str());
        entry.erase(0, position+1);

        QList<QStandardItem*> row;
        row.append(col1);
        row.append(col2);
        model->appendRow(row);
    }
}

void ClinicianUI::on_diagnosisBtn_clicked()
{
    ui->recordTypeLabel->setText("Patient Diagnoses");
    vector<string> diagnoses = clinicianServer.viewTable("diagnosis", myPatient.getId());
    /**
     *  example diagnosis data
    string diag1 = "high blood pressure,13/02/2018";
    string diag2 = "diabetes,03/09/2020";

    diagnoses.push_back(diag1);
    diagnoses.push_back(diag2);
    **/
    currentRecord = "Diagnosis";
    refreshMedicalRecord(diagnoses, currentRecord);
    ui->addToRecBtn->show();
    ui->deleteBtn->show();
    ui->stackedWidget->setCurrentWidget(ui->med_record_view);
}

void ClinicianUI::on_allergiesBtn_clicked()
{
    ui->recordTypeLabel->setText("Patient Allergies");
    vector<string> allergies = clinicianServer.viewTable("allergy", myPatient.getId());
    /**
     *  example allergies data
    string diag1 = "peanut allergy,14/02/2018";
    string diag2 = "pollen,03/04/2012";

    allergies.push_back(diag1);
    allergies.push_back(diag2);
    **/
    currentRecord = "Allergy";
    refreshMedicalRecord(allergies, currentRecord);
    ui->addToRecBtn->show();
    ui->deleteBtn->show();
    ui->stackedWidget->setCurrentWidget(ui->med_record_view);
}

void ClinicianUI::on_prescriptionBtn_clicked()
{
    ui->recordTypeLabel->setText("Patient Prescriptions");
    vector<string> prescriptions = clinicianServer.viewTable("prescription", myPatient.getId());
    /**
     *  example prescriptions data
    string diag1 = "Warfarin,16/04/2018";
    string diag2 = "Ventolin,03/08/2017";

    prescriptions.push_back(diag1);
    prescriptions.push_back(diag2);
    **/
    currentRecord = "Prescription";
    refreshMedicalRecord(prescriptions, currentRecord);
    ui->addToRecBtn->show();
    ui->deleteBtn->show();
    ui->stackedWidget->setCurrentWidget(ui->med_record_view);
}

void ClinicianUI::on_surgeryBtn_clicked()
{
    ui->recordTypeLabel->setText("Patient Surgeries");
    vector<string> surgeries = clinicianServer.viewTable("surgery", myPatient.getId());
    /**
     *  example surgeries data
    string diag1 = "Cardiac Surgery,13/01/2018";
    string diag2 = "Tonsillectomy,14/12/2020";

    surgeries.push_back(diag1);
    surgeries.push_back(diag2);
    **/
    currentRecord = "Surgery";
    refreshMedicalRecord(surgeries, currentRecord);
    ui->addToRecBtn->show();
    ui->deleteBtn->show();
    ui->stackedWidget->setCurrentWidget(ui->med_record_view);
}

void ClinicianUI::on_vaccineBtn_clicked()
{
    ui->recordTypeLabel->setText("Patient Vaccinations");
    vector<string> vaccinations = clinicianServer.viewTable("vaccination", myPatient.getId());
    /**
     *  example vaccinations data
    string diag1 = "Measles,13/07/2018";
    string diag2 = "Covid,03/02/2021";

    vaccinations.push_back(diag1);
    vaccinations.push_back(diag2);
    **/
    currentRecord = "Vaccination";
    refreshMedicalRecord(vaccinations, currentRecord);
    ui->addToRecBtn->show();
    ui->deleteBtn->show();
    ui->stackedWidget->setCurrentWidget(ui->med_record_view);
}

void ClinicianUI::on_diaryBtn_clicked()
{
    ui->recordTypeLabel->setText("Patient Diary Entries");
    vector<string> diaries = clinicianServer.viewTable("diaryEntry", myPatient.getId());
    /**
     * example diaries data
    string diag1 = "felt dizzy today,13/10/2022";
    string diag2 = "high fever,20/04/2022";

    diaries.push_back(diag1);
    diaries.push_back(diag2);
    **/
    currentRecord = "Diary Entry";
    refreshMedicalRecord(diaries, currentRecord);
    ui->addToRecBtn->hide();
    ui->deleteBtn->hide();
    ui->stackedWidget->setCurrentWidget(ui->med_record_view);
}

void ClinicianUI::on_medRecBackBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->patient_record);

}
