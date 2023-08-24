#ifndef ADD_DIARY_H
#define ADD_DIARY_H

#include <QMainWindow>
#include <QObject>
//#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>
#include <QDialog>
#include <string>
using namespace std;

namespace Ui {
class AddDiary;
}

class AddDiary : public QDialog
{
    Q_OBJECT

public:
    explicit AddDiary(QWidget *parent = nullptr);
    ~AddDiary();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::AddDiary *ui;

};

#endif // ADD_DIARY_H
