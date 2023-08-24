/**
 * @file clinician_ui.cpp
 * @brief Methods declared in this file takes the clinician to the page that shows patient record or the page that lets the clinician to submit request for patients
 * 
 * @author Jessica Liu 
 * @bug No known bugs
*/ 
#ifndef CLINICIANUI_HPP
#define CLINICIANUI_HPP

#include <QWidget>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QDebug>
#include <QMessageBox>
#include <QStandardItemModel>

#include <iostream>
#include <string>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "clinician.hpp"
#include "clinician_server.hpp"
#include "patient.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class ClinicianUI; }
QT_END_NAMESPACE


class ClinicianUI : public QWidget
{
    Q_OBJECT

public: 
	 /**
     * @brief ClinicianUI represents the class constructor. A ClinicianUI object is initialized by the LoginServer passing it an optional parent widget, and a Clinician* object.
     *  The constructor initializes a Clinician* class variable with the Clinician* passed and initializes a ClinicianServer object, which will interact with the backend of the program.
     * @param parent represents the parent Widget, which is set to null by default
     * @param myself represents the Clinician who is using this UI
     */
    ClinicianUI(QWidget *parent = nullptr, Clinician* myself = nullptr); 
     /**
     * @brief ClinicianUI represents the class destructor. 
     */
    ~ClinicianUI();
	/**
     * @brief init initializes the class variables once the UI Widget has been linked to the LoginServer.
     * @param myself represents the clinician that is logged in
     */
    void init(Clinician* myself = nullptr);

private slots:
    //void on_addPatientBtn_clicked();
    //void on_removePatientBtn_clicked(); 
    /**
    * @brief on_viewRecordBtn_clicked is executed when the "View Record" button is pressed from the Home Page. This takes the clinician onto the patient medical record overivew.
    */
    void on_viewRecordBtn_clicked();
    //void on_formBackBtn_clicked(); 
    /**
    * @brief on_recordBackBtn_clicked returns the user to the Home Page from the record view.
    */
    void on_recordBackBtn_clicked(); 
    /**
    * @brief on_infoBackBtn_clicked returns user to record view.
    */
    void on_infoBackBtn_clicked();
    //void on_formSubmitBtn_clicked(); 
    /**
    * @brief on_requestBackBtn_clicked returns the user to the Home Page from the request page.
    */
    void on_requestBackBtn_clicked(); 
    /**
    * @brief on_notifBackBtn_clicked returns to the Home Screen from the notifications screen.
    */
    void on_submitRequestBtn_clicked(); 
    /**
    * @brief on_transferBtn_clicked the transfer request page is launched
    */
    void on_transferBtn_clicked();

    //void on_editRecordBtn_clicked();
	/**
    * @brief on_diagnosisBtn_clicked opens the diagnosis view
    */
    void on_diagnosisBtn_clicked();
	/**
    * @brief on_medRecBackBtn_clicked returns the user to the patient record view
    */
    void on_medRecBackBtn_clicked();

    //void on_saveBtn_clicked();

    //void on_addToRecBtn_clicked();

    //void on_entryBackBtn_clicked();

    //void on_addEntryBtn_clicked(); 
    /**
    * @brief on_allergiesBtn_clicked opens allergy view of medical record
    */
    void on_allergiesBtn_clicked(); 
    /**
    * @brief on_prescriptionBtn_clicked_clicked opens allergy view of medical record
    */
    void on_prescriptionBtn_clicked(); 
    /**
    * @brief on_surgeryBtnn_clicked opens allergy view of medical record
    */
    void on_surgeryBtn_clicked(); 
    /**
    * @brief on_vaccineBtn_clicked opens allergy view of medical record
    */
    void on_vaccineBtn_clicked();
	/**
    * @brief on_diaryBtn_clicked opens allergy view of medical record
    */
    void on_diaryBtn_clicked();

private: 
	/**
    * @brief refreshMain is a helper method that refreshes the patient table on the main page
    */
    void refreshMain(); 
    /**
    * @brief editRecord is a method that lets clinician edit record 
    */
    void editRecord(Patient patient, std::string editCommand, std::string editorParams);
	 /**
    * @brief refreshMedicalRecord is a method that lets clinician refresh 
    */
    void refreshMedicalRecord(std::vector<std::string> entries, std::string col1);
	//private variables 
    Ui::ClinicianUI *ui;

    Clinician *clinician;
    std::vector<Patient> patientList;
    Patient myPatient;

    ClinicianServer clinicianServer;

    std::string currentRecord;
};

#endif // CLINICIANUI_HPP



