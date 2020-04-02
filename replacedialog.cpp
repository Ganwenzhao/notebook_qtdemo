#include "replacedialog.h"
#include "ui_replacedialog.h"

replaceDialog::replaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::replaceDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    setWindowTitle("Replace");

    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(textChange_s()));
}

replaceDialog::~replaceDialog()
{
    delete ui;
}

void replaceDialog::on_ButtonCancel_clicked()
{
    this->close();
}

//文本改变
void replaceDialog::textChange_s(){
    if(ui->lineEdit->text().trimmed().isEmpty()){
        ui->ButtonFdN->setEnabled(false);
        ui->ButtonReplace->setEnabled(false);
        ui->ButtonReAll->setEnabled(false);
    }else{
        ui->ButtonFdN->setEnabled(true);
        ui->ButtonReplace->setEnabled(true);
        ui->ButtonReAll->setEnabled(true);
    }
}

void replaceDialog::on_ButtonReplace_clicked()
{
    bool checkbox = ui->checkBox->isChecked();
    QString target = ui->lineEdit->text().trimmed();
    QString value = ui->lineEdit_2->text().trimmed();
    //回调事件
    emit this->replace(target,value,checkbox,false);
}



void replaceDialog::on_ButtonFdN_clicked()
{
    bool checkbox = ui->checkBox->isChecked();
    QString value = ui->lineEdit->text().trimmed();
    //回调事件
    emit this->find(value,checkbox);
}



void replaceDialog::on_ButtonReAll_clicked()
{
    bool checkbox = ui->checkBox->isChecked();
    QString target = ui->lineEdit->text().trimmed();
    QString value = ui->lineEdit_2->text().trimmed();
    //回调事件
    emit this->replace(target,value,checkbox,true);
}
