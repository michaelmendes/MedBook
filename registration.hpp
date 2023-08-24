/**
 * @file registration.hpp
 * @brief the registration
 *
 * deals with the registration page
 * 
 * @author Jessica Liu
 * @bug No known bugs
*/

#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>

namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief constructor
    */
    explicit Registration(QWidget *parent = nullptr);
	/**
     * @brief deconstructor
    */
    ~Registration();

private slots:
    /**
     * @brief when register button is clicked
     * @return void
    */
    void on_registerButton_clicked();

signals:
    /**
     * @brief when user is registered
     * @return void
    */
    void userRegistered();

private:
    Ui::Registration *ui;
};

#endif // REGISTRATION_H
