#ifndef S_CONFIRM_REMOVE_H
#define S_CONFIRM_REMOVE_H

#include <QDialog>

namespace Ui {
class SConfirmRemove;
}

class SConfirmRemove : public QDialog
{
    Q_OBJECT

public:
    explicit SConfirmRemove(QWidget *parent = 0);
    ~SConfirmRemove();

private:
    Ui::SConfirmRemove *ui;
};

#endif // S_CONFIRM_REMOVE_H
