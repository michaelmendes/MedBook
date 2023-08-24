/**
 * @file view_record.cpp
 * @brief The patient can mention a table name which basically is the category of record the patient wants for him/herself
 * The records are presented in a table format with entry and corresponding date.
 *
 * @author Amreen Anbar
 * @bug No known bugs
*/
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <QDateTime>
#include <QDebug>
#include <QTextEdit>
#include <QDialog>
#include <QStandardItemModel>
#include <QTableView>
#include <QStringList>
#include <QStackedWidget>

#include "view_record.hpp"
#include "ui_view_record.h"
#include "patient_server.hpp"

using namespace std;


ViewRecord::ViewRecord(QWidget *parent, Patient* myself) :
    QDialog(parent),
    ui(new Ui::ViewRecord)
{
    //ui now is set to be this
    ui->setupUi(this);
    //stacked widget used for each category to be shown in different pages
    ui->stackedWidget->setCurrentWidget(this);
    patient = myself;
}

ViewRecord::~ViewRecord()
{
    delete ui;
}
//view allergy
void ViewRecord::on_pushButton_clicked()
{
    //server object created to get the records from each category when asked for
    patientServer server(patient);
    //entries as the allergy records
    vector<string> entries = server.viewMedicalRecordPatient("allergy");
    //string currentRecord = "Allergy";
    QStringList horizontalHeader;
    QStringList verticalHeader;

    horizontalHeader.append("Date");
    horizontalHeader.append("Allergy");

    QStandardItemModel *model = new QStandardItemModel();

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    ui->tableAllergy->setModel(model);
    ui->tableAllergy->verticalHeader()->setVisible(false);
    ui->tableAllergy->verticalHeader()->setDefaultSectionSize(10);
    ui->tableAllergy->setShowGrid(false);
   string delimiter = ",";
   string token;
   size_t position;
   //setting up enties with dates on the table
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
    //go to this page to show the table made
    ui->stackedWidget->setCurrentWidget(ui->page_allergy);
}
//view vaccination
void ViewRecord::on_pushButton_4_clicked()
{
    patientServer server(patient);
    vector<string> entries = server.viewMedicalRecordPatient("vaccination");
    QStringList horizontalHeader;
    QStringList verticalHeader;

    horizontalHeader.append("Date");
    horizontalHeader.append("Vaccination");

    QStandardItemModel *model = new QStandardItemModel();

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    ui->tableVaccination->setModel(model);
    ui->tableVaccination->verticalHeader()->setVisible(false);
    ui->tableVaccination->verticalHeader()->setDefaultSectionSize(10);
    ui->tableVaccination->setShowGrid(false);
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
    ui->stackedWidget->setCurrentWidget(ui->page_vaccination); //go to this page
}
//view diagnosis history
void ViewRecord::on_pushButton_3_clicked()
{
    patientServer server(patient);
    vector<string> entries = server.viewMedicalRecordPatient("diagnosis");
    QStringList horizontalHeader;
    QStringList verticalHeader;

    horizontalHeader.append("Date");
    horizontalHeader.append("Diagnosis");

    QStandardItemModel *model = new QStandardItemModel();

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    ui->tableDiagnosis->setModel(model);
    ui->tableDiagnosis->verticalHeader()->setVisible(false);
    ui->tableDiagnosis->verticalHeader()->setDefaultSectionSize(10);
    ui->tableDiagnosis->setShowGrid(false);
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
    ui->stackedWidget->setCurrentWidget(ui->page_diagnosis); //go to this page
}

//view prescriptions
void ViewRecord::on_pushButton_2_clicked()
{
   patientServer server(patient);
   vector<string> entries = server.viewMedicalRecordPatient("prescription");
    QStringList horizontalHeader;
    QStringList verticalHeader;

    horizontalHeader.append("Date");
    horizontalHeader.append("Prescription");

    QStandardItemModel *model = new QStandardItemModel();

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    ui->tablePrescription->setModel(model);
    ui->tablePrescription->verticalHeader()->setVisible(false);
    ui->tablePrescription->verticalHeader()->setDefaultSectionSize(10);
    ui->tablePrescription->setShowGrid(false);
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
    ui->stackedWidget->setCurrentWidget(ui->page_prescription); //go to this page
}

//view surgical history
void ViewRecord::on_pushButton_5_clicked()
{
   patientServer server(patient);
   vector<string> entries = server.viewMedicalRecordPatient("surgery");
    QStringList horizontalHeader;
    QStringList verticalHeader;

    horizontalHeader.append("Date");
    horizontalHeader.append("Surgery");

    QStandardItemModel *model = new QStandardItemModel();

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    ui->tableSurgery->setModel(model);
    ui->tableSurgery->verticalHeader()->setVisible(false);
    ui->tableSurgery->verticalHeader()->setDefaultSectionSize(10);
    ui->tableSurgery->setShowGrid(false);
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
    ui->stackedWidget->setCurrentWidget(ui->page_surgery); //go to this page

}

//view diary
void ViewRecord::on_pushButton_6_clicked()
{
    patientServer server(patient);
    vector<string> entries = server.viewMedicalRecordPatient("diaryEntry");
    QStringList horizontalHeader;
    QStringList verticalHeader;

    horizontalHeader.append("Date");
    horizontalHeader.append("Diary Entry");

    QStandardItemModel *model = new QStandardItemModel();

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    ui->tableView_2->setModel(model);
    ui->tableView_2->verticalHeader()->setVisible(false);
    ui->tableView_2->verticalHeader()->setDefaultSectionSize(10);
    ui->tableView_2->setShowGrid(false);
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
    ui->stackedWidget->setCurrentWidget(ui->page); //go to this page

}

/* void ViewRecord::showRecord( string col1)
//void ViewRecord::showRecord(vector<string> entries, string col1)
{
    //tableView
    QStringList horizontalHeader;
    QStringList verticalHeader;

    horizontalHeader.append("Date");
    horizontalHeader.append(col1.c_str());

    QStandardItemModel *model = new QStandardItemModel();

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    ui->tableAllergy->setModel(model);
    ui->tableAllergy->verticalHeader()->setVisible(false);
    ui->tableAllergy->verticalHeader()->setDefaultSectionSize(10);
    ui->tableAllergy->setShowGrid(false);
//    string delimiter = ",";
//    string token;
//    size_t position;
//    for (string entry : entries) {
//        position = entry.find(delimiter);
//        token = entry.substr(0, position);
//        QStandardItem *col1 = new QStandardItem(token.c_str());
//        entry.erase(0, position+1);

//        position = entry.find(delimiter);
//        token = entry.substr(0, position);
//        QStandardItem *col2 = new QStandardItem(token.c_str());
//        entry.erase(0, position+1);

//        QList<QStandardItem*> row;
//        row.append(col1);
//        row.append(col2);
//        model->appendRow(row);
//    }
}
*/
