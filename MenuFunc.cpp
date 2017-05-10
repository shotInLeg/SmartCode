#include "SSmartCode.h"
#include "ui_SSmartCode.h"

void SSmartCode::on_aCreateProject_triggered()
{
    SCreateProjectForm * creator = new SCreateProjectForm();

    connect(creator, SIGNAL(projectCreated(QString)),
            this, SLOT(projectCreated(QString)));


    creator->show();
}

void SSmartCode::projectCreated(QString path)
{
    currentPath = path;
    updateTreeView();
}

void SSmartCode::entryCreated(QString type, QString name)
{
    Q_UNUSED(type);
    Q_UNUSED(name);

    updateTreeView();
}
