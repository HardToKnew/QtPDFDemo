#ifndef SPLITFILEDLG_H
#define SPLITFILEDLG_H

#include <QDialog>

namespace Ui {
class SplitFileDlg;
}

class SplitFileDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SplitFileDlg(QWidget *parent = nullptr);
    ~SplitFileDlg();
    void setFilePathName(QString filePathName);
    void setOutFilePath(QString outFilePath);
    QString getCmd();
    QString getPDFinfo();

private slots:
    void on_okBtn_clicked();

    void on_addFileBtn_clicked();

private:
    Ui::SplitFileDlg *ui;
    QString m_OutFilePath;
    QString m_FilePathName;
    QString m_FileName;
};

#endif // SPLITFILEDLG_H
