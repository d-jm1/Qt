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

void MainWindow::openTable()
{
    // 1. 创建数据模型, 打开数据表
    table_model = new QSqlTableModel(this, DB);                                     // 数据模型
    table_model->setTable("employee");                                              // 设置数据表
    table_model->setEditStrategy(QSqlTableModel::OnManualSubmit);                   // 设置数据保存方式 为手动提交
    table_model->setSort(table_model->fieldIndex("empNo"), Qt::AscendingOrder);     // 按照 empNo 列升序排序
    if (!table_model->select())
    {
        QMessageBox::critical(this, "错误", "打开数据表错误, 错误信息: \n" + table_model->lastError().text());
        return;
    }
    showRecordCount();

    // 2. 设置字段显示标题
    table_model->setHeaderData(table_model->fieldIndex("empNo"), Qt::Horizontal, "工号");
    table_model->setHeaderData(table_model->fieldIndex("Name"), Qt::Horizontal, "姓名");
    table_model->setHeaderData(table_model->fieldIndex("Gender"), Qt::Horizontal, "性别");
    table_model->setHeaderData(table_model->fieldIndex("Birthday"), Qt::Horizontal, "出生日期");
    table_model->setHeaderData(table_model->fieldIndex("Province"), Qt::Horizontal, "省份");
    table_model->setHeaderData(table_model->fieldIndex("Department"), Qt::Horizontal, "部门");
    table_model->setHeaderData(table_model->fieldIndex("Salary"), Qt::Horizontal, "工资");
    // 在 tabView 中不显示一下两项
    table_model->setHeaderData(table_model->fieldIndex("Memo"), Qt::Horizontal, "备注");
    table_model->setHeaderData(table_model->fieldIndex("Photo"), Qt::Horizontal, "照片");

    // 3. 创建选择模型
    select_model = new QItemSelectionModel(table_model, this);
    connect(select_model, &QItemSelectionModel::currentChanged, this, &MainWindow::do_currentChanged);
    connect(select_model, &QItemSelectionModel::currentRowChanged, this, &MainWindow::do_currentRowChanged);

    // 4. 模型/视图结构
    ui->tableView->setModel(table_model);                                           // 设置数据模型
    ui->tableView->setSelectionModel(select_model);                                 // 设置选择模型
    ui->tableView->setColumnHidden(table_model->fieldIndex("Memo"), true);          // 隐藏 Memo 列
    ui->tableView->setColumnHidden(table_model->fieldIndex("Photo"), true);         // 隐藏 Photo 列

    // 5. 为 tableView 中的 性别 和 部门 字段设置代理
    QStringList strList;
    strList << "男" << "女";
    bool isEditable = false;
    delegateSex.setItems(strList, isEditable);
    ui->tableView->setItemDelegateForColumn(table_model->fieldIndex("Gender"), &delegateSex);
    ui->comboBox_2->addItems(strList);
    strList.clear();
    strList << "销售部" << "技术部" << "生产部" << "行政部";
    isEditable = true;
    delegateDepart.setItems(strList, isEditable);
    ui->tableView->setItemDelegateForColumn(table_model->fieldIndex("Department"), &delegateDepart);
    ui->comboBox_5->addItems(strList);
    ui->comboBox_5->setEditable(isEditable);

    // 6. 创建界面组件和模型的数据映射
    data_mapper = new QDataWidgetMapper(this);
    data_mapper->setModel(table_model);                                             // 设置数据模型
    data_mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);                    // 自动提交保存
    data_mapper->addMapping(ui->spinBox, table_model->fieldIndex("empNo"));
    data_mapper->addMapping(ui->lineEdit, table_model->fieldIndex("Name"));
    data_mapper->addMapping(ui->comboBox_2, table_model->fieldIndex("Gender"));
    data_mapper->addMapping(ui->dateEdit, table_model->fieldIndex("Birthday"));
    data_mapper->addMapping(ui->comboBox_4, table_model->fieldIndex("Province"));
    data_mapper->addMapping(ui->comboBox_5, table_model->fieldIndex("Department"));
    data_mapper->addMapping(ui->spinBox_2, table_model->fieldIndex("Salary"));
    data_mapper->addMapping(ui->plainTextEdit, table_model->fieldIndex("Memo"));
    data_mapper->toFirst();

    // 7. 获取字段名称列表, 填充 "排序字段" 的下拉列表框
    getFieldNames();

    // 8. 更新 action 和 界面组件 的使能状态
    ui->act_open_db->setEnabled(false);
    ui->act_add->setEnabled(true);
    ui->act_insert->setEnabled(true);
    ui->act_remove->setEnabled(true);
    ui->act_salary_up->setEnabled(true);
    ui->groupBox_3->setEnabled(true);
    ui->groupBox_4->setEnabled(true);
}

void MainWindow::getFieldNames()
{
    auto empty_record = table_model->record();
    for(int i = 0;i < empty_record.count(); i++)
        ui->comboBox->addItem(empty_record.fieldName(i));
}

void MainWindow::showRecordCount()
{
    ui->statusbar->showMessage(QString("记录条数: %1").arg(table_model->rowCount()));
}

void MainWindow::do_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);
    ui->act_submit->setEnabled(table_model->isDirty());                             // 当存在数据还没更新到数据库时可以使用
    ui->act_revert->setEnabled(table_model->isDirty());
}

void MainWindow::do_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    ui->act_remove->setEnabled(current.isValid());
    ui->act_set_photo->setEnabled(current.isValid());
    ui->act_remove_photo->setEnabled(current.isValid());
    if (!current.isValid())
    {
        ui->label_2->clear();
        return;
    }
    data_mapper->setCurrentIndex(current.row());
    int cur_rec_no = current.row();
    auto cur_record = table_model->record(cur_rec_no);
    if (cur_record.isNull("Photo"))
        ui->label_2->clear();
    else
    {
        auto data = cur_record.value("Photo").toByteArray();
        QPixmap pic;
        pic.loadFromData(data);
        ui->label_2->setPixmap(pic.scaledToWidth(ui->label_2->size().width()));
    }
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
        openTable();
}


void MainWindow::on_act_add_triggered()
{
    auto record = table_model->record();
    record.setValue(table_model->fieldIndex("empNo"), 2000+table_model->rowCount());
    record.setValue(table_model->fieldIndex("Gender"),"男");
    table_model->insertRecord(table_model->rowCount(), record);

    select_model->clearSelection();
    auto cur_index = table_model->index(table_model->rowCount() - 1, 1);
    select_model->setCurrentIndex(cur_index, QItemSelectionModel::Select);
    showRecordCount();
}


void MainWindow::on_act_insert_triggered()
{
    auto cur_index = ui->tableView->currentIndex();
    auto record = table_model->record();
    table_model->insertRecord(cur_index.row(), record);
    select_model->clearSelection();
    select_model->setCurrentIndex(cur_index, QItemSelectionModel::Select);
    showRecordCount();
}


void MainWindow::on_act_remove_triggered()
{
    auto cur_index = ui->tableView->currentIndex();
    table_model->removeRow(cur_index.row());
    showRecordCount();
}


void MainWindow::on_act_submit_triggered()
{
    auto res = table_model->submitAll();
    if(!res)
        QMessageBox::information(this, "消息", "数据保存错误, 错误信息\n" + table_model->lastError().text());
    else
    {
        ui->act_submit->setEnabled(false);
        ui->act_revert->setEnabled(false);
    }
    showRecordCount();
}


void MainWindow::on_act_revert_triggered()
{
    table_model->revertAll();
    ui->act_submit->setEnabled(false);
    ui->act_revert->setEnabled(false);
    showRecordCount();
}


void MainWindow::on_act_set_photo_triggered()
{
    auto file_name = QFileDialog::getOpenFileName(this, "选择图片文件", "", "照片(*.jpg *.png)");
    if (file_name.isEmpty())
        return;
    QByteArray data;
    auto file = new QFile(file_name);
    file->open(QIODevice::ReadOnly);
    data = file->readAll();
    file->close();

    auto cur_record_no = select_model->currentIndex().row();
    auto cur_record = table_model->record(cur_record_no);
    cur_record.setValue("Photo", data);
    table_model->setRecord(cur_record_no, cur_record);
    QPixmap pic;
    pic.load(file_name);
    ui->label_2->setPixmap(pic.scaledToWidth(ui->label_2->width()));
}


void MainWindow::on_act_remove_photo_triggered()
{
    auto cur_record_no = select_model->currentIndex().row();
    auto cur_record = table_model->record(cur_record_no);
    cur_record.setNull("Photo");
    table_model->setRecord(cur_record_no, cur_record);
    ui->label_2->clear();
}


void MainWindow::on_act_salary_up_triggered()
{
    if (table_model->rowCount() == 0)
        return;
    for(int i = 0; i < table_model->rowCount(); i++)
    {
        auto rec = table_model->record(i);
        auto salary = rec.value("Salary").toFloat();
        salary*=1.1;
        rec.setValue("Salary", salary);
        table_model->setRecord(i, rec);
    }
    if (table_model->submitAll())
        QMessageBox::information(this, "消息", "涨工资数据计算完毕");
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (ui->radioButton->isChecked())
        table_model->setSort(index, Qt::AscendingOrder);
    else
        table_model->setSort(index, Qt::DescendingOrder);
    table_model->select();
}


void MainWindow::on_radioButton_clicked()
{
    table_model->setSort(ui->comboBox->currentIndex(), Qt::AscendingOrder);
    table_model->select();
}


void MainWindow::on_radioButton_2_clicked()
{
    table_model->setSort(ui->comboBox->currentIndex(), Qt::DescendingOrder);
    table_model->select();
}


void MainWindow::on_radioButton_3_clicked()
{
    table_model->setFilter("Gender = '男'");
    showRecordCount();
}


void MainWindow::on_radioButton_4_clicked()
{
    table_model->setFilter("Gender = '女'");
    showRecordCount();
}


void MainWindow::on_radioButton_5_clicked()
{
    table_model->setFilter("");
    showRecordCount();
}

