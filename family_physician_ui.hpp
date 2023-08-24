/**
 * @file add_diary.hpp
 * @brief Methods in patient server allows the patient to add entry to their diary
 * 
 * The patient can add entry and date or ask for the interface to close.  
 * @author Amreen Anbar
 * @bug No known bugs
*/
#ifndef FAMILY_PHYSICIAN_UI_H
#define FAMILY_PHYSICIAN_UI_H

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
#include <ctype.h>

#include "family_physician_server.hpp"
#include "patient.hpp"
#include "family_physician.hpp"
#include "ui_family_physician.h"
//#include "physician_ui_tester.hpp"


// Forward Declarations
class Patient;
class FamilyPhysicianServer;

QT_BEGIN_NAMESPACE
namespace Ui { class FamilyPhysicianUI; }
QT_END_NAMESPACE

/**
 * @brief The FamilyPhysicianUI class amilyPhysicianUI represents the UI for users of type Family Physician. The home screen of this UI features a table that displays all of the Family Physician's patients.
     *  This UI has functionalities to add a new patient, remove a current patient, request the transfer of a patient from another family physician, and view the medical record of
     *  a selected patient.
 */
class FamilyPhysicianUI : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief FamilyPhysicianUI represents the class constructor. A FamilyPhysicianUI object is initialized by the LoginServer passing it an optional parent widget, and a FamilyPhysician* object.
     *  The constructor initializes a FamilyPhysician* class variable with the FamilyPhysician* passed and initializes a FamilyPhysicianServer object, which will interact with the backend of the program.
     * @param parent represents the parent Widget, which is set to null by default
     * @param myself represents the Family Physician who is using this UI
     * @author Michael Mendes
     */
    FamilyPhysicianUI(QWidget *parent = nullptr, FamilyPhysician* myself = nullptr);
    /**
     * @brief ~FamilyPhysicianUI is the class destructor. It delete the UI.
     */
    ~FamilyPhysicianUI();
    /**
     * @brief init initializes the class variables once the UI Widget has been linked to the LoginServer.
     * @param myself represents the family physician that is logged in
     */
    void init(FamilyPhysician* myself = nullptr);

private slots:
    /**
     * @brief on_addPatientBtn_clicked is executed when the "Add Patient" button is presed from the Home Page and redirects the user to the "Add Patient" form.
     */
    void on_addPatientBtn_clicked();
    /**
     * @brief on_removePatientBtn_clicked is executed when the "Remove Patient" button is presed from the Home Page. This will promt the user to confirm the deletion and then signals to the
     *  server to remove this patient.
     */
    void on_removePatientBtn_clicked();
    /**
     * @brief on_viewRecordBtn_clicked is executed when the "View Record" button is pressed from the Home Page. This takes the family physician onto the patient medical record overivew.
     */
    void on_viewRecordBtn_clicked();
    /**
     * @brief on_formBackBtn_clicked returns the user to the Home Page from the add patient form.
     */
    void on_formBackBtn_clicked();
    /**
     * @brief on_recordBackBtn_clicked returns the user to the Home Page from the record view.
     */
    void on_recordBackBtn_clicked();
    /**
     * @brief on_infoBackBtn_clicked returns user to record view.
     */
    void on_infoBackBtn_clicked();
    /**
     * @brief on_formSubmitBtn_clicked submits the new patient information to the server to be added to the physician's database.
     */
    void on_formSubmitBtn_clicked();
    /**
     * @brief on_requestBackBtn_clicked returns the user to the Home Page from the request page.
     */
    void on_requestBackBtn_clicked();
    /**
     * @brief on_submitRequestBtn_clicked submits a patient transfer request to the server.
     */
    void on_submitRequestBtn_clicked();
    /**
     * @brief on_notifBackBtn_clicked returns to the Home Screen from the notifications screen.
     */
    void on_notifBackBtn_clicked();
    /**
     * @brief on_acceptBtn_clicked executes when the physician decides to accept a patient transfer. The acceptance is sent to the server which updates the database.
     */
    void on_acceptBtn_clicked();
    /**
     * @brief on_transferBtn_clicked the transfer request page is launched
     */
    void on_transferBtn_clicked();
    /**
     * @brief on_notifications_clicked the notifications page is launched, which displays all incoming patioent transfer and record view requests from other clinicians.
     */
    void on_notifications_clicked();
    /**
     * @brief on_deleteBtn_clicked allows the physician to delete an entry from a patient record
     */
    void on_deleteBtn_clicked();
    /**
     * @brief on_diagnosisBtn_clicked opens the diagnosis view
     */
    void on_diagnosisBtn_clicked();
    /**
     * @brief on_medRecBackBtn_clicked returns the user to the patient record view
     */
    void on_medRecBackBtn_clicked();
    /**
     * @brief on_saveBtn_clicked unneeded.
     */
    void on_saveBtn_clicked();
    /**
     * @brief on_addToRecBtn_clicked adds new entry to the medical record
     */
    void on_addToRecBtn_clicked();
    /**
     * @brief on_entryBackBtn_clicked returns the user to the patient record
     */
    void on_entryBackBtn_clicked();
    /**
     * @brief on_addEntryBtn_clicked takes the user to the add entry page to enter the information for the new entry of the corresponding record
     */
    void on_addEntryBtn_clicked();
    /**
     * @brief on_allergiesBtn_clicked opens allergy view of medical record
     */
    void on_allergiesBtn_clicked();
    /**
     * @brief on_prescriptionBtn_clicked opens prescription view of medical record
     */
    void on_prescriptionBtn_clicked();
    /**
     * @brief on_surgeryBtn_clicked opens surgeries view of medical record
     */
    void on_surgeryBtn_clicked();
    /**
     * @brief on_vaccineBtn_clicked opens vaccinations view of medical record
     */
    void on_vaccineBtn_clicked();
    /**
     * @brief on_diaryBtn_clicked opens diary entries view of medical record
     */
    void on_diaryBtn_clicked();

private:
    /**
     * @brief refreshMain is a helper method that refreshes the patient table on the main page
     */
    void refreshMain();
    /**
     * @brief loadRequests is a helper function that refreshes the family physician's list of transfer requests and record view requests
     */
    void loadRequests();
    /**
     * @brief refreshMedicalRecord is a helper funnction that fetches the record from the database for the correponding aspect of the patient's medical record
     */
    void refreshMedicalRecord(std::vector<std::string> entries, std::string col1);

    // below are the global private variables
    Ui::FamilyPhysicianUI *ui;
    FamilyPhysician *physician;
    std::vector<Patient> patientList;
    //PhysicianUiTester server;
    FamilyPhysicianServer server;
    Patient myPatient;
    std::string currentRecord;
};

#endif // FAMILY_PHYSICIAN_UI_H

