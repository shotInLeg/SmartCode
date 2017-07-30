#include "SSmartCode.h"
#include "ui_SSmartCode.h"

SSmartCode::SSmartCode(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SSmartCode)
{
    ui->setupUi(this);
    setupCodeEditor();
    setupTreeView();
    setupRightBar();
    setupBottomBar();
    setupLeftBar();

    currentPath = "";
    currentFile = "";

    codeEditorPos = new QLabel("0|0");
    ui->statusBar->addWidget(codeEditorPos);
}

SSmartCode::~SSmartCode()
{
    delete ui;
}

void SSmartCode::closeEvent(QCloseEvent *event)
{
    cashCurrentDocument();

    if(cashedFiles.size() > 0)
    {
        event->ignore();
        QVector<QString> unsaved;
        for(auto it = cashedFiles.begin();
            it != cashedFiles.end();
            it++)
        {
            unsaved.push_back(it.key());
        }

        SSaveChangesForm * saveForm = new SSaveChangesForm(unsaved);

        connect(saveForm, SIGNAL(save()), this, SLOT(saveAndClose()));
        connect(saveForm, SIGNAL(notSave()), this, SLOT(notSaveAndClose()));

        saveForm->show();
    }
    else
    {
        event->accept();
    }
}


