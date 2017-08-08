#include "s_git_commit.h"
#include "ui_s_git_commit.h"

SGitCommit::SGitCommit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SGitCommit)
{
    ui->setupUi(this);
}

SGitCommit::SGitCommit(const QVector<QPair<QString, QString> > &untrackedFiles,
                       const QVector<QPair<QString, QString> > &trackedFiles,
                       QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SGitCommit)
{
    ui->setupUi(this);

    this->untrackedFiles = untrackedFiles;
    this->trackedFiles = trackedFiles;

    updateUntracked();
    updateTracked();
}

SGitCommit::~SGitCommit()
{
    delete ui;
}

void SGitCommit::on_bAddToTracked_clicked()
{
    QVector<int> selected
            = getSelectedRows(ui->lwUntrackedFiles->selectionModel()->selectedIndexes());

    for(int index : selected)
    {
        addToTracked(index);
    }

    updateUntracked();
    updateTracked();
}

void SGitCommit::on_bAddToUntracked_clicked()
{
    QVector<int> selected
            = getSelectedRows(ui->lwTrackedFiles->selectionModel()->selectedIndexes());

    for(int index : selected)
    {
        addToUntracked(index);
    }

    updateUntracked();
    updateTracked();
}


void SGitCommit::updateUntracked()
{
    ui->lwUntrackedFiles->clear();

    for(const QPair<QString, QString>& item : untrackedFiles)
    {
        ui->lwUntrackedFiles->addItem(item.second);
    }
}

void SGitCommit::updateTracked()
{
    ui->lwTrackedFiles->clear();

    for(const QPair<QString, QString>& item : trackedFiles)
    {
        ui->lwTrackedFiles->addItem(item.second);
    }
}

void SGitCommit::addToUntracked(int index)
{
    if(index > trackedFiles.size() || index < 0)
        return;

    QPair<QString, QString> item = trackedFiles.at(index);
    trackedFiles.remove(index);

    untrackedFiles.push_back(item);
}

void SGitCommit::addToTracked(int index)
{
    if(index > untrackedFiles.size() || index < 0)
        return;

    QPair<QString, QString> item = untrackedFiles.at(index);
    untrackedFiles.remove(index);

    trackedFiles.push_back(item);

    updateUntracked();
    updateTracked();
}

QVector<int> SGitCommit::getSelectedRows(const QModelIndexList &selected)
{
    QVector<int> rows;
    for(const QModelIndex& item : selected)
    {
        rows.push_back(item.row());
    }

    rows = sort(rows);

    return rows;
}

QVector<int> SGitCommit::sort(QVector<int> vec)
{
    for(int i = 0; i < vec.size()-1; i++)
    {
        int max = i;
        for(int j = i+1; j < vec.size(); j++)
        {
            if(vec.at(max) < vec.at(j))
            {
                max = j;
            }
        }

        int temp = vec.at(i);
        vec[i] = vec.at(max);
        vec[max] = temp;
    }

    return vec;
}

void SGitCommit::on_bCommit_clicked()
{
    QString commitMessage = ui->pteCommit->toPlainText();

    emit commit(untrackedFiles, trackedFiles, commitMessage);

    trackedFiles.clear();

    updateUntracked();
    updateTracked();
}

void SGitCommit::on_bCancel_clicked()
{
    emit canceled();
    this->close();
}

void SGitCommit::on_pteCommit_textChanged()
{
    if( !ui->pteCommit->toPlainText().isEmpty() )
    {
        ui->bCommit->setEnabled(true);
    }
    else
    {
        ui->bCommit->setEnabled(false);
    }
}
