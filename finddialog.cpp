#include "finddialog.h"
#include "ui_finddialog.h"

findDialog::findDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    setWindowTitle("Find");

    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(textChange_s()));
}

findDialog::~findDialog()
{
    delete ui;
}
void findDialog::showMessage(QString title){
    QMessageBox box(QMessageBox::Question,"NoteBook - Find",title);
    box.setIcon(QMessageBox::NoIcon);
    box.setStandardButtons (QMessageBox::Ok);
    box.setButtonText (QMessageBox::Ok,QString("ok"));
    box.setWindowFlags( Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint );
    box.exec();
}





void findDialog::textChange_s(){
    if(ui->lineEdit->text().trimmed().isEmpty()){
        ui->pushButton->setEnabled(false);
    }else{
        ui->pushButton->setEnabled(true);
    }
}

void findDialog::on_pushButton_2_clicked()
{
    this->close();
}

void findDialog::on_pushButton_clicked()
{
    bool checkbox = ui->checkBox->isChecked();
    QString value = ui->lineEdit->text().trimmed();
    bool isUp = false;
    if(ui->radioButtonUp->isChecked()){
        isUp = true;
    }
    if(value.isEmpty()){
        this->showMessage("Please input key word");
        return;
    }
    //回调事件
    emit this->find(value,checkbox,isUp);
}
