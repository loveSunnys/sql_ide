#ifndef SETDIALOG_H
#define SETDIALOG_H

#include <QDialog>
#include <QSettings>
namespace Ui {
class setDialog;
}

class setDialog : public QDialog
{
    Q_OBJECT

public:
    explicit setDialog(QWidget *parent = 0);
    ~setDialog();

private:
    Ui::setDialog *ui;
};

#endif // SETDIALOG_H
