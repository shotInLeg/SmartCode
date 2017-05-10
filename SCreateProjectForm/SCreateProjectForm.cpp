#include "SCreateProjectForm.h"
#include "ui_SCreateProjectForm.h"
#include <QDebug>

SCreateProjectForm::SCreateProjectForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SCreateProjectForm)
{
    ui->setupUi(this);
}

SCreateProjectForm::~SCreateProjectForm()
{
    delete ui;
}

void SCreateProjectForm::on_buttonBox_accepted()
{
    data.insert("PROJECT NAME", ui->eNameProject->text());
    data.insert("PROJECT PATH", ui->ePath->text());
    data.insert("TRANSLATOR PATH", ui->eCompiler->text());
    data.insert("MAIN LANG", ui->cbLang->currentText());

    makeProject();

    emit projectCreated(projPath);

    this->close();
}

void SCreateProjectForm::on_buttonBox_rejected()
{
    this->close();
}

void SCreateProjectForm::on_bChoosePath_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,
                                                     "Выберите папку",
                                                     "~");
    ui->ePath->setText(path);
}

void SCreateProjectForm::on_bChooseCompiler_clicked()
{
    QString translator = QFileDialog::getOpenFileName(this,
                                                      "Выберите транслятор",
                                                      "~");
    ui->eCompiler->setText(translator);
}

void SCreateProjectForm::makeProject()
{
    QString path = data.value("PROJECT PATH");
    QString project = data.value("PROJECT NAME");
    QString translator = data.value("TRANSLATOR PATH");
    QString lang = data.value("MAIN LANG");

    QDir projectDir(path);
    qDebug() << projectDir.mkpath(project);
    qDebug() << projectDir.cd(project);

    projPath = projectDir.absolutePath();
    QString proFilePath = projectDir.absolutePath() + "/" + project + ".scp";

    qDebug() << proFilePath;

    QFile proFile(proFilePath);

    if( !proFile.open(QIODevice::WriteOnly) )
    {
        QMessageBox::information(this, "Ошибка", "Во время создания файла "
                                                 "проекта произошла ошибка. "
                                                 "Проверьте, что указанная папка "
                                                 "существует и у приложения есть "
                                                 "доступ на запись в нее.");
        return;
    }

    proFile.write( ("PROJECT NAME:" + project + "\n").toLatin1() );
    proFile.write( ("MAIN LANG:" + lang + "\n").toLatin1() );
    proFile.write( ("RANSLATOR PATH:" + translator + "\n").toLatin1() );

    proFile.close();
}
