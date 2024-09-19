#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_str_list << "北京" << "上海" << "天津" << "河北" << "山东" << "四川" << "重庆" << "广东" << "河南";
    m_model = new QStringListModel(this);
    m_model->setStringList(m_str_list);
    ui->listView->setModel(m_model);
    ui->chk_list_editable->setChecked(true);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->btn_list_sort->setCheckable(true);
    ui->btn_list_sort->setFlat(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_list_recv_clicked()
{
    m_model->setStringList(m_str_list);
}


void MainWindow::on_btn_list_clear_clicked()
{
    m_model->removeRows(0, m_model->rowCount());
}


void MainWindow::on_btn_item_add_clicked()
{
    m_model->insertRow(m_model->rowCount());
    auto index = m_model->index(m_model->rowCount()-1, 0);
    m_model->setData(index, "new item", Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}


void MainWindow::on_btn_item_insert_clicked()
{
    auto index = ui->listView->currentIndex();
    m_model->insertRow(index.row());
    m_model->setData(index, "inserted item", Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}


void MainWindow::on_btn_item_rm_clicked()
{
    auto index = ui->listView->currentIndex();
    m_model->removeRow(index.row());
}


void MainWindow::on_btn_item_up_clicked()
{
    auto cur_row = ui->listView->currentIndex().row();
    auto index = QModelIndex();
    m_model->moveRow(index, cur_row, index, cur_row - 1);
}


void MainWindow::on_btn_item_down_clicked()
{
    auto cur_row = ui->listView->currentIndex().row();
    auto index = QModelIndex();
    m_model->moveRow(index, cur_row, index, cur_row + 2);
}




void MainWindow::on_btn_list_sort_clicked(bool checked)
{
    if(checked)
        m_model->sort(0,Qt::AscendingOrder);
    else
        m_model->sort(0,Qt::DescendingOrder);
}


void MainWindow::on_chk_list_editable_clicked(bool checked)
{
    if(checked)
        ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    else
        ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    auto str = QString::asprintf("模型索引: row = %d, column = %d; ", index.row(), index.column());
    auto var = m_model->data(index, Qt::DisplayRole);
    str += var.toString();
    ui->statusbar->showMessage(str);
}


void MainWindow::on_btn_plt_show_clicked()
{
    const auto& tmp_list = m_model->stringList();
    ui->plainTextEdit->clear();
    for(int i = 0; i < tmp_list.size(); i++)
        ui->plainTextEdit->appendPlainText(tmp_list.at(i));
}

