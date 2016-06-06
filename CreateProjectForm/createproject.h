#ifndef CREATEPROJECT_H
#define CREATEPROJECT_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>

namespace Ui {
class CreateProject;
}

class CreateProject : public QWidget
{
    Q_OBJECT

public:
    explicit CreateProject(QWidget *parent = 0);
    ~CreateProject();

private slots:
    void on_tbSelectPath_clicked();

    void on_bCreate_clicked();

    void on_bCancel_clicked();

signals:
    void createdDone(QString, QWidget*);
    void createdCancel(QWidget*);

private:
    Ui::CreateProject *ui;
};

#endif // CREATEPROJECT_H
