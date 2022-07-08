#ifndef LOCKEDANDUNLOCKEDDLG_H
#define LOCKEDANDUNLOCKEDDLG_H

#include <QDialog>

namespace Ui {
class lockedAndUnlockedDlg;
}

class lockedAndUnlockedDlg : public QDialog
{
    Q_OBJECT
public:
    enum Type{
        locked,
        unlocked
    };
public:
    explicit lockedAndUnlockedDlg(QWidget *parent = nullptr);
    ~lockedAndUnlockedDlg();
    void setType(lockedAndUnlockedDlg::Type);
    void setFilePathName(QString filePathName);
    void setOutFilePath(QString outFilePath);
    QString getCmd();


private slots:

    void on_checkBox_clicked(bool checked);

    void on_addFileBtn_clicked();

    void on_okBtn_clicked();

private:
    Ui::lockedAndUnlockedDlg *ui;
    lockedAndUnlockedDlg::Type m_Type = lockedAndUnlockedDlg::locked;
    QString m_OutFilePath;
    QString m_FilePathName;
    QString m_FileName;
};

#endif // LOCKEDANDUNLOCKEDDLG_H
