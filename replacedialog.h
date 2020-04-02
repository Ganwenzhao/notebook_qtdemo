#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "ui_replacedialog.h"

namespace Ui {
class replaceDialog;
}

class replaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit replaceDialog(QWidget *parent = nullptr);
    ~replaceDialog();
signals:
    void find(QString,bool);
    void replace(QString,QString,bool,bool);

private slots:
    void on_ButtonCancel_clicked();
    //文本改变
    void textChange_s();

    void on_ButtonReplace_clicked();

    void on_ButtonFdN_clicked();

    void on_ButtonReAll_clicked();

private:
    Ui::replaceDialog *ui;
};

#endif // REPLACEDIALOG_H
