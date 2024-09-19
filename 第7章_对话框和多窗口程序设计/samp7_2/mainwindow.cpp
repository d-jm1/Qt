#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_model = new QStandardItemModel(6, 4, this);
    QStringList headers;
    headers << "姓名" <<"性别" << "学位" << "部门";
    m_model->setHorizontalHeaderLabels(headers);
    m_selection = new QItemSelectionModel(m_model, this);
    connect(m_selection, &QItemSelectionModel::currentChanged, this, &MainWindow::do_model_currentChanged);
    ui->tableView->setModel(m_model);
    ui->tableView->setSelectionModel(m_selection);
    setCentralWidget(ui->tableView);
    lab_cell_pos = new QLabel("当前单元格: ", this);
    lab_cell_pos->setMinimumWidth(180);
    lab_cell_pos->setAlignment(Qt::AlignHCenter);
    ui->statusbar->addWidget(lab_cell_pos);
    lab_cell_text = new QLabel("单元格内容: ", this);
    lab_cell_text->setMinimumWidth(200);
    ui->statusbar->addWidget(lab_cell_text);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    auto result = QMessageBox::question(this,"确认", "确定要退出本程序吗?");
    if (result == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

void MainWindow::do_setCellText(int col, int row, QString &text)
{
    auto index = m_model->index(row, col);a
    m_selection->clearSelection();
    m_selection->setCurrentIndex(index, QItemSelectionModel::Select);
    m_model->setData(index, text, Qt::DisplayRole);
}

void MainWindow::do_model_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if(current.isValid())
    {
        lab_cell_pos->setText(QString::asprintf("当前单元格: %d行, %d 列", current.row(), current.column()));
        auto item = m_model->itemFromIndex(current);
        this->lab_cell_text->setText("单元格内容: " + item->text());
    }
}

void MainWindow::on_act_set_list_rows_cols_triggered()
{
    auto dlg_table_size = new DialogSize(this);
    dlg_table_size->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    dlg_table_size->setRowCol(m_model->rowCount(), m_model->columnCount());
    auto ret = dlg_table_size->exec();
    if(ret == QDialog::Accepted)
    {
        auto col = dlg_table_size->col();
        m_model->setColumnCount(col);
        col = dlg_table_size->row();
        m_model->setRowCount(col);
    }
    delete dlg_table_size;
}


void MainWindow::on_actionact_set_list_header_triggered()
{
    if(!dlg_set_headers)
        dlg_set_headers = new DialogHeaders(this);
    if(dlg_set_headers->header().size() != m_model->columnCount())
    {
        QStringList headers;
        for(int i = 0; i < m_model->columnCount(); i++)
            headers << m_model->horizontalHeaderItem(i)->data(Qt::DisplayRole).toString();
        dlg_set_headers->setHeader(headers);
    }
    auto ret = dlg_set_headers->exec();
    if (ret == QDialog::Accepted)
    {
        auto headers = dlg_set_headers->header();
        m_model ->setHorizontalHeaderLabels(headers);
    }
}


void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    emit cellIndexChanged(index.row(), index.column());
}


void MainWindow::on_act_locate_list_cell_triggered()
{
    auto dlg_locate = new DialogLocate(this);
    dlg_locate->setAttribute(Qt::WA_DeleteOnClose);
    dlg_locate->setWindowFlag(Qt::WindowStaysOnTopHint);
    dlg_locate->setSpinRange(m_model->columnCount(), m_model->rowCount());
    auto cur_index = m_selection->currentIndex();
    if(cur_index.isValid())
        dlg_locate->setSpinValue(cur_index.column(), cur_index.row());
    connect(dlg_locate, &DialogLocate::changeCellText, this, &MainWindow::do_setCellText);
    connect(dlg_locate, &DialogLocate::changeActEnable, ui->act_locate_list_cell, &QAction::setEnabled);
    connect(this, &MainWindow::cellIndexChanged, dlg_locate, &DialogLocate::setSpinValue);
    dlg_locate->setModal(false);
    dlg_locate->show();
}

