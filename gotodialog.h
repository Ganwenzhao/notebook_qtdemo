#ifndef GOTODIALOG_H
#define GOTODIALOG_H

#include <QMessageBox>
#include <QDialog>
#include "ui_gotodialog.h"

namespace Ui {
class gotoDialog;
}

class gotoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit gotoDialog(QWidget *parent = nullptr);
    ~gotoDialog();
signals:
    void goToLine(QString);


private slots:
    void on_pushButtonCancel_clicked();

    void on_pushButtonOk_clicked();

private:
    Ui::gotoDialog *ui;

    void showMessage(QString title);
};

#endif // GOTODIALOG_H
