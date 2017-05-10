#ifndef SCREATENEWENTRY_H
#define SCREATENEWENTRY_H

#include <QWidget>
#include <QDir>
#include <QFile>
#include <QMessageBox>

namespace Ui {
class SCreateNewEntry;
}

class SCreateNewEntry : public QWidget
{
    Q_OBJECT

public:
    explicit SCreateNewEntry(QString parentPath, QWidget *parent = 0);
    ~SCreateNewEntry();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:
    void entryCreated(QString, QString);

private:
    Ui::SCreateNewEntry *ui;
    QString pPath;
};

#endif // SCREATENEWENTRY_H
