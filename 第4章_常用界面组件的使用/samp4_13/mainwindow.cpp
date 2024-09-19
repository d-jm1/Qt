#include "mainwindow.h"
#include "./ui_mainwindow.h"

void MainWindow::createItemsARow(int row_no, QString name, QString sex, QDate birth, QString nation, bool isPM, int score)
{
    auto stud_id = 202105000;

    auto item = new QTableWidgetItem(name, ctName);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    stud_id += row_no;
    item->setData(Qt::UserRole, QVariant(stud_id));
    ui->tableWidget->setItem(row_no, colName, item);

    QIcon icon;
    if(sex == "男")
        icon.addFile(":/images/icons/boy.ico");
    else
        icon.addFile(":/images/icons/girl.ico");
    item = new QTableWidgetItem(sex, ctSex);
    item->setIcon(icon);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    auto flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;          // 不可编辑
    item->setFlags(flags);
    ui->tableWidget->setItem(row_no, colSex, item);

    auto str = birth.toString("yyyy-MM-dd");
    item = new QTableWidgetItem(str, ctBirth);
    item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->tableWidget->setItem(row_no, colBirth, item);

    item = new QTableWidgetItem(nation, ctNation);
    item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->tableWidget->setItem(row_no, colNation, item);

    item = new QTableWidgetItem("党员", ctPartyM);
    item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    flags |= Qt::ItemIsUserCheckable;                               // 不可编辑, 可选
    item->setFlags(flags);
    if (isPM)
        item->setCheckState(Qt::Checked);
    else
        item->setCheckState(Qt::Unchecked);
    ui->tableWidget->setItem(row_no, colPartyM, item);

    str.setNum(score);
    item = new QTableWidgetItem(str, ctScore);
    item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->tableWidget->setItem(row_no, colScore, item);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lab_status_cell_index = new QLabel("当前单元个坐标: ", this);
    lab_status_cell_type = new QLabel("当前单元格类型: ", this);
    lab_status_stud_id = new QLabel("学生ID: ", this);

    lab_status_cell_index->setMinimumWidth(250);
    lab_status_cell_type->setMinimumWidth(200);
    lab_status_stud_id->setMinimumWidth(200);

    ui->statusbar->addWidget(lab_status_cell_index);
    ui->statusbar->addWidget(lab_status_cell_type);
    ui->statusbar->addWidget(lab_status_stud_id);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_table_set_header_clicked()
{
    QStringList header_text;
    header_text << "姓名" << "性别" << "出生日期" << "民族" << "分数" << "是否党员";
    ui->tableWidget->setHorizontalHeaderLabels(header_text);     // 只设置标题
    ui->tableWidget->setColumnCount(header_text.size());
    for(int i = 0; i < ui->tableWidget->columnCount(); i++)
    {
        auto header_item = new QTableWidgetItem(header_text.at(i));
        auto font = header_item->font();
        font.setBold(true);
        font.setPointSize(11);
        header_item->setBackground(QBrush(Qt::red));
        header_item->setFont(font);
        ui->tableWidget->setHorizontalHeaderItem(i, header_item);
    }
}


void MainWindow::on_btn_table_init_clicked()
{
    QDate birth(2001, 4,6);
    ui->tableWidget->clearContents();
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        auto str_name = QString("学生%1").arg(i);
        auto str_sex = (i % 2) ? "男" : "女";
        auto is_Party = (i % 2 != 0);
        auto score = QRandomGenerator::global()->bounded(60, 100);
        createItemsARow(i, str_name, str_sex, birth, "汉族", is_Party,score);
        birth = birth.addDays(20);
    }
}


void MainWindow::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED(previousColumn);
    Q_UNUSED(previousRow);
    auto item = ui->tableWidget->item(currentRow, currentColumn);
    if(!item)
        return;
    lab_status_cell_index->setText(QString::asprintf("当前单元格坐标: %d 行, %d 列", currentRow, currentColumn));
    auto cell_type = item->type();
    lab_status_cell_type->setText(QString::asprintf("当前单元个类型: %d", cell_type));

    item = ui->tableWidget->item(currentRow, colName);
    auto id = item->data(Qt::UserRole).toUInt();
    lab_status_stud_id->setText(QString::asprintf("学生ID: %d", id));
}


void MainWindow::on_btn_table_insert_row_clicked()
{
    auto cur_row = ui->tableWidget->currentRow();
    ui->tableWidget->insertRow(cur_row);
    createItemsARow(cur_row, "新学生", "男", QDate::fromString("2022-10-2","yyyy-M-d"), "苗族", true, 80);
}


void MainWindow::on_btn_table_add_row_clicked()
{
    auto cur_row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(cur_row);
    createItemsARow(cur_row, "新生", "女", QDate::fromString("2022-1-2","yyyy-M-d"), "满族", true, 76);
}


void MainWindow::on_btn_table_delete_cur_row_clicked()
{
    auto cur_row = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(cur_row);
}


void MainWindow::on_btn_table_fit_height_clicked()
{
    ui->tableWidget->resizeColumnsToContents();
}


void MainWindow::on_btn_table_fit_width_clicked()
{
    ui->tableWidget->resizeRowsToContents();
}


void MainWindow::on_chk_table_editable_clicked(bool checked)
{
    if(checked)
        ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    else
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void MainWindow::on_chk_table_show_header_h_clicked(bool checked)
{
    ui->tableWidget->horizontalHeader()->setVisible(checked);
}


void MainWindow::on_chk_table_show_header_v_clicked(bool checked)
{
    ui->tableWidget->verticalHeader()->setVisible(checked);
}


void MainWindow::on_chk_table_spaceed_row_bg_clicked(bool checked)
{
    ui->tableWidget->setAlternatingRowColors(checked);
}


void MainWindow::on_rbtn_select_cell_clicked()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
}


void MainWindow::on_rbtn_select_row_clicked()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}


void MainWindow::on_btn_table_read_content_to_plt_clicked()
{
    QTableWidgetItem const*item;
    ui->plainTextEdit->clear();
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        auto str = QString::asprintf("第 %d 行: ", i+ 1);
        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            item = ui->tableWidget->item(i, j);
            str = str + item->text() + "   ";
        }
        item  = ui->tableWidget->item(i, colPartyM);
        if (item->checkState() == Qt::Checked)
            str += "党员";
        else
            str += "群众";
        ui->plainTextEdit->appendPlainText(str);
    }
}

