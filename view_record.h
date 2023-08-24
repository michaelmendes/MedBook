#ifndef VIEW_RECORD_H
#define VIEW_RECORD_H

#include <QMainWindow>
#include <QObject>
//#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>
#include <QDialog>
#include <string>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <QDateTime>
#include <QDebug>
#include <QTextEdit>
#include <QDialog>
#include <QStandardItemModel>
#include <QTableView>
#include <QStringList>
#include <QStackedWidget>

using namespace std;

namespace Ui {
class ViewRecord;
}

class ViewRecord : public QDialog
{
    Q_OBJECT

public:
    explicit ViewRecord(QWidget *parent = nullptr);
    ~ViewRecord();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::ViewRecord *ui;
    //void showRecord(vector<string> entries, string col1);
};

#endif // VIEW_RECORD_H
