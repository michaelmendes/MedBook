#include "view_diary.hpp"
#include "ui_view_diary.h"
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <QDateTime>
#include <QDebug>
#include <QTextEdit>
#include <QDialog>
#include <QLabel>
#include "patient_server.hpp"

using namespace std;

ViewDiary::ViewDiary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDiary)
{
    ui->setupUi(this);
    QLabel *label = new QLabel(this);
    PatientServer obj4;
    vector<string> printdiary = obj4.viewDiaryPatient(); //view where?
    string str;
    str = accumulate(printdiary.begin(), printdiary.end(), str); //from vector string to string
    QString qstr = QString::fromStdString(str); //from string to qstring
    label->setText(qstr);
}

ViewDiary::~ViewDiary()
{
    delete ui;
}


