#ifndef PATIENT_UI_TWO_H
#define PATIENT_UI_TWO_H

#include <QDialog>
#include <add_diary.hpp>
#include <view_diary.hpp>
#include <view_record.hpp>
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
    explicit PatientUiTwo(QWidget *parent = nullptr);
    ~PatientUiTwo();


private slots:
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

private:
    Ui::PatientUiTwo *ui;
//    Patient patient;
    AddDiary *adddiary;
    ViewRecord *viewrecord;
};

#endif // PATIENT_UI_TWO_H
