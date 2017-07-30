#ifndef SCREATEPROJECTFORM_H
#define SCREATEPROJECTFORM_H

#include <QWidget>
#include <QMap>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class SCreateProjectForm;
}

class SCreateProjectForm : public QWidget
{
    Q_OBJECT

public:
    explicit SCreateProjectForm(QWidget *parent = 0);
    ~SCreateProjectForm();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_bChoosePath_clicked();

    void on_bChooseCompiler_clicked();

signals:
    void projectCreated(QString);
    void projectCreateReject();

private:
    void makeProject();

private:
    Ui::SCreateProjectForm *ui;
    QString projPath;

    QMap<QString, QString> data;
};

#endif // SCREATEPROJECTFORM_H
