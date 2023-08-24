/**
 * @file med_book.hpp
 * @brief compiles all the UI
 *
 * initializes all the different UIs
 * 
 * @author Jessica Liu
 * @bug No known bugs
*/

#ifndef MED_BOOK_HPP
#define MED_BOOK_HPP

#include "clinician_ui.hpp"
#include "family_physician_ui.hpp"
#include "login_ui.hpp"
#include "registration.hpp"
#include "user.hpp"
#include "patient_ui_two.h"

#include <QMainWindow>

namespace Ui {
class MedBook;
}

class MedBook : public QMainWindow
{
    Q_OBJECT

private:
    LoginUI loginUI;
    Registration registration;
    PatientUiTwo patientUI;
    ClinicianUI clinicianUI;
    FamilyPhysicianUI familyPhysicianUI;

public:
    /**
     * @brief constructor
    */
    explicit MedBook(QWidget *parent = nullptr);
    ~MedBook();

private slots:
    /**
     * @brief when loggedIn
     * @param user is a user object
     * @return void
    */
    void on_loggedIn(User* user); // from loginUI
    /**
     * @brief when register required
     * @return void
    */
    void on_registerRequired();   // from loginUI
    /**
     * @brief when user registered
     * @return void
    */
    void on_userRegistered();     // from registration

private:
    Ui::MedBook *ui;
};

#endif // MED_BOOK_HPP
