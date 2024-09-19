#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->tableView);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setAlternatingRowColors(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_currentChanged(const QModelIndex &, const QModelIndex &)
{
    ui->act_save->setEnabled(table_model->isDirty());
    ui->act_cancel->setEnabled(table_model->isDirty());
}

void MainWindow::openTable()
{
    // 1. 创建数据模型, 打开数据表
    table_model = new QSqlRelationalTableModel(this, db);                                     // 数据模型
    table_model->setTable("studinfo");                                              // 设置数据表
    table_model->setEditStrategy(QSqlTableModel::OnManualSubmit);                   // 设置数据保存方式 为手动提交
    table_model->setSort(table_model->fieldIndex("studID"), Qt::AscendingOrder);     // 按照 empNo 列升序排序

    // 2. 设置字段显示标题
    table_model->setHeaderData(table_model->fieldIndex("studID"), Qt::Horizontal, "学号");
    table_model->setHeaderData(table_model->fieldIndex("name"), Qt::Horizontal, "姓名");
    table_model->setHeaderData(table_model->fieldIndex("gender"), Qt::Horizontal, "性别");
    table_model->setHeaderData(table_model->fieldIndex("departID"), Qt::Horizontal, "学院");
    table_model->setHeaderData(table_model->fieldIndex("majorID"), Qt::Horizontal, "专业");

    // 3. 外键关系设置
    table_model->setRelation(table_model->fieldIndex("departID"), QSqlRelation("departments","departID","department"));
    table_model->setRelation(table_model->fieldIndex("majorID"), QSqlRelation("majors","majorID","major"));
    select_model = new QItemSelectionModel(table_model, this);
    connect(select_model, &QItemSelectionModel::currentChanged, this, &MainWindow::do_currentChanged);
    ui->tableView->setModel(table_model);
    ui->tableView->setSelectionModel(select_model);

    // 4. 设置外键字段代理
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    table_model->select();                                                          // 查询表数据

    ui->act_open_db->setEnabled(false);
    ui->act_add->setEnabled(true);
    ui->act_insert->setEnabled(true);
    ui->act_remove->setEnabled(true);
    ui->act_column_list->setEnabled(true);

    qDebug() << table_model->rowCount();
}


void MainWindow::on_act_open_db_triggered()
{
    auto file_name = QFileDialog::getOpenFileName(this, "打开数据库","","数据库文件(*.db3)");
    if(file_name.isEmpty())
        return;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(file_name);
    if(db.open())
        openTable();
    else
        QMessageBox::warning(this, "错误", "打开数据库失败");
}


void MainWindow::on_act_column_list_triggered()
{
    auto record = table_model->record();
    QString str;
    for(int i = 0; i < record.count(); i++)
        str += record.fieldName(i) + "\n";
    QMessageBox::information(this, "所有字段名", str);
}

