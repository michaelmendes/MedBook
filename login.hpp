/**
 * @file login.hpp
 * @brief the login ui
 *
 * creates the functionality for the login
 * 
 * @author Jessica Liu
 * @bug No known bugs
*/
#ifndef LOGIN_HPP
#define LOGIN_HPP

#include "User.hpp"

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief constructor
    */
    explicit Login(QWidget *parent = nullptr);
    /**
     * @brief deconstructor
    */
    ~Login();

private slots:
    /**
     * @brief when login button link is clicked
     * @return void
    */
    void on_loginButton_clicked();
    /**
     * @brief when register link is clicked
     * @return void
    */
    void on_registrationLink_clicked();

signals:
    /**
     * @brief the user is logged in
     * @param user is a user object
     * @return void
    */
    void loggedIn(User* user);
    /**
     * @brief register is required
     * @return void
    */
    void registerRequired();

private:
    Ui::Login *ui;
};

#endif // LOGIN_HPP
