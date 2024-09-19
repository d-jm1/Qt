#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    query_model = new QSqlQueryModel(this);                                     // 数据模型
    select_model = new QItemSelectionModel(query_model, this);
    ui->tableView->setModel(query_model);                                           // 设置数据模型
    ui->tableView->setSelectionModel(select_model);                                 // 设置选择模型
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
}

void MainWindow::updateRecord(int record_no)
{
    auto cur_record = query_model->record(record_no);
    auto emp_no = cur_record.value("empNo").toInt();
    QSqlQuery query(DB);
    query.prepare("SELECT * FROM employee WHERE EmpNo = :ID");
    query.bindValue(":ID", emp_no);
    query.exec();
    query.first();
    if(!query.isValid())
        return;
    cur_record = query.record();
    auto data_dialog = new TDialog(this);
    auto flags = data_dialog->windowFlags();
    data_dialog->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    data_dialog->setUpdateRecord(cur_record);
    auto ret = data_dialog->exec();
    if (ret == QDialog::Accepted)
    {
        auto record_data = data_dialog->getRecord();
        query.prepare("UPDATE employee SET Name = :Name, Gender = :Gender, "
                      " Birthday = :Birthday, Province = :Province, "
                      " Department = :Department, Salary = :Salary, "
                      " Memo = :Memo, Photo = :Photo, "
                      " WHERE EmpNo = :ID");
        query.bindValue(":empNo",       record_data.value("empNo"));
        query.bindValue(":Name",        record_data.value("Name"));
        query.bindValue(":Gender",      record_data.value("Gender"));
        query.bindValue(":Birthday",    record_data.value("Birthday"));
        query.bindValue(":Province",    record_data.value("Province"));
        query.bindValue(":Department",   record_data.value("Department"));
        query.bindValue(":Salary",      record_data.value("Salary"));
        query.bindValue(":Memo",        record_data.value("Memo"));
        query.bindValue(":Photo",       record_data.value("Photo"));
        query.bindValue(":ID",          emp_no);
        if(!query.exec())
            QMessageBox::critical(this, "错误", "记录更新错误\n", query.lastError().text());
        else
        {
            auto sql = query_model->query().executedQuery();
            query_model->setQuery(sql);
        }
    }
    delete data_dialog;
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

void MainWindow::on_act_edit_record_triggered()
{
    auto cur_redord_no = select_model->currentIndex().row();
    updateRecord(cur_redord_no);
}


void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    auto cur_record_no = index.row();
    updateRecord(cur_record_no);
}


void MainWindow::on_act_insert_triggered()
{
    QSqlQuery query(DB);
    query.exec("SELECT * FROM employee WHERE empNo = -1");
    auto cur_record = query.record();
    for (int i = 0; i < cur_record.count(); ++i) {
        QString fieldName = cur_record.fieldName(i);
        qDebug() << fieldName;
    }
    auto data_dialog = new TDialog(this);
    auto flags = data_dialog->windowFlags();
    data_dialog->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    data_dialog->setInsertRecord(cur_record);
    auto ret = data_dialog->exec();
    if (ret == QDialog::Accepted)
    {
        auto record_data = data_dialog->getRecord();
        query.prepare("INSERT INTO employee(empNo,Name,Gender,Birthday,Province,Department,Salary,Memo,Photo)"
                      "VALUES (:empNo, :Name, :Gender, :Birthday, :Province, :Department, :Salary, :Memo, :Photo)");
        query.bindValue(":empNo",       record_data.value("empNo"));
        query.bindValue(":Name",        record_data.value("Name"));
        query.bindValue(":Gender",      record_data.value("Gender"));
        query.bindValue(":Birthday",    record_data.value("Birthday"));
        query.bindValue(":Province",    record_data.value("Province"));
        query.bindValue(":Department",   record_data.value("Department"));
        query.bindValue(":Salary",      record_data.value("Salary"));
        query.bindValue(":Memo",        record_data.value("Memo"));
        query.bindValue(":Photo",       record_data.value("Photo"));

        qDebug() << record_data.value("empNo").toInt();
        qDebug() << record_data.value("Name").toString();
        qDebug() << record_data.value("Gender").toString();
        qDebug() << record_data.value("Birthday").toDate();
        qDebug() << record_data.value("Province").toString();
        qDebug() << record_data.value("Department").toString();
        qDebug() << record_data.value("Salary").toFloat();
        qDebug() << record_data.value("Memo").toString();

        if(!query.exec())
            QMessageBox::critical(this, "错误", "记录更新错误\n", query.lastError().text());
        else
        {
            auto sql = query_model->query().executedQuery();
            query_model->setQuery(sql);
        }
    }
    delete data_dialog;
}


void MainWindow::on_act_remove_triggered()
{
    auto cur_index = select_model->currentIndex().row();
    auto cur_record = query_model->record(cur_index);
    if(cur_record.isEmpty())
        return;
    auto emp_no = cur_record.value("empNo");
    QSqlQuery query(DB);
    query.prepare("DELETE FROM employee where empNo = :empNo");
    query.bindValue(":empNo", emp_no);
    if(!query.exec())
        QMessageBox::critical(this, "错误", "记录更新错误\n", query.lastError().text());
    else
    {
        auto sql = query_model->query().executedQuery();
        query_model->setQuery(sql);
    }
}


void MainWindow::on_act_salary_up_triggered()
{
    QSqlQuery query(DB);
    query.prepare("UPDATE employee SET Salary = :Salary WHERE empNo = :ID");
    QSqlQuery query_list(DB);
    query_list.setForwardOnly(true);
    query_list.exec("SELECT empNo, Salary FROM employee ORDER BY empNo");
    query_list.first();
    while(query_list.isValid())
    {
        auto id = query_list.value("empNo").toInt();
        auto salary = 1000 + query_list.value("Salary").toFloat();
        query.bindValue(":ID", id);
        query.bindValue(":Salary", salary);
        query.exec();
        qDebug() << id << ": " << salary;
        query_list.next();
    }
    auto sql = query_model->query().executedQuery();
    query_model->setQuery(sql);
    QMessageBox::information(this, "消息", "涨工资数据计算完毕");
}

