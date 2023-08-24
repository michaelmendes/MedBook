#include "family_physician_ui.hpp"
#include "ui_family_physician.h"



using namespace std;


FamilyPhysicianUI::FamilyPhysicianUI(QWidget *parent, FamilyPhysician* myself)
    : QWidget(parent)
    , ui(new Ui::FamilyPhysicianUI)
    , physician(myself)
    , server(myself)
{
    ui->setupUi(this);

    init(myself);
}

FamilyPhysicianUI::~FamilyPhysicianUI()
{
    delete ui;
}

void FamilyPhysicianUI::init(FamilyPhysician* myself) {

    physician = myself;

    if (myself != nullptr) {
        server.setFamilyPhysician(myself);

        refreshMain();

        ui->stackedWidget->setCurrentWidget(ui->main_page);
        cout << physician->getId() << "  " << physician->getName() << endl; 
    }
}

void FamilyPhysicianUI::refreshMain()
{
    ui->physicianNameLabel->setText(QString::fromStdString(physician->getName()));

    //patientList = test.getPatients();
    patientList = server.getPatients();

    QStringList horizontalHeader;
    QStringList verticalHeader;

    // NOW just populate the table with these values
    horizontalHeader.append("Patient ID");
    horizontalHeader.append("Patient Name");

    QStandardItemModel *model = new QStandardItemModel();

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    ui->patientTable->setModel(model);
    ui->patientTable->verticalHeader()->setVisible(false);
    ui->patientTable->verticalHeader()->setDefaultSectionSize(10);
    ui->patientTable->setShowGrid(false);

    for (Patient patient : patientList) {
        QStandardItem *col1 = new QStandardItem(to_string(patient.getId()).c_str());
        QStandardItem *col2 = new QStandardItem(patient.getName().c_str());
        QList<QStandardItem*> row;
        row.append(col1);
        row.append(col2);
        model->appendRow(row);
    }
}

// FAMILY PHYSICIAN MAIN UI BUTTONS
void FamilyPhysicianUI::on_addPatientBtn_clicked()
{
    qDebug() << "User clicked add patient button";
    ui->stackedWidget->setCurrentWidget(ui->new_patient);
}

void FamilyPhysicianUI::on_removePatientBtn_clicked()
{
    qDebug() << "User clicked remove patient";
    QItemSelectionModel *selection = ui->patientTable->selectionModel();
    if (selection->hasSelection() && selection->selectedRows().size() == 1)
    {
        QMessageBox deletePatient;
        deletePatient.setText("Are you sure you want to delete this patient?");
        QPushButton *deleteButton = deletePatient.addButton(tr("Delete Patient"), QMessageBox::ActionRole);
        deletePatient.addButton(QMessageBox::Cancel);
        deletePatient.exec();
        if (deletePatient.clickedButton() == deleteButton)
        {
            int row = selection->selectedRows().at(0).row();
            QModelIndex idIndex = ui->patientTable->model()->index(row,0); // 0 is col
            myPatient.setId(ui->patientTable->model()->data(idIndex).toString().toInt());
            QModelIndex nameIndex = ui->patientTable->model()->index(row,1); // 1 is col
            myPatient.setName(ui->patientTable->model()->data(nameIndex).toString().toStdString());

            server.removeMedicalRecord(myPatient);
            cout << "Patient Removed" << endl;
            refreshMain();
        }
    }
    else
    {
        QMessageBox::information(this, "Message", "No patient selected", QMessageBox::Ok);
    }
}

void FamilyPhysicianUI::on_viewRecordBtn_clicked()
{
    qDebug() << "User clicked view record";

    QItemSelectionModel *selection = ui->patientTable->selectionModel();
    if (selection->hasSelection() && selection->selectedRows().size() == 1)
    {
        int row = selection->selectedRows().at(0).row();

        QModelIndex idIndex = ui->patientTable->model()->index(row,0); // 0 is col
        int patientId;
        try {
            patientId = ui->patientTable->model()->data(idIndex).toString().toInt();
        }
        catch (const invalid_argument&) {
            QMessageBox::information(this, "Message", "Please enter a valid ID", QMessageBox::Ok);
        }
        for (Patient patient : patientList)
        {
            if (patient.getId() == patientId)
            {
                myPatient = patient;
                break;
            }
        }
        cout << patientId << "  " << myPatient.getName() << myPatient.getBirth() << endl;

        ui->idLabel->setText(QString::fromStdString(to_string(myPatient.getId())));
        ui->nameLabel->setText(QString::fromStdString(myPatient.getName()));
        ui->ageLabel->setText(QString::fromStdString(myPatient.getBirth()));
        ui->sexLabel->setText(QString::fromStdString(myPatient.getSex()));

        ui->stackedWidget->setCurrentWidget(ui->patient_record);
    }
    else
    {
        QMessageBox::information(this, "Message", "No patient selected", QMessageBox::Ok);
    }
}

void FamilyPhysicianUI::on_transferBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->request_page);
}


void FamilyPhysicianUI::on_notifications_clicked()
{
    server.viewRequests();
    loadRequests();
    ui->stackedWidget->setCurrentWidget(ui->notifs_page);

}


// helper function to load physicians requests
void FamilyPhysicianUI::loadRequests()
{
    vector<string> requests = physician->getRequests();
    QStringList horizontalHeader;
    QStringList verticalHeader;

    horizontalHeader.append("Request Type");
    horizontalHeader.append("Patient ID");
    horizontalHeader.append("Patient Name");
    horizontalHeader.append("Requesting Physician ID");
    horizontalHeader.append("Requesting Physician Name");

    QStandardItemModel *model = new QStandardItemModel();

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    ui->requestsTable->setModel(model);
    ui->requestsTable->verticalHeader()->setVisible(false);
    ui->requestsTable->verticalHeader()->setDefaultSectionSize(10);
    ui->requestsTable->setShowGrid(false);

    string delimiter = ",";
    string token;
    size_t position;
    for (string request : requests) {
        cout << "New Request: " << request << endl;
        position = request.find(delimiter);
        token = request.substr(0, position);
        QStandardItem *col1 = new QStandardItem(token.c_str());
        request.erase(0, position+1);

        position = request.find(delimiter);
        token = request.substr(0, position);
        QStandardItem *col2 = new QStandardItem(token.c_str());
        request.erase(0, position+1);

        position = request.find(delimiter);
        token = request.substr(0, position);
        QStandardItem *col3 = new QStandardItem(token.c_str());
        request.erase(0, position+1);

        position = request.find(delimiter);
        token = request.substr(0, position);
        QStandardItem *col4 = new QStandardItem(token.c_str());
        request.erase(0, position+1);

        position = request.find(delimiter);
        token = request.substr(0, position);
        QStandardItem *col5 = new QStandardItem(token.c_str());
        request.erase(0, position+1);

        QList<QStandardItem*> row;
        row.append(col1);
        row.append(col2);
        row.append(col3);
        row.append(col4);
        row.append(col5);
        model->appendRow(row);
    }
}


// NEW PATIENT FORM BUTTONS

void FamilyPhysicianUI::on_formSubmitBtn_clicked()
{
    qDebug() << "User clicked submit new patient form";
    bool validPatient = true;
    if (!ui->patientIdLine->text().isEmpty()) {
        try {
            int id = ui->patientIdLine->text().toInt();
            myPatient.setId(id);
        }
        catch (const invalid_argument&) {
            QMessageBox::information(this, "Message", "Please enter a valid ID", QMessageBox::Ok);
            validPatient = false;
        }
    }
    else {
        QMessageBox::information(this, "Message", "Missing patient ID", QMessageBox::Ok);
        validPatient = false;
    }
    if (!ui->patientNameLine->text().isEmpty()) {
        myPatient.setName(ui->patientNameLine->text().toStdString());
    }
    else {
        QMessageBox::information(this, "Message", "Missing patient name", QMessageBox::Ok);
        validPatient = false;
    }
    if (!ui->patientAgeLine->text().isEmpty()) {
        myPatient.setBirth(ui->patientAgeLine->text().toStdString());
    }
    else {
        QMessageBox::information(this, "Message", "Missing patient date of birth", QMessageBox::Ok);
        validPatient = false;
    }
    if (!ui->patientSexLine->text().isEmpty()) {
        myPatient.setSex(ui->patientSexLine->text().toStdString());
    }
    else {
        QMessageBox::information(this, "Message", "Missing patient sex", QMessageBox::Ok);
        validPatient = false;
    }
    if (validPatient == true)
    {
        server.addMedicalRecord(myPatient);
        ui->patientIdLine->setText("");
        ui->patientNameLine->setText("");
        ui->patientAgeLine->setText("");
        ui->patientSexLine->setText("");
        refreshMain();
        ui->stackedWidget->setCurrentWidget(ui->main_page);
    }
}

void FamilyPhysicianUI::on_formBackBtn_clicked()
{
    qDebug() << "User returned to home";
    refreshMain();
    ui->stackedWidget->setCurrentWidget(ui->main_page);
}



// PATIENT RECORD BUTTONS
void FamilyPhysicianUI::on_recordBackBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main_page);
}



// INFO SCREEN BUTTONS
void FamilyPhysicianUI::on_infoBackBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->patient_record);
}



// TRANSFER REQUEST BUTTONS
void FamilyPhysicianUI::on_requestBackBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main_page);
}


void FamilyPhysicianUI::on_submitRequestBtn_clicked()
{
    qDebug() << "User clicked submit transfer request";
    bool validRequest = true;
    int currPhysicianId = -1;
    string currPhysicianName;
    if (!ui->patientIdLine_2->text().isEmpty()) {
        try {
            int id = ui->patientIdLine_2->text().toInt();
            myPatient.setId(id);
        }
        catch (const invalid_argument&) {
            QMessageBox::information(this, "Message", "Please enter a valid patient ID", QMessageBox::Ok);
            validRequest = false;
        }
    }
    else {
        QMessageBox::information(this, "Message", "Missing patient ID", QMessageBox::Ok);
        validRequest = false;
    }
    if (!ui->patientNameLine_2->text().isEmpty()) {
        myPatient.setName(ui->patientNameLine_2->text().toStdString());
    }
    else {
        QMessageBox::information(this, "Message", "Missing patient name", QMessageBox::Ok);
        validRequest = false;
    }
    if (!ui->physicianIdLine->text().isEmpty()) {
        try {
            currPhysicianId = ui->physicianIdLine->text().toInt();
        }
        catch (const invalid_argument&) {
            QMessageBox::information(this, "Message", "Please enter a valid physician ID", QMessageBox::Ok);
            validRequest = false;
        }
    }
    else {
        QMessageBox::information(this, "Message", "Missing current physician ID", QMessageBox::Ok);
        validRequest = false;
    }
    if (!ui->physicianNameLine->text().isEmpty()) {
        currPhysicianName= ui->physicianNameLine->text().toStdString();
    }
    else {
        QMessageBox::information(this, "Message", "Missing current physician name", QMessageBox::Ok);
        validRequest = false;
    }
    if (validRequest == true)
    {
        server.sendRequest("Transfer", &myPatient, currPhysicianId);
        ui->patientIdLine_2->setText("");
        ui->patientNameLine_2->setText("");
        ui->physicianIdLine->setText("");
        ui->physicianNameLine->setText("");
        ui->stackedWidget->setCurrentWidget(ui->main_page);
    }
}


// NOTIFICATIONS PAGE BUTTONS
void FamilyPhysicianUI::on_notifBackBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main_page);
}


void FamilyPhysicianUI::on_acceptBtn_clicked()
{
    qDebug() << "User clicked Approve Request";
    QItemSelectionModel *selection = ui->requestsTable->selectionModel();
    if (selection->hasSelection() && selection->selectedRows().size() == 1)
    {
        int row = selection->selectedRows().at(0).row();
        QModelIndex requestIndex = ui->requestsTable->model()->index(row,0); // 0 is col
        string requestType =  ui->requestsTable->model()->data(requestIndex).toString().toStdString();
        QMessageBox requestMsg;
        QPushButton *confirmButton;
        if (requestType == "Transfer")
        {
            requestMsg.setText("Are you sure you want to transfer this patient?");
            confirmButton = requestMsg.addButton(tr("Transfer Patient"), QMessageBox::ActionRole);
        }
        else
        {
            requestMsg.setText("Are you sure you want to share patient medical record?");
            confirmButton = requestMsg.addButton(tr("Send Record"), QMessageBox::ActionRole);
        }
        requestMsg.addButton(QMessageBox::Cancel);
        requestMsg.exec();
        if (requestMsg.clickedButton() == confirmButton)
        {
            QModelIndex patientIdIndex = ui->requestsTable->model()->index(row,1); // 1 is col
            try {
                myPatient.setId(ui->requestsTable->model()->data(patientIdIndex).toString().toInt());
            }
            catch (const invalid_argument&) {
                QMessageBox::information(this, "Message", "Please enter a valid ID", QMessageBox::Ok);
            }
            QModelIndex patientNameIndex = ui->requestsTable->model()->index(row,2); // 2 is col
            myPatient.setName(ui->requestsTable->model()->data(patientNameIndex).toString().toStdString());

            QModelIndex physIdIndex = ui->requestsTable->model()->index(row,3); // 3 is col
            int currPhysID = ui->requestsTable->model()->data(physIdIndex).toString().toInt();
            server.acceptRequest(requestType, &myPatient, currPhysID);
            //server.editRecord(myPatient, "transfer patient", physParams);
            refreshMain();

            if (requestType == "Transfer") {
                QMessageBox::information(this, "Message", "Patient transferred", QMessageBox::Ok);
            }
            else {
                QMessageBox::information(this, "Message", "Medical Record Shared", QMessageBox::Ok);
            }
            ui->stackedWidget->setCurrentWidget(ui->main_page);
        }
    }
    else
    {
        QMessageBox::information(this, "Message", "No request selected", QMessageBox::Ok);
    }

}



// MEDICAL RECORD BUTTONS

void FamilyPhysicianUI::refreshMedicalRecord(vector<string> entries, string col1)
{
    QStringList horizontalHeader;
    QStringList verticalHeader;

    horizontalHeader.append(col1.c_str());
    horizontalHeader.append("Date");

    QStandardItemModel *model = new QStandardItemModel();

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    ui->recordTable->setModel(model);
    ui->recordTable->verticalHeader()->setVisible(false);
    ui->recordTable->verticalHeader()->setDefaultSectionSize(10);
    ui->recordTable->setShowGrid(false);

    string delimiter = ",";
    string token;
    size_t position;
    for (string entry : entries) {
        position = entry.find(delimiter);
        token = entry.substr(0, position);
        QStandardItem *col1 = new QStandardItem(token.c_str());
        entry.erase(0, position+1);

        position = entry.find(delimiter);
        token = entry.substr(0, position);
        QStandardItem *col2 = new QStandardItem(token.c_str());
        entry.erase(0, position+1);

        QList<QStandardItem*> row;
        row.append(col1);
        row.append(col2);
        model->appendRow(row);
    }
}

void FamilyPhysicianUI::on_diagnosisBtn_clicked()
{
    ui->recordTypeLabel->setText("Patient Diagnoses");
    vector<string> diagnoses = server.viewTable("diagnosis", myPatient.getId());
    /**
     *  example diagnosis data
    string diag1 = "high blood pressure,13/02/2018";
    string diag2 = "diabetes,03/09/2020";

    diagnoses.push_back(diag1);
    diagnoses.push_back(diag2);
    **/
    currentRecord = "Diagnosis";
    refreshMedicalRecord(diagnoses, currentRecord);
    ui->addToRecBtn->show();
    ui->deleteBtn->show();
    ui->stackedWidget->setCurrentWidget(ui->med_record_view);
}

void FamilyPhysicianUI::on_allergiesBtn_clicked()
{
    ui->recordTypeLabel->setText("Patient Allergies");
    vector<string> allergies = server.viewTable("allergy", myPatient.getId());
    /**
     *  example allergies data
    string diag1 = "peanut allergy,14/02/2018";
    string diag2 = "pollen,03/04/2012";

    allergies.push_back(diag1);
    allergies.push_back(diag2);
    **/
    currentRecord = "Allergy";
    refreshMedicalRecord(allergies, currentRecord);
    ui->addToRecBtn->show();
    ui->deleteBtn->show();
    ui->stackedWidget->setCurrentWidget(ui->med_record_view);
}

void FamilyPhysicianUI::on_prescriptionBtn_clicked()
{
    ui->recordTypeLabel->setText("Patient Prescriptions");
    vector<string> prescriptions = server.viewTable("prescription", myPatient.getId());
    /**
     *  example prescriptions data
    string diag1 = "Warfarin,16/04/2018";
    string diag2 = "Ventolin,03/08/2017";

    prescriptions.push_back(diag1);
    prescriptions.push_back(diag2);
    **/
    currentRecord = "Prescription";
    refreshMedicalRecord(prescriptions, currentRecord);
    ui->addToRecBtn->show();
    ui->deleteBtn->show();
    ui->stackedWidget->setCurrentWidget(ui->med_record_view);
}

void FamilyPhysicianUI::on_surgeryBtn_clicked()
{
    ui->recordTypeLabel->setText("Patient Surgeries");
    vector<string> surgeries = server.viewTable("surgery", myPatient.getId());
    /**
     *  example surgeries data
    string diag1 = "Cardiac Surgery,13/01/2018";
    string diag2 = "Tonsillectomy,14/12/2020";

    surgeries.push_back(diag1);
    surgeries.push_back(diag2);
    **/
    currentRecord = "Surgery";
    refreshMedicalRecord(surgeries, currentRecord);
    ui->addToRecBtn->show();
    ui->deleteBtn->show();
    ui->stackedWidget->setCurrentWidget(ui->med_record_view);
}

void FamilyPhysicianUI::on_vaccineBtn_clicked()
{
    ui->recordTypeLabel->setText("Patient Vaccinations");
    vector<string> vaccinations = server.viewTable("vaccination", myPatient.getId());
    /**
     *  example vaccinations data
    string diag1 = "Measles,13/07/2018";
    string diag2 = "Covid,03/02/2021";

    vaccinations.push_back(diag1);
    vaccinations.push_back(diag2);
    **/
    currentRecord = "Vaccination";
    refreshMedicalRecord(vaccinations, currentRecord);
    ui->addToRecBtn->show();
    ui->deleteBtn->show();
    ui->stackedWidget->setCurrentWidget(ui->med_record_view);
}

void FamilyPhysicianUI::on_diaryBtn_clicked()
{
    ui->recordTypeLabel->setText("Patient Diary Entries");
    vector<string> diaries = server.viewTable("diaryEntry", myPatient.getId());
    /**
     * example diaries data
    string diag1 = "felt dizzy today,13/10/2022";
    string diag2 = "high fever,20/04/2022";

    diaries.push_back(diag1);
    diaries.push_back(diag2);
    **/
    currentRecord = "Diary Entry";
    refreshMedicalRecord(diaries, currentRecord);
    ui->addToRecBtn->hide();
    ui->deleteBtn->hide();
    ui->stackedWidget->setCurrentWidget(ui->med_record_view);
}


void FamilyPhysicianUI::on_deleteBtn_clicked()
{
    QItemSelectionModel *selection = ui->recordTable->selectionModel();
    if (selection->hasSelection() && selection->selectedRows().size() == 1)
    {
        QMessageBox deleteEntry;
        deleteEntry.setText("Are you sure you want to remove this entry?");
        QPushButton *deleteButton = deleteEntry.addButton(tr("Delete Entry"), QMessageBox::ActionRole);
        deleteEntry.addButton(QMessageBox::Cancel);
        deleteEntry.exec();
        if (deleteEntry.clickedButton() == deleteButton)
        {
            int row = selection->selectedRows().at(0).row();
            QModelIndex entryIndex = ui->recordTable->model()->index(row,0); // 0 is col
            string entry = ui->recordTable->model()->data(entryIndex).toString().toStdString();
            QModelIndex dateIndex = ui->recordTable->model()->index(row,1); // 1 is col
            string date = ui->recordTable->model()->data(dateIndex).toString().toStdString();

            string transferParams = entry + "," + date;
            //cout << "Entry: " << entry << "Date: " << date << endl;
            string command = "remove a " + currentRecord;
            server.editRecord(myPatient, command, transferParams);
            cout << "Entry Removed" << endl;
            ui->stackedWidget->setCurrentWidget(ui->patient_record);
        }
    }
    else
    {
        QMessageBox::information(this, "Message", "No entry selected", QMessageBox::Ok);
    }


}

// MEDICAL RECORD BUTTONS

void FamilyPhysicianUI::on_medRecBackBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->patient_record);

}


void FamilyPhysicianUI::on_addToRecBtn_clicked()
{
    ui->variableLabel->setText(currentRecord.c_str());
    ui->stackedWidget->setCurrentWidget(ui->add_entry_page);
}


// ENTRY PAGE BUTTONS
void FamilyPhysicianUI::on_entryBackBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->med_record_view);
}

//HERE
void FamilyPhysicianUI::on_addEntryBtn_clicked()
{
    qDebug() << "User clicked add entry";
    bool validEntry = true;
    string entry;
    string date;

    if (!ui->entryLine->text().isEmpty()) {
        entry = ui->entryLine->text().toStdString();
    }
    else {
        QMessageBox::information(this, "Message", "Missing entry", QMessageBox::Ok);
        validEntry = false;
    }

    if (!ui->dateLine->text().isEmpty()) {
        date = ui->dateLine->text().toStdString();
    }
    else {
        QMessageBox::information(this, "Message", "Missing date", QMessageBox::Ok);
        validEntry = false;
    }
    if (validEntry == true)
    {
        string transferParams = entry + "," + date;
        string command = "add a " + currentRecord;
        server.editRecord(myPatient, command, transferParams);
        ui->entryLine->setText("");
        ui->dateLine->setText("");
        ui->stackedWidget->setCurrentWidget(ui->patient_record);
    }
}


// UNUSED

void FamilyPhysicianUI::on_saveBtn_clicked()
{
    cout << ui->recordTable->model()->data(ui->recordTable->model()->index(0,0)).toString().toStdString() << endl;



    QMessageBox::information(this, "Message", "Medical Record Updated", QMessageBox::Ok);
    ui->stackedWidget->setCurrentWidget(ui->patient_record);
}


