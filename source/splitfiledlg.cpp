#include "splitfiledlg.h"
#include "ui_splitfiledlg.h"
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>
SplitFileDlg::SplitFileDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SplitFileDlg)
{
    ui->setupUi(this);
    setMinimumSize(200,125);
    setWindowTitle("拆分文件");
}

SplitFileDlg::~SplitFileDlg()
{
    delete ui;
}

void SplitFileDlg::setFilePathName(QString filePathName)
{
    m_FilePathName = filePathName;
    ui->fileNameLineEdit->setText(m_FilePathName);
    m_FileName = filePathName.mid(filePathName.lastIndexOf("/")+1);
    m_FileName = m_FileName.left(m_FileName.lastIndexOf("."));
}

void SplitFileDlg::setOutFilePath(QString outFilePath)
{
    m_OutFilePath = outFilePath;
}

QString SplitFileDlg::getCmd()
{
    QString cmd = "pdftk " +m_FilePathName + " dump_data";
    QProcess *cmdProcess = new QProcess(this);
    cmdProcess->start(cmd);
    cmdProcess->waitForFinished();
    cmd = cmdProcess->readAllStandardOutput();
    cmdProcess->close();
    int Page = cmd.mid(cmd.indexOf("NumberOfPages: ")+15,1).toInt();///获取页数
    int width = 0;
    while (Page!=0)
    {
        Page = Page/10;
        width++;
    }

    cmd = "pdftk " +m_FilePathName + " burst output " +
            m_OutFilePath+"/"+m_FileName+"_Page_%0"+QString::number(width)+"d.pdf" ;
    return  cmd;
}

QString SplitFileDlg::getPDFinfo()///获取文件详细信息
{
    QString cmd = "pdftk " +m_FilePathName + " dump_data";

    return  cmd;
}

void SplitFileDlg::on_okBtn_clicked()
{

    m_FilePathName = ui->fileNameLineEdit->text();
    if(m_FilePathName.isEmpty()||!m_FilePathName.right(4).contains(".pdf")
            &!m_FilePathName.right(4).contains(".PDF"))////提示文件未存在
    {
        QMessageBox::critical(this, tr("错误!"),
                              "文件不存在!",
                              QMessageBox::Ok );
        return;
    }
    m_FileName = m_FilePathName.mid(m_FilePathName.lastIndexOf("/")+1);
    m_FileName = m_FileName.left(m_FileName.lastIndexOf("."));

    if(m_FilePathName.isEmpty())
        return;
    QDialog::accept();
    //this->close();
}


void SplitFileDlg::on_addFileBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("文件对话框！"),
                                                        m_FilePathName,
                                                        tr("PDF文件(*pdf)"));
    if(!fileName.isEmpty())
    {
        m_FilePathName = fileName;
        ui->fileNameLineEdit->setText(m_FilePathName);
        m_FileName = m_FilePathName.mid(m_FilePathName.lastIndexOf("/")+1);
    }
}
