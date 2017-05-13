#include "SSmartCode.h"
#include "ui_SSmartCode.h"


//File

void SSmartCode::on_aCreateProject_triggered()
{
    SCreateProjectForm * creator = new SCreateProjectForm();
    connect(creator,
            SIGNAL(projectCreated(QString)),
            this,
            SLOT(projectCreated(QString)));
    creator->show();
}

void SSmartCode::on_aOpenProject_triggered()
{
    currentPath = QFileDialog::getExistingDirectory(this,
                                                    "Открыть проект",
                                                    "~");
    updateTreeView();
    ui->wLeftSide->show();
    ui->aProjectTree->setChecked(true);
}

//Edit

void SSmartCode::on_aFindReplace_triggered()
{
    ui->wRightSide->show();
}

//Panels

void SSmartCode::on_aPanelFindReplace_triggered()
{
    if(ui->wRightSide->isHidden())
    {
        ui->wRightSide->show();
        ui->swRight->setCurrentIndex(1);
    }
    else if(ui->swRight->currentIndex() != 1)
    {
        ui->swRight->setCurrentIndex(1);
    }
    else
    {
        ui->wRightSide->hide();
    }
}

void SSmartCode::on_aTerminal_triggered()
{
    if(ui->wBotomSide->isHidden())
    {
        ui->wBotomSide->show();
    }
    else
    {
        ui->wBotomSide->hide();
    }
}

void SSmartCode::on_aProjectTree_triggered()
{
    if(ui->wLeftSide->isHidden())
    {
        ui->wLeftSide->show();
    }
    else
    {
        ui->wLeftSide->hide();
    }
}



