#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mdiArea->setTabsClosable(true);
    ui->mdiArea->setTabsMovable(true);
    setCentralWidget(ui->mdiArea);
    setWindowState(Qt::WindowMaximized);
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_act_doc_new_triggered()
{
    auto form_doc = new TFormDoc(this);
    ui->mdiArea->addSubWindow(form_doc);
    form_doc->show();
    ui->act_cut->setEnabled(true);
    ui->act_copy->setEnabled(true);
    ui->act_paste->setEnabled(true);
    ui->act_font->setEnabled(true);
}


void MainWindow::on_act_doc_open_triggered()
{
    bool need_new = false;
    TFormDoc *form_doc;
    if(ui->mdiArea->subWindowList().size() > 0)
    {
        form_doc = (TFormDoc*) ui->mdiArea->activeSubWindow()->widget();
        need_new = form_doc->getFile_opened();
    }
    else
        need_new = true;

    auto cur_path = QDir::currentPath();
    auto file_name = QFileDialog::getOpenFileName(this, tr("打开一个文件"), cur_path, "C程序文件(*.h *.cpp);; 文本文件(*.txt);;所有文件(*.*)");

    if(file_name.isEmpty())
        return;
    if(need_new)
    {
        form_doc = new TFormDoc(this);
        ui->mdiArea->addSubWindow(form_doc);
    }
    form_doc->loadFromFile(file_name);
    form_doc->show();
    ui->act_cut->setEnabled(true);
    ui->act_copy->setEnabled(true);
    ui->act_paste->setEnabled(true);
    ui->act_font->setEnabled(true);
}


void MainWindow::on_act_mdi_model_triggered(bool checked)
{
    if(checked)
        ui->mdiArea->setViewMode(QMdiArea::TabbedView);
    else
        ui->mdiArea->setViewMode(QMdiArea::SubWindowView);
    ui->mdiArea->setTabsClosable(checked);
    ui->act_cascade->setEnabled(!checked);
    ui->act_tile->setEnabled(!checked);
}


void MainWindow::on_act_font_triggered()
{
    auto form_doc = static_cast<TFormDoc*>(ui->mdiArea->activeSubWindow()->widget());
    form_doc->setEditFont();
}


void MainWindow::on_act_cut_triggered()
{
    auto form_doc = static_cast<TFormDoc*>(ui->mdiArea->activeSubWindow()->widget());
    form_doc->textCut();
}


void MainWindow::on_act_copy_triggered()
{
    auto form_doc = static_cast<TFormDoc*>(ui->mdiArea->activeSubWindow()->widget());
    form_doc->textCopy();
}


void MainWindow::on_act_paste_triggered()
{
    auto form_doc = static_cast<TFormDoc*>(ui->mdiArea->activeSubWindow()->widget());
    form_doc->textPaste();
}


void MainWindow::on_act_doc_save_triggered()
{
    auto form_doc = static_cast<TFormDoc*>(ui->mdiArea->activeSubWindow()->widget());
    form_doc->saveToFile();
}


void MainWindow::on_mdiArea_subWindowActivated(QMdiSubWindow *arg1)
{
    if (ui->mdiArea->subWindowList().size() == 0)
    {
        ui->act_cut->setEnabled(false);
        ui->act_copy->setEnabled(false);
        ui->act_paste->setEnabled(false);
        ui->act_font->setEnabled(false);
        ui->statusbar->clearMessage();
    }
    else
    {
        auto form_doc = static_cast<TFormDoc*>(arg1->widget());
        ui->statusbar->showMessage(form_doc->getFile_name());
    }
}

