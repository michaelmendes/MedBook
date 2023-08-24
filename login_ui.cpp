#include "login_ui.hpp"
#include "login_server.hpp"

#include "ui_login.h"

#include <QDebug>
#include <iostream>

using namespace std;

LoginUI::LoginUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginUI)
{
    ui->setupUi(this);
    ui->errorLabel->hide();
}

LoginUI::~LoginUI()
{
    delete ui;
}

void LoginUI::on_loginButton_clicked()
{
    cout << "This is from Login::on_loginButton_clicked" << endl;
    ui->errorLabel->hide();

    User user;
    user.setId(ui->userIdEdit->text().toInt());
    user.setPassword( ui->passwordEdit->text().toStdString());
    user.setType(ui->userTypeBox->currentText().toStdString());

    // TODO validate userName and password, make sure not empty string

    LoginServer loginServer;
    User* existing = loginServer.login(&user);

    if (existing == nullptr) {
        // failed to log in
        ui->errorLabel->show();
        return;
    }
    emit loggedIn(existing);
}

void LoginUI::on_registrationLink_clicked()
{
    cout << "This is from Login::on_registrationLink_clicked" << endl;
    emit registerRequired();
}

