#ifndef S_GIT_COMMIT_H
#define S_GIT_COMMIT_H

#include <QDialog>
#include <QModelIndexList>

namespace Ui {
class SGitCommit;
}

class SGitCommit : public QDialog
{
    Q_OBJECT

public:
    explicit SGitCommit(QWidget *parent = 0);
    explicit SGitCommit(const QVector<QPair<QString, QString> >& untrackedFiles,
                        const QVector<QPair<QString, QString> >& trackedFiles,
                        QWidget *parent = 0);
    ~SGitCommit();

signals:
    void commit(QVector<QPair<QString, QString> >,
                QVector<QPair<QString, QString> >,
                const QString&);
    void viewChanges(QString);
    void canceled();

private slots:
    void on_bAddToTracked_clicked();
    void on_bAddToUntracked_clicked();

    void on_bCommit_clicked();
    void on_bCancel_clicked();

    void on_pteCommit_textChanged();

    void on_lwUntrackedFiles_doubleClicked(const QModelIndex &index);
    void on_lwTrackedFiles_doubleClicked(const QModelIndex &index);

private:
    void updateUntracked();
    void updateTracked();

    void addToUntracked(int index);
    void addToTracked(int index);

    QVector<int> getSelectedRows(const QModelIndexList& selected);
    QVector<int> sort(QVector<int> vec);

private:
    Ui::SGitCommit *ui;

    QVector<QPair<QString, QString> > untrackedFiles;
    QVector<QPair<QString, QString> > trackedFiles;
};

#endif // S_GIT_COMMIT_H
