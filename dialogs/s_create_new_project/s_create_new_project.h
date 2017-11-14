#ifndef S_CREATE_NEW_PROJECT_H
#define S_CREATE_NEW_PROJECT_H

#include <QDialog>
#include <QString>
#include <QVector>
#include <QPair>
#include <QFileDialog>

namespace Ui {
class SCreateNewProject;
}

class SCreateNewProject : public QDialog
{
    Q_OBJECT

public:
    explicit SCreateNewProject(QWidget *parent = 0);
    explicit SCreateNewProject(const QVector<QPair<QString, QString> >& langs,
                               const QString& baseInterpreterPath,
                               const QVector<QPair<QString, QString> >& types,
                               const QString& baseProjectPath,
                               QWidget *parent = 0);
    ~SCreateNewProject();

private slots:
    void on_bCreate_clicked();

    void on_bCancel_clicked();

    void on_bSelectInterpreterPath_clicked();

    void on_bSelectProjectPath_clicked();

signals:
    void createProject(QString lang,
                     QString interpreterPath,
                     QString projectType,
                     QString projectPath,
                     QString projectName);
    void canceled();

private:
    Ui::SCreateNewProject *ui;


    QVector<QPair<QString, QString> > langs;
    QString baseInterpreterPath;
    QVector<QPair<QString, QString> > types;
    QString baseProjectPath;
};

#endif // S_CREATE_NEW_PROJECT_H
