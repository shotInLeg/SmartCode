#include "s_create_new_entry.h"
#include "ui_s_create_new_entry.h"

SCreateNewEntry::SCreateNewEntry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SCreateNewEntry)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
}

SCreateNewEntry::SCreateNewEntry(const QVector<QPair<QString, QString> > &types,
                                 const QString &basePath,
                                 QWidget *parent):
    QDialog(parent),
    ui(new Ui::SCreateNewEntry)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);

    // Сохраняем базовую папку
    this->basePath = basePath;
    ui->eEntryPath->setText(basePath);

    // Сохраняем типы включений
    this->types = types;

    //Заполняем поле выбора типа
    for(const QPair<QString, QString>& type : types)
    {
        ui->cbEntryType->addItem(type.second);
    }
}

SCreateNewEntry::~SCreateNewEntry()
{
    delete ui;
}

void SCreateNewEntry::on_bAccept_clicked()
{
    int entryTypeIndex = ui->cbEntryType->currentIndex();
    QString entryType = this->types.at(entryTypeIndex).first;

    QString entryPath = ui->eEntryPath->text();
    QString entryName = ui->eEntryName->text();

    emit createEntry(entryType, entryPath, entryName);
    this->close();
}

void SCreateNewEntry::on_bCancel_clicked()
{
    emit canceled();
    this->close();
}

void SCreateNewEntry::on_bSelectEntry_clicked()
{
    QString entryPath = QFileDialog::getExistingDirectory(
                        this, "Выберите путь для добавления элемента", basePath);
    ui->eEntryPath->setText(entryPath);
}
