#ifndef S_CONFIRM_REMOVE_H
#define S_CONFIRM_REMOVE_H

#include <QDialog>
#include <QVector>
#include <QString>
#include <QCheckBox>

namespace Ui {
class SConfirmRemove;
}

class SConfirmRemove : public QDialog
{
    Q_OBJECT

public:
    explicit SConfirmRemove(QWidget *parent = 0);
    explicit SConfirmRemove(const QVector<QString>& filesToRemove,
                            QWidget *parent = 0);
    ~SConfirmRemove();

private:
    Ui::SConfirmRemove *ui;
    QVector<QString> filesToRemove;
    QVector<QCheckBox*> checkers;

signals:
    void removeFiles(QVector<QString>);
    void canceled();
private slots:
    void on_bRemoveChecked_clicked();
    void on_bCheckAll_clicked();
    void on_bRevertChecked_clicked();
    void on_bCancel_clicked();
};

#endif // S_CONFIRM_REMOVE_H
