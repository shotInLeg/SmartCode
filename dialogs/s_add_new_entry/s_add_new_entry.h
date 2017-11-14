#ifndef S_ADD_NEW_ENTRY_H
#define S_ADD_NEW_ENTRY_H

#include <QDialog>
#include <QVector>
#include <QString>
#include <QPair>
#include <QFileDialog>

namespace Ui {
class SAddNewEntry;
}

class SAddNewEntry : public QDialog
{
    Q_OBJECT

public:
    explicit SAddNewEntry(QWidget *parent = 0);
    explicit SAddNewEntry(const QVector<QPair<QString, QString> > &types,
                          const QString &basePath,
                          QWidget *parent = 0);
    ~SAddNewEntry();

private slots:
    void on_bAdd_clicked();

    void on_bCancel_clicked();

    void on_bChoosePath_clicked();

    void on_bChooseEntryPath_clicked();

    void on_cbEntryType_currentIndexChanged(int);

signals:
    void addEntry(const QString&,
                  const QString&,
                  const QString&,
                  const QString&);
    void canceled();

private:
    Ui::SAddNewEntry *ui;

    QVector<QPair<QString, QString> > types;
    QString basePath;

};

#endif // S_ADD_NEW_ENTRY_H
