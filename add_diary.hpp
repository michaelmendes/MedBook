#ifndef ADDDIARY_H
#define ADDDIARY_H

#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>
#include <QDialog>
#include <string>

#include "patient_server.hpp"
#include "patient.hpp"

using namespace std;

namespace Ui {
class AddDiary;
}

class AddDiary : public QDialog
{
    Q_OBJECT

public:
    explicit AddDiary(QWidget *parent = nullptr, Patient* myself = nullptr);
    ~AddDiary();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::AddDiary *ui;
    Patient* patient;


};

#endif // ADDDIARY_H
