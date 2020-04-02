#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include "ui_aboutdialog.h"

namespace Ui {
class aboutDialog;
}

class aboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit aboutDialog(QWidget *parent = nullptr);
    ~aboutDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::aboutDialog *ui;
};

#endif // ABOUTDIALOG_H
