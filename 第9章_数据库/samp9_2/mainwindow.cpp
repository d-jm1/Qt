#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);    // 选择行为为项选择
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);    // 单项选择模式
    ui->tableView->setAlternatingRowColors(true);                           // 设置表格隔行颜色显示
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectData()
{
    // 1. 创建数据模型, 打开数据表
    query_model = new QSqlQueryModel(this);
    query_model->setQuery("SELECT empNo, Name, Gender, Birthday, Province, Department,"
                          " Salary From employee ORDER BY empNo");
    if (query_model->lastError().isValid())
    {
        QMessageBox::critical(this, "错误", "数据表查询错误, 错误信息\n" + query_model->lastError().text());
        return;
    }

    // 2. 设置字段显示标题
    auto record = query_model->record();
    query_model->setHeaderData(record.indexOf("empNo"), Qt::Horizontal, "工号");
    query_model->setHeaderData(record.indexOf("Name"), Qt::Horizontal, "姓名");
    query_model->setHeaderData(record.indexOf("Gender"), Qt::Horizontal, "性别");
    query_model->setHeaderData(record.indexOf("Birthday"), Qt::Horizontal, "出生日期");
    query_model->setHeaderData(record.indexOf("Province"), Qt::Horizontal, "省份");
    query_model->setHeaderData(record.indexOf("Department"), Qt::Horizontal, "部门");
    query_model->setHeaderData(record.indexOf("Salary"), Qt::Horizontal, "工资");

    // 3. 创建选择模型
    select_model = new QItemSelectionModel(query_model, this);
    connect(select_model, &QItemSelectionModel::currentRowChanged, this, &MainWindow::do_currentRowChanged);
    ui->tableView->setModel(query_model);                                           // 设置数据模型
    ui->tableView->setSelectionModel(select_model);                                 // 设置选择模型

    // 4. 创建界面组件和模型的数据映射
    data_mapper = new QDataWidgetMapper(this);
    data_mapper->setModel(query_model);                                             // 设置数据模型
    data_mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);                    // 自动提交保存
    data_mapper->addMapping(ui->spinBox, record.indexOf("empNo"));
    data_mapper->addMapping(ui->lineEdit, record.indexOf("Name"));
    data_mapper->addMapping(ui->comboBox_2, record.indexOf("Gender"));
    data_mapper->addMapping(ui->dateEdit, record.indexOf("Birthday"));
    data_mapper->addMapping(ui->comboBox_4, record.indexOf("Province"));
    data_mapper->addMapping(ui->comboBox_5, record.indexOf("Department"));
    data_mapper->addMapping(ui->spinBox_2, record.indexOf("Salary"));
    data_mapper->toFirst();

    // 5. 更新 action 和 界面组件 的使能状态
    ui->act_open_db->setEnabled(false);
}

void MainWindow::refreshTableView()
{
    auto index = data_mapper->currentIndex();
    auto cur_index = query_model->index(index, 1);
    select_model->clearSelection();
    select_model->setCurrentIndex(cur_index, QItemSelectionModel::Select);
}

void MainWindow::do_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if (!current.isValid())
    {
        ui->label_2->clear();
        ui->plainTextEdit->clear();
        return;
    }

    data_mapper->setCurrentModelIndex(current);

    qDebug() << "当前行 : " << current.row();
    auto first = current.row()!=0;
    auto last = current.row()!=(query_model->rowCount() - 1);
    ui->act_front_record->setEnabled(first);
    ui->act_back_record->setEnabled(last);
    ui->act_previous_record->setEnabled(first);
    ui->act_next_record->setEnabled(last);

    auto cur_record_no = select_model->currentIndex().row();
    auto cur_record = query_model->record(cur_record_no);
    auto empNo = cur_record.value("EmpNo").toInt();
    QSqlQuery query;
    query.prepare("SELECT empNo, Memo, Photo From employee WHERE EmpNo = :ID ");
    query.bindValue(":ID", empNo);
    query.exec();
    query.first();

    QVariant photo = query.value("Photo");
    if (!photo.isValid())
        ui->label_2->clear();
    else
    {
        auto data = photo.toByteArray();
        QPixmap pic;
        pic.loadFromData(data);
        ui->label_2->setPixmap(pic.scaledToWidth(ui->label_2->size().width()));
    }
    QVariant Memo = query.value("Memo");
    ui->plainTextEdit->setPlainText(Memo.toString());
}



void MainWindow::on_act_open_db_triggered()
{
    auto file_name = QFileDialog::getOpenFileName(this, "选择文件", "","SQLite数据库(*.db3)");
    if (file_name.isEmpty())
        return;
    DB = QSqlDatabase::addDatabase("QSQLITE");                              // 添加 SQLite 驱动
    DB.setDatabaseName(file_name);
    // 网络数据库还需要设置下面的选项
    // DB.setHostName();
    // DB.setUserName();
    // DB.setPassword();
    if(!DB.open())
        QMessageBox::warning(this, "错误", "打开数据库失败");
    else
        selectData();
}


void MainWindow::on_act_front_record_triggered()
{
    data_mapper->toFirst();
    refreshTableView();
}


void MainWindow::on_act_previous_record_triggered()
{
    data_mapper->toPrevious();
    refreshTableView();
}


void MainWindow::on_act_next_record_triggered()
{
    data_mapper->toNext();
    refreshTableView();
}


void MainWindow::on_act_back_record_triggered()
{
    data_mapper->toLast();
    refreshTableView();
}

