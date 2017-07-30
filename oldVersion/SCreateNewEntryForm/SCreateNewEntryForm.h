#ifndef SCREATENEWENTRYFORM_H
#define SCREATENEWENTRYFORM_H

#include <QWidget>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class SCreateNewEntryForm;
}

class SCreateNewEntryForm : public QWidget
{
    Q_OBJECT

public:
    explicit SCreateNewEntryForm(const QString& parentPath,
                                 QWidget *parent = 0);
    ~SCreateNewEntryForm();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

signals:
    void entryCreated(QString, QString);

private:
    Ui::SCreateNewEntryForm *ui;
    QString parentPath;
};

#endif // SCREATENEWENTRYFORM_H
