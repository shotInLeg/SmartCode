#ifndef S_CREATE_NEW_ENTRY_H
#define S_CREATE_NEW_ENTRY_H

#include <QDialog>
#include <QString>
#include <QVector>
#include <QPair>
#include <QFileDialog>

namespace Ui {
class SCreateNewEntry;
}

class SCreateNewEntry : public QDialog
{
    Q_OBJECT

public:
    explicit SCreateNewEntry(QWidget *parent = 0);
    explicit SCreateNewEntry(const QVector<QPair<QString, QString> >& types,
                             const QString& basePath,
                             QWidget *parent = 0);
    ~SCreateNewEntry();

private slots:
    void on_bAccept_clicked();
    void on_bCancel_clicked();

    void on_bSelectEntry_clicked();

signals:
    void createEntry(QString entryType,
                     QString entryPath,
                     QString entryName);
    void canceled();

private:
    Ui::SCreateNewEntry *ui;

    QString basePath;
    QVector<QPair<QString, QString> > types;
};

#endif // S_CREATE_NEW_ENTRY_H
