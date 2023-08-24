#ifndef VIEWDIARY_H
#define VIEWDIARY_H

//#include <QDeclarativeItem>
#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>
#include <QDialog>
#include <string>
//#include <QDeclarativeItem>
using namespace std;

namespace Ui {
class ViewDiary;
}

class ViewDiary : public QDialog
{
    Q_OBJECT

public:
    explicit ViewDiary(QWidget *parent = nullptr);
    ~ViewDiary();

private:
    Ui::ViewDiary *ui;

};

#endif // VIEWDIARY_H
