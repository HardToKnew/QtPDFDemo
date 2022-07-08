#include "mainw.h"
#include "ui_mainw.h"
#include <QStringListModel>
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include <QMouseEvent>
#include <QDebug>
#include <QProcess>
#include "helpdlg.h"
#include "aboutdlg.h"
#include "lockedandunlockeddlg.h"
#include "splitfiledlg.h"
MainW::MainW(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainW)
{

    ui->setupUi(this);
     setWindowTitle("PDFProDemo0.0.1");
    ui->passwdEdit->setVisible(false);
    QRegExp regExp("[#?!@$%^&*-_A-Za-z0-9]+$");///密码正则表达式
    ui->passwdEdit->setValidator(new QRegExpValidator(regExp,this));///限制输入范围
    ui->passwdEdit->setAttribute(Qt::WA_InputMethodEnabled, false);///屏蔽中文输入法
    ui->comboBox->setVisible(false);
    ui->showPasswd->setVisible(false);


    QStringListModel *model;
    model = new QStringListModel(this);
    ui->fileListView->setModel(model);
    //ui->fileListView->setMovement(QListView::Snap);
    //ui->fileListView->setSelectionMode(QAbstractItemView::ExtendedSelection);///设置为多选属性，可通过鼠标拖拽、按下Ctrl或Shift键操作多选


    QString history_ini_path = QCoreApplication::applicationDirPath()+"/config/config.ini";
    QSettings *read_history_ini = new QSettings(history_ini_path, QSettings::IniFormat);
    defaultOpenFileName = read_history_ini->value("/history/path").toString();
    defaultOutPath = read_history_ini->value("/outpath/path").toString();
    delete read_history_ini;

    if(defaultOutPath.isNull())
    {
        defaultOutPath = QCoreApplication::applicationDirPath();///默认软件运行位置
        defaultOutPath += "/";
    }
    filePathInfo = new QLabel(defaultStr+defaultOutPath);
    ///filePathInfo->installEventFilter(this);///32 bit 导致无法显示  默认文件夹 64bit release 导致程序异常退出
    filePathInfo->setMinimumWidth(150);
    ui->statusbar->setMinimumHeight(25);
    ui->statusbar->addWidget(filePathInfo);

    ///connect(this, &MainW::filePathInfoCliked, this, &MainW::on_filePathInfoCliked);
}

MainW::~MainW()
{
    delete ui;
}


void MainW::on_readOnlyCheckBox_clicked(bool checked)
{
    if(checked)
        ui->comboBox->setVisible(true);
    else
        ui->comboBox->setVisible(false);
}

void MainW::on_lockedCheckBox_clicked(bool checked)
{
    if(checked)
    {
        ui->passwdEdit->setVisible(true);
        ui->showPasswd->setVisible(true);
    }
    else
    {
        ui->passwdEdit->setVisible(false);
        ui->showPasswd->setVisible(false);
    }
}

void MainW::on_addFileBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("文件对话框！"),
                                                        defaultOpenFileName,
                                                        tr("PDF文件(*pdf)"));
    if(!fileName.isEmpty())
    {
        QStringListModel *model = dynamic_cast<QStringListModel *>(ui->fileListView->model());
        model->insertRow(model->rowCount());
        QModelIndex index = model->index(model->rowCount()-1);
        model->setData(index, fileName);

        //  保存打开文件的历史记录
        //  Qt中使用QSettings类读写ini文件
        //  QSettings构造函数的第一个参数是ini文件的路径,第二个参数表示针对ini文件,第三个参数可以缺省
        QString history_ini_path = QCoreApplication::applicationDirPath()+"/config/config.ini";
        QSettings *write_history_ini = new QSettings(history_ini_path, QSettings::IniFormat);
        write_history_ini->setValue("history/path", fileName);
        defaultOpenFileName = fileName;
        //  写入完成后删除指针
        delete write_history_ini;
    }
}

void MainW::on_removeFileBtn_clicked()
{
    /*QStringListModel *model = dynamic_cast<QStringListModel *>(ui->fileListView->model());
    int currentRow = ui->fileListView.c;
    if(currentRow < 0)
        return;
    QListWidgetItem *item = ui->listWidget->currentItem();
    ui->listWidget->removeItemWidget(item);
    ui->listWidget->takeItem(currentRow);*/

    QItemSelectionModel *selmodel = ui->fileListView->selectionModel();
    if (selmodel)
    {
        QModelIndexList indexlist = selmodel->selectedIndexes();
        int count = indexlist.size();
        QStringListModel *model = dynamic_cast<QStringListModel *>(ui->fileListView->model());
        for(int idx = 0 ; idx<count; idx++)///删除所有选中项目
        {
            model->removeRow(indexlist[idx].row());
        }
    }
}

void MainW::on_removeAllBtn_clicked()
{
    QStringListModel *model = dynamic_cast<QStringListModel *>(ui->fileListView->model());
    if(model->rowCount()>0)
    {
        int rowCount =  model->rowCount();
        for (int index = 0; index<rowCount; index++) {
            model->removeRow(model->rowCount()-1);
        }
    }
}


void MainW::on_showPasswd_clicked(bool checked)
{
    if(checked)
        ui->passwdEdit->setEchoMode(QLineEdit::Normal);
    else
        ui->passwdEdit->setEchoMode(QLineEdit::Password);

}

void MainW::on_actionLocked_triggered()
{
    lockedAndUnlockedDlg locked(this);
    locked.setType(lockedAndUnlockedDlg::locked);
    locked.setFilePathName(defaultOpenFileName);
    locked.setOutFilePath(defaultOutPath);
    if(locked.exec() == QDialog::Accepted)
    {
        QString cmd = locked.getCmd();
        QProcess *cmdProcess = new QProcess(this);
        connect(cmdProcess,&QProcess::readyReadStandardError,this,[=,&cmdProcess]()mutable{///失败
                QString Error=cmdProcess->readAllStandardError();
                QMessageBox::question(this, tr("提示!"),
                "加密失败!原文件可能有密码！",
                QMessageBox::Ok );
                //qDebug()<<"Error:"<<cmdProcess->readAllStandardError();
            });
        cmdProcess->start(cmd);
        cmdProcess->waitForFinished();
        //qDebug()<<cmd<<endl;
    }

}

void MainW::on_actionUnlocked_triggered()
{
    lockedAndUnlockedDlg unlocked(this);
    unlocked.setType(lockedAndUnlockedDlg::unlocked);
    unlocked.setFilePathName(defaultOpenFileName);
    unlocked.setOutFilePath(defaultOutPath);
    if(unlocked.exec() == QDialog::Accepted)
    {
        QString cmd = unlocked.getCmd();
        QProcess *cmdProcess = new QProcess(this);
        connect(cmdProcess,&QProcess::readyReadStandardOutput,this,[=,&cmdProcess]()mutable{ //注意我这里lambda表达式的写法，[]里的内容需要根据实际情况更改
                QString Output=cmdProcess->readAllStandardOutput();
                //qDebug()<<"Output:"<<Output;
            });
        connect(cmdProcess,&QProcess::readyReadStandardError,this,[=,&cmdProcess]()mutable{///失败
                QString Error=cmdProcess->readAllStandardError();
                //qDebug()<<"Error:"<<cmdProcess->readAllStandardError();
                QMessageBox::question(this, tr("提示!"),
                "密码错误!",
                QMessageBox::Ok );
            });
        cmdProcess->start(cmd);
        cmdProcess->waitForFinished();
        //qDebug()<<cmd<<endl;
    }
}

void MainW::on_actionSplitFile_triggered()
{
    SplitFileDlg splitFile;
    splitFile.setFilePathName(defaultOpenFileName);
    splitFile.setOutFilePath(defaultOutPath);
    if(splitFile.exec() == QDialog::Accepted)
    {
        QString cmd = splitFile.getCmd();
        QProcess *cmdProcess = new QProcess(this);

        connect(cmdProcess,&QProcess::readyReadStandardError,this,[=,&cmdProcess]()mutable{///失败
                QString Error=cmdProcess->readAllStandardError();
                ///qDebug()<<"Error:"<<cmdProcess->readAllStandardError();
                QMessageBox::question(this, tr("提示!"),
                "拆分失败!",
                QMessageBox::Ok );
            });
        cmdProcess->start(cmd);
        cmdProcess->waitForFinished();
    }
}

void MainW::on_actionHelp_triggered()
{
   helpDlg help;
   help.exec();
}

void MainW::on_actionAbout_triggered()
{
    //QMessageBox::aboutQt(this, tr("About Qt消息框"));
    aboutDlg about;
    about.exec();
}

void MainW::on_filePathInfoCliked(Qt::MouseButton button)
{
    if(Qt::LeftButton == button)///左键点击
    {
        QString filePath = QFileDialog::getExistingDirectory(this, "请选择文件保存路径...", defaultOutPath);
        if(!filePath.isEmpty())
        {
            defaultOutPath = filePath;
            QString history_ini_path = QCoreApplication::applicationDirPath()+"/config/config.ini";
            QSettings *write_history_ini = new QSettings(history_ini_path, QSettings::IniFormat);
            write_history_ini->setValue("outpath/path", defaultOutPath);
            //  写入完成后删除指针
            delete write_history_ini;
        }
        else
            return;
        filePathInfo ->setText(defaultStr+defaultOutPath);
    }
    else if(Qt::RightButton == button)///右键点击  ，打开文件夹 ，会弹出文件夹菜单，相当于在文件夹中又点击了右键
    {
       ;// QString filePath = QFileDialog::getExistingDirectory(this, "请选择文件保存路径...", defaultOutPath);
    }
}

QString MainW::getCmd()
{
    QString cmd = "pdftk ";//pdftk A=one.pdf B=two.pdf cat A B A output combined.pdf owner_pw foo user_pw baz allow printing
    QString passwd="";
    if(ui->lockedCheckBox->isChecked())
    {
       passwd = ui->passwdEdit->text();
    }

    QStringListModel *model = dynamic_cast<QStringListModel *>(ui->fileListView->model());
    QStringList strList = model->stringList();
    for (QStringList::iterator it = strList.begin(); it!=strList.end(); it++) {

        cmd += *it;
        cmd+=" ";
    }

    QString outFileName = ui->outFileNameEdit->text();
    if(outFileName.isEmpty())
    {
        outFileName = *strList.begin();
        ///qDebug()<<outFileName<<endl;
        outFileName =  outFileName.mid(outFileName.lastIndexOf("/")+1);
        outFileName = outFileName.left(outFileName.lastIndexOf("."));
        if(!passwd.isEmpty())
             outFileName = outFileName+"_加密版";
        else
             outFileName = outFileName+"_合成版";
        ///qDebug()<<outFileName<<endl;
    }

    cmd += "cat output "+ defaultOutPath+"/"+outFileName + ".pdf";



    if(ui->readOnlyCheckBox->isChecked())
    {
        cmd += +" owner_pw foopass"+passwd;
    }

    if(ui->lockedCheckBox->isChecked()&&!passwd.isEmpty())
    {
       cmd += " user_pw "+passwd;
    }
    if(ui->readOnlyCheckBox->isChecked())
    {
        if(ui->comboBox->currentIndex() == 1)
        {
           cmd += " allow Printing";
        }
    }

    return cmd;
}


/*bool MainW::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == filePathInfo)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *e = static_cast<QMouseEvent *>(event);

            emit filePathInfoCliked(e->button());
            //emit sendObject(ui->label);

        }
    }
}*/

void MainW::on_compositeBtn_clicked()
{
    QStringListModel *model = dynamic_cast<QStringListModel *>(ui->fileListView->model());
    if(model->rowCount() == 0)
    {
        ///无加密文件  退出程序
        ///
        QMessageBox::critical(this, tr("错误!"),
        "文件为空!",
        QMessageBox::Ok );
        return ;
    }

    if(ui->outFileNameEdit->text().isEmpty())
    {
        QMessageBox::StandardButton result = QMessageBox::warning(this, tr("警告!"),
                             "未输入文件名,使用默认文件输出!",
                             QMessageBox::Ok | QMessageBox::Cancel);
        if(result == QMessageBox::Cancel)
            return;
    }

    if(ui->lockedCheckBox->isChecked() && ui->passwdEdit->text().isEmpty())
    {
        QMessageBox::StandardButton result = QMessageBox::warning(this, tr("警告!"),
                             "未输入密码, 加密将失效，是否继续!",
                             QMessageBox::Yes| QMessageBox::No);
        if(result == QMessageBox::No)
            return;
    }
    QString cmd = getCmd();
    QProcess *cmdProcess = new QProcess(this);
    connect(cmdProcess,&QProcess::readyReadStandardError,this,[=,&cmdProcess]()mutable{///失败
            QString Error=cmdProcess->readAllStandardError();
            //qDebug()<<"Error:"<<cmdProcess->readAllStandardError();
            QMessageBox::question(this, tr("提示!"),
            "合成失败!",
            QMessageBox::Ok );

        });
    cmdProcess->start(cmd);
    cmdProcess->waitForFinished();
}

void MainW::on_actionSeting_triggered()
{
    QString filePath = QFileDialog::getExistingDirectory(this, "请选择文件保存路径...", defaultOutPath);
    if(!filePath.isEmpty())
    {
        defaultOutPath = filePath;
        QString history_ini_path = QCoreApplication::applicationDirPath()+"/config/config.ini";
        QSettings *write_history_ini = new QSettings(history_ini_path, QSettings::IniFormat);
        write_history_ini->setValue("outpath/path", defaultOutPath);
        //  写入完成后删除指针
        delete write_history_ini;
    }
    else
        return;
    filePathInfo ->setText(defaultStr+defaultOutPath);
}
