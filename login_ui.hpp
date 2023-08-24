/**
 * @file login_ui.hpp
 * @brief Methods declared in this file allows user to log in
 * @author Jessica Liu
 * @bug No known bugs
*/
#ifndef LOGIN_UI_H
#define LOGIN_UI_H

#include "user.hpp"

#include <QWidget>

namespace Ui {
class LoginUI;
}

class LoginUI : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief LoginUI represents the class constructor. A LoginUI object is initialized by a parent widget.
     * @param parent represents the parent Widget, which is set to null by default
     */
    explicit LoginUI(QWidget *parent = nullptr);

    /**
    * @brief ~LoginUI represents the class destructor.
    */
    ~LoginUI();

private slots:

    /**
     * @brief on_loginButton_clicked when user clicks the login button
     */
    void on_loginButton_clicked();

    /**
     * @brief on_registrationLink_clicked when user clicks the registration button
     */
    void on_registrationLink_clicked();

signals:

    /**
     * @brief loggedIn triggers a signal when a user logs in successfully
     * @param user will be passed back to slot function
     */
    void loggedIn(User* user);

    /**
     * @brief registerRequired triggers a signal when user clicks registration link
     */
    void registerRequired();

private:
    Ui::LoginUI *ui;
};

#endif // LOGIN_UI_H
