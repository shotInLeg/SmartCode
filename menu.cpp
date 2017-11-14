#include "smartcode.h"
#include "ui_smartcode.h"

#include "dialogs/s_create_new_project/s_create_new_project.h"


void SmartCode::on_aCreateProject_triggered()
{
    QVector<QPair<QString, QString> > langs = {
        {"lego", "Лего"}
    };

    QString baseInterpreterPath = "/usr/local/bin/";

    QVector<QPair<QString, QString> > projectTypes = {
        {"console", "Консольное приложение"}
    };

    QString baseProjectPath = QDir::homePath();

    SCreateNewProject* cp = new SCreateNewProject(langs,
                                                  baseInterpreterPath,
                                                  projectTypes,
                                                  baseProjectPath,
                                                  this);
    cp->show();

    QObject::connect(cp, SIGNAL(createProject(QString,QString,QString,QString, QString)),
                     this, SLOT(createProject(QString,QString,QString,QString, QString)));
}

void SmartCode::on_aOpenProject_triggered()
{
    QString projectPath = QFileDialog::getExistingDirectory(
                this,
                "$Select Dir With Project",
                QDir::homePath()
    );

    showDirTree(projectPath);
    this->projectPath = projectPath;
}
