/**
 * @file patient_ui_two.hpp
 * @brief Methods in this file takes the patient to the page that shows record or the page that lets the patient add entry to diary
 *
 * @author Amreen Anbar
 * @bug No known bugs
*/
#ifndef PATIENTUITWO_H
#define PATIENTUITWO_H

#include <QDialog>
#include "add_diary.hpp"
#include "view_record.hpp"
#include <QStandardItemModel>
#include "patient.hpp"

namespace Ui {
class PatientUiTwo;
}

class PatientUiTwo : public QDialog
{
    Q_OBJECT

//public:
//    explicit PatientUiTwo(QWidget *parent = nullptr,Patient newpatient);
//    ~PatientUiTwo();
public:
    /**
    *@brief Constructor for the class.
    *
    *@param parent represents the parent Widget, which is set to null by default
    */
    explicit PatientUiTwo(QWidget *parent = nullptr, Patient* currPatient = nullptr);
     /**
    *@brief Destructor for the class.
    */
    ~PatientUiTwo();

    void init(Patient* myself);


private slots:
    /**
     * @brief This button takes to the ui that views patient record
     */
    void on_pushButton_clicked();
     /**
     * @brief This button takes to the ui that takes to the page to add diary entries
     */
    void on_pushButton_2_clicked();

private:
    //private variables
    Ui::PatientUiTwo *ui;
    Patient* patient;
    AddDiary *adddiary;
    ViewRecord *viewrecord;
};

#endif // PATIENTUITWO_H
