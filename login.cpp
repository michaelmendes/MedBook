#include "login.hpp"
#include "user_service.hpp"

#include "ui_login.h"

#include <QDebug>
#include <iostream>

using namespace std;

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->errorLabel->hide();
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    cout << "This is from Login::on_loginButton_clicked" << endl;
    ui->errorLabel->hide();

    QString email = ui->emailEdit->text();
    cout << "This is from Login::on_loginButton_clicked email = " << email.toStdString() << endl;

    User user;
    user.setEmail( ui->emailEdit->text().toStdString());
    user.setPassword( ui->passwordEdit->text().toStdString());

    // TODO validate email and password, make sure not empty string

    UserService userService;
    User* existing = userService.login(&user);

    if (existing == nullptr) {
        // failed to log in
        ui->errorLabel->show();
        return;
    }
    emit loggedIn(existing);
}

void Login::on_registrationLink_clicked()
{
    cout << "This is from Login::on_registrationLink_clicked" << endl;
    emit registerRequired();
}

