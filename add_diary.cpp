/**
 * @file add_diary.cpp
 * @brief The patient can add entry and date or ask for the interface to close.The methods for these are defined here.
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
#include <string>
#include <QStackedWidget>

#include "add_diary.hpp"
#include "ui_add_diary.h"
#include "patient_server.hpp"

using namespace std;

AddDiary::AddDiary(QWidget *parent, Patient* myself) :
    QDialog(parent),
    ui(new Ui::AddDiary)
{
    //the ui is set to be this file
    ui->setupUi(this);
    patient = myself;
}

AddDiary::~AddDiary()
{
    delete ui;
}

void AddDiary::on_pushButton_clicked() //save diary to database
{
    //creates a server object(svr) of patientServer class to eventually send entry to server
       patientServer server(patient);
       qDebug() << "User clicked add entry";
       bool validEntry = true;
       string entry;
       string date;
       //To check if line is empty or not and store the entry
       if (!ui->lineEdit->text().isEmpty()) {
           entry = ui->lineEdit->text().toStdString();
       }
       else {
           QMessageBox::information(this, "Message", "Missing entry", QMessageBox::Ok);
           validEntry = false;
       }
       //To check if date is empty or not and store the entry
       if (!ui->lineEdit_2->text().isEmpty()) {
           date = ui->lineEdit_2->text().toStdString();
       }
       else {
           QMessageBox::information(this, "Message", "Missing date", QMessageBox::Ok);
           validEntry = false;
       }
       if (validEntry == true)
       {
           //transfer the strings with entry and date separated by commas
           string transferParams = entry + "," + date;
           server.writeDiaryPatient(transferParams);
           ui->lineEdit->setText("");
           ui->lineEdit_2->setText("");
       }
}

void AddDiary::on_pushButton_2_clicked() //close
{
    //Checks if the interface is to be closed or not
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Close Diary","Are you sure you want to quit?",
                                        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}


