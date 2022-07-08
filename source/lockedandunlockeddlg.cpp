#include "lockedandunlockeddlg.h"
#include "ui_lockedandunlockeddlg.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
lockedAndUnlockedDlg::lockedAndUnlockedDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lockedAndUnlockedDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("加密");
    QRegExp regExp("[#?!@$%^&*-_A-Za-z0-9]+$");///密码正则表达式
    ui->passwdLineEdit->setValidator(new QRegExpValidator(regExp,this));///限制输入范围
    ui->passwdLineEdit->setAttribute(Qt::WA_InputMethodEnabled, false);///屏蔽中文输入法
    setMinimumSize(200,135);
}

lockedAndUnlockedDlg::~lockedAndUnlockedDlg()
{
    delete ui;
}

void lockedAndUnlockedDlg::setType(lockedAndUnlockedDlg::Type type)
{
    m_Type = type;
    if(type == lockedAndUnlockedDlg::locked)
    {
        this->setWindowTitle("加密");
        ui->okBtn->setText("加密");
    }
    else
    {
        this->setWindowTitle("解密");
        ui->okBtn->setText("解密");
    }
}

void lockedAndUnlockedDlg::setFilePathName(QString filePathName)
{
    m_FilePathName = filePathName;
    ui->fileNameLineEdit->setText(m_FilePathName);
    //m_FileName = filePathName.mid(filePathName.lastIndexOf("/")+1);
   // m_FileName = m_FileName.left(m_FileName.lastIndexOf("."));
}

void lockedAndUnlockedDlg::setOutFilePath(QString outFilePath)
{
    m_OutFilePath = outFilePath;
}

QString lockedAndUnlockedDlg::getCmd()
{
    QString cmd= "";
    QString passwd = ui->passwdLineEdit->text();

    if(passwd.isEmpty())///未输入密码
        return passwd;
    if(m_Type == lockedAndUnlockedDlg::locked)
    {
        cmd = "pdftk " +m_FilePathName +" output "
                + m_OutFilePath+"/"+m_FileName+"_加密版.pdf"+" owner_pw foopass"+passwd + " user_pw "+ passwd;
    }
    else
    {
        cmd = "pdftk " + m_FilePathName +" input_pw foopass" + passwd + " output "
                +m_OutFilePath+"/"+m_FileName+"_解密版.pdf" ;
    }
    return cmd;
}



void lockedAndUnlockedDlg::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        ui->passwdLineEdit->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->passwdLineEdit->setEchoMode(QLineEdit::Password);
    }
}

void lockedAndUnlockedDlg::on_addFileBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("文件对话框！"),
                                                        m_FilePathName,
                                                        tr("PDF文件(*pdf)"));
    if(!fileName.isEmpty())
    {
        m_FilePathName = fileName;
        ui->fileNameLineEdit->setText(m_FilePathName);
        //m_FileName = m_FilePathName.mid(m_FilePathName.lastIndexOf("/")+1);
        //m_FileName = m_FileName.left(m_FileName.lastIndexOf("."));
    }
}

void lockedAndUnlockedDlg::on_okBtn_clicked()
{
    m_FilePathName = ui->fileNameLineEdit->text();
#ifdef QT_DEBUG
    qDebug()<<m_FilePathName<<m_FilePathName.right(4).contains(".pdf")<<endl;
#endif
    if(m_FilePathName.isEmpty()||!m_FilePathName.right(4).contains(".pdf")
            &!m_FilePathName.right(4).contains(".PDF"))////提示文件未存在
    {
        QMessageBox::critical(this, tr("错误!"),
                              "文件名不正确!",
                              QMessageBox::Ok );
        return;
    }

    m_FileName = m_FilePathName.mid(m_FilePathName.lastIndexOf("/")+1);
    m_FileName = m_FileName.left(m_FileName.lastIndexOf("."));

    QString passwd = ui->passwdLineEdit->text();
    if(passwd.isEmpty())///未输入密码
    {
        QMessageBox::critical(this, tr("错误!"),
                              "密码为空!",
                              QMessageBox::Ok );
        return;
    }
    if(m_Type == lockedAndUnlockedDlg::locked)
    {

    }
    else
    {

    }
    QDialog::accept();
    //this->close();
}
