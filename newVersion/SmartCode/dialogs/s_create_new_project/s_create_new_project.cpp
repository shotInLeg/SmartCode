#include "s_create_new_project.h"
#include "ui_s_create_new_project.h"

SCreateNewProject::SCreateNewProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SCreateNewProject)
{
    ui->setupUi(this);
}

SCreateNewProject::SCreateNewProject(const QVector<QPair<QString, QString> > &langs,
                                     const QString &baseInterpreterPath,
                                     const QVector<QPair<QString, QString> > &types,
                                     const QString &baseProjectPath,
                                     QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SCreateNewProject)
{
    ui->setupUi(this);

    // Сохраняем базовые папки
    this->baseInterpreterPath = baseInterpreterPath;
    this->baseProjectPath = baseProjectPath;

    // Сохраняем список языков
    this->langs = langs;

    // Сохраняем список типов проектов
    this->types = types;

    //Заполняем поле выбора языка
    for(const QPair<QString, QString>& lang : langs)
    {
        ui->cbLanguage->addItem(lang.second);
    }

    //Заполняем поле выбора типа проекта
    for(const QPair<QString, QString>& type : types)
    {
        ui->cbProjectType->addItem(type.second);
    }
}

SCreateNewProject::~SCreateNewProject()
{
    delete ui;
}

void SCreateNewProject::on_bCreate_clicked()
{
    int  langIndex = ui->cbLanguage->currentIndex();
    QString lang = this->types.at(langIndex).first;

    QString interpreterPath = ui->eInterpreterPath->text();

    int  projectTypeIndex = ui->cbProjectType->currentIndex();
    QString projectType = this->types.at(projectTypeIndex).first;

    QString projectPath = ui->eProjectPath->text();

    QString projectName = ui->eProjectName->text();


    emit createEntry(lang, interpreterPath, projectType, projectPath, projectName);
    this->close();
}

void SCreateNewProject::on_bCancel_clicked()
{
    emit canceled();
    this->close();
}

void SCreateNewProject::on_bSelectInterpreterPath_clicked()
{
    QString interpreterPath = QFileDialog::getOpenFileName(
                        this, "Выберите транслятор", baseInterpreterPath);
    ui->eInterpreterPath->setText(interpreterPath);
}

void SCreateNewProject::on_bSelectProjectPath_clicked()
{
    QString projectPath = QFileDialog::getExistingDirectory(
                        this, "Выберите папку сохранения проекта", baseProjectPath);
    ui->eProjectPath->setText(projectPath);
}
