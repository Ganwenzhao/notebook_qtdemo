#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "ui_finddialog.h"

namespace Ui {
class findDialog;
}

class findDialog : public QDialog
{
    Q_OBJECT

public:
    explicit findDialog(QWidget *parent = nullptr);
    ~findDialog();
signals:
    void find(QString,bool,bool);


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    //文本改变
    void textChange_s();
private:
    Ui::findDialog *ui;
    //显示消息
    void showMessage(QString title);
};

#endif // FINDDIALOG_H
