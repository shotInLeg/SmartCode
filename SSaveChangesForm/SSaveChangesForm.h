#ifndef SSAVECHANGESFORM_H
#define SSAVECHANGESFORM_H

#include <QWidget>

namespace Ui {
class SSaveChangesForm;
}

class SSaveChangesForm : public QWidget
{
    Q_OBJECT

public:
    explicit SSaveChangesForm(const QVector<QString>& files,
                              QWidget *parent = 0);
    ~SSaveChangesForm();

private slots:
    void on_bSave_clicked();

    void on_bNotSave_clicked();

    void on_bCancel_clicked();

signals:
    void save();
    void notSave();

private:
    Ui::SSaveChangesForm *ui;
};

#endif // SSAVECHANGESFORM_H
