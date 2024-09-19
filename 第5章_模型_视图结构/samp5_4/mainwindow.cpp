#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_model = new QFileSystemModel(this);
    m_model->setRootPath(QDir::currentPath());
    // qDebug() << "当前路经是: " << QDir::currentPath();
    ui->treeView->setModel(m_model);
    ui->listView->setModel(m_model);
    ui->tableView->setModel(m_model);

    connect(ui->treeView, &QAbstractItemView::clicked, ui->listView, &QAbstractItemView::setRootIndex);
    connect(ui->treeView, &QAbstractItemView::clicked, ui->tableView, &QAbstractItemView::setRootIndex);

    ui->com_box_filter->setEditable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->chk_is_folder->setChecked(m_model->isDir(index));
    ui->lab_file_path->setText(m_model->filePath(index));
    ui->lab_file_type->setText(m_model->type(index));
    ui->lab_file_name->setText(m_model->fileName(index));
    auto size = m_model->size(index) / 1024;
    if(size < 1024)
        ui->lab_file_size->setText(QString("%1 KB").arg(size));
    else
        ui->lab_file_size->setText(QString::asprintf("%.1f MB", size/1024.0));
}


void MainWindow::on_act_set_root_floder_triggered()
{
    auto dir = QFileDialog::getExistingDirectory(this, "选择目录", QDir::currentPath());
    if(!dir.isEmpty())
    {
        m_model->setRootPath(dir);
        ui->treeView->setRootIndex(m_model->index(dir));
    }
}


void MainWindow::on_rbt_show_folder_files_clicked()
{
    ui->widget->setEnabled(true);
    m_model->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
}


void MainWindow::on_rbt_show_only_files_clicked()
{
    ui->widget->setEnabled(false);
    m_model->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
}


void MainWindow::on_chk_file_filt_clicked(bool checked)
{
    m_model->setNameFilterDisables(!checked);
    ui->com_box_filter->setEnabled(checked);
    ui->btn_do_filt->setEnabled(checked);
}


void MainWindow::on_btn_do_filt_clicked()
{
    auto flts = ui->com_box_filter->currentText().trimmed();
    auto filter = flts.split(";", Qt::SkipEmptyParts);
    m_model->setNameFilters(filter);
}

