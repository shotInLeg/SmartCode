#ifndef S_CHECK_UNSAVE_CHANGES_H
#define S_CHECK_UNSAVE_CHANGES_H

#include <QDialog>
#include <QVector>
#include <QString>
#include <QCheckBox>

namespace Ui {
class SCheckUnsaveChanges;
}

class SCheckUnsaveChanges : public QDialog
{
    Q_OBJECT

public:
    explicit SCheckUnsaveChanges(QWidget *parent = 0);
    explicit SCheckUnsaveChanges(const QVector<QString>& unsaveFiles,
                                 QWidget *parent = 0);
    ~SCheckUnsaveChanges();

private slots:
    void on_bSave_clicked();

    void on_bNotSave_clicked();

    void on_bCancel_clicked();

    void on_bViewChanges_clicked();

signals:
    void saveFiles(QVector<QString> filesToSave);
    void notSave();
    void canceled();
    void viewChanges(QString file);

private:
    Ui::SCheckUnsaveChanges *ui;

    QVector<QString> unsaveFiles;
    QVector<QCheckBox*> checkers;
};

#endif // S_CHECK_UNSAVE_CHANGES_H
