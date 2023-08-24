#include "registration.hpp"
#include "user.hpp"
#include "login_server.hpp"

#include "ui_registration.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

Registration::Registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
    ui->errorLabel->hide();
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_registerButton_clicked()
{
    cout << "This is from Registration::on_registerButton_clicked" << endl;
    ui->errorLabel->hide();

    User user;
    user.setType(ui->userNameEdit->text().toStdString());
    user.setName(ui->firstNameEdit->text().toStdString());
    user.setPassword(ui->passwordEdit->text().toStdString());
    user.setType(ui->userTypeBox->currentText().toStdString());

    // TODO validate input, if fail, show error

    LoginServer loginServer;
    if (!loginServer.registerUser(&user)) {
        // failed to register user
        ui->errorLabel->show();
        return;
    }

    emit userRegistered();
}

