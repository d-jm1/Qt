#include "mainwindow.h"
#include "./ui_mainwindow.h"

void MainWindow::initModelData(QStringList &a_file_content)
{
    auto row_cnt = a_file_content.size();
    m_model->setRowCount(row_cnt - 1);
    auto header = a_file_content.at(0);
    auto header_list = header.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    m_model->setHorizontalHeaderLabels(header_list);
    int j;
    QStandardItem *a_item;
    for(int i = 1; i < row_cnt; i++)
    {
        auto a_line_text = a_file_content.at(i);
        auto tmp_list = a_line_text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        for(j = 0; j < FixedColumnCount - 1; j++)
        {
            a_item = new QStandardItem(tmp_list.at(j));
            m_model->setItem(i - 1, j, a_item);
        }

        a_item = new QStandardItem(header_list.at(j));
        a_item->setCheckable(true);
        a_item->setBackground(QBrush(Qt::yellow));
        // qDebug() << "a_item = " << a_item->text();
        if (tmp_list.at(j) == "0")
            a_item->setCheckState(Qt::Unchecked);
        else
            a_item->setCheckState(Qt::Checked);
        m_model->setItem(i - 1, j, a_item);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_model = new QStandardItemModel(2, FixedColumnCount, this);
    m_selection = new QItemSelectionModel(m_model, this);
    connect(m_selection, &QItemSelectionModel::currentChanged,this, &MainWindow::do_currentChanged);
    ui->tableView->setModel(m_model);
    ui->tableView->setSelectionModel(m_selection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    int_spin_delegate = new TSpinDelegate(this);
    float_spin_delegate = new TFloatSpinDelegate(this);
    combo_delegate = new TComboBoxDelegate(this);

    QStringList str_list;
    str_list << "优" << "良" << "一般" << "不合格";
    combo_delegate->setItems(str_list, false);

    ui->tableView->setItemDelegateForColumn(0, int_spin_delegate);
    ui->tableView->setItemDelegateForColumn(1, float_spin_delegate);
    ui->tableView->setItemDelegateForColumn(2, float_spin_delegate);
    ui->tableView->setItemDelegateForColumn(3, float_spin_delegate);
    ui->tableView->setItemDelegateForColumn(4, combo_delegate);

    // 菜单栏
    group_act_ali = new QActionGroup(this);
    group_act_ali->addAction(ui->act_ali_center);
    group_act_ali->addAction(ui->act_ali_left);
    group_act_ali->addAction(ui->act_ali_right);

    // 状态栏
    lab_cur_file = new QLabel("当前文件: ", this);
    lab_cell_pos = new QLabel("当前单元格: ", this);
    lab_cell_text = new QLabel("单元格内容: ", this);

    lab_cur_file->setMinimumWidth(200);
    lab_cell_pos->setMinimumWidth(180);
    lab_cell_text->setMinimumWidth(150);

    lab_cell_pos->setAlignment(Qt::AlignHCenter);

    ui->statusbar->addWidget(lab_cur_file);
    ui->statusbar->addWidget(lab_cell_pos);
    ui->statusbar->addWidget(lab_cell_text);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if(current.isValid())
    {
        lab_cell_pos->setText(QString::asprintf("当前单元格: %d 行, %d 列", current.row(), current.column()));
        auto a_item = m_model->itemFromIndex(current);
        lab_cell_text->setText(QString::asprintf("单元格内容: ", a_item->text()));
        auto font = a_item->font();
        ui->act_font_bold->setChecked(font.bold());
    }
}

void MainWindow::on_act_open_file_triggered()
{
    auto cur_path = QCoreApplication::applicationDirPath();
    a_file_name = QFileDialog::getOpenFileName(this, "打开一个文件", cur_path, "数据文件(*.txt);; 所有文件(*.*)");
    if(a_file_name.isEmpty())
        return;
    QStringList a_file_content;
    QFile a_file(a_file_name);
    if(a_file.open(QIODevice::ReadOnly | QIODevice::Text))  // 只读方式并以文本格式打开文件
    {
        QTextStream a_stream(&a_file);
        ui->plainTextEdit->clear();
        while(!a_stream.atEnd())
        {
            auto str = a_stream.readLine();
            ui->plainTextEdit->appendPlainText(str);
            a_file_content.append(str);
        }
        a_file.close();
        lab_cur_file->setText("当前文件: " + a_file_name);
        ui->act_add_row->setEnabled(true);
        ui->act_insert_row->setEnabled(true);
        ui->act_remove_row->setEnabled(true);
        ui->act_save_file->setEnabled(true);
        initModelData(a_file_content);
    }
}


void MainWindow::on_act_add_row_triggered()
{
    QList<QStandardItem*> a_item_list;
    QStandardItem *a_item;
    for(int i = 0; i < FixedColumnCount - 1; i++)
    {
        a_item = new QStandardItem("0");
        a_item_list << a_item;
    }
    auto str = m_model->headerData(m_model->columnCount() - 1, Qt::Horizontal, Qt::DisplayRole).toString();
    a_item = new QStandardItem(str);
    a_item->setCheckable(true);
    a_item_list << a_item;

    m_model->insertRow(m_model->rowCount(), a_item_list);
    auto cur_index = m_model->index(m_model->rowCount() - 1, 0);
    m_selection->clearSelection();
    m_selection->setCurrentIndex(cur_index, QItemSelectionModel::Select);
}


void MainWindow::on_act_insert_row_triggered()
{
    QList<QStandardItem*> a_item_list;
    QStandardItem *a_item;
    for(int i = 0; i < FixedColumnCount - 1; i++)
    {
        a_item = new QStandardItem("1");
        a_item_list << a_item;
    }
    auto str = m_model->headerData(m_model->columnCount() - 1, Qt::Horizontal, Qt::DisplayRole).toString();
    a_item = new QStandardItem(str);
    a_item->setCheckable(true);
    a_item_list << a_item;
    auto cur_row = ui->tableView->currentIndex().row();
    m_model->insertRow(cur_row, a_item_list);
    auto cur_index = m_model->index(cur_row, 0);
    m_selection->clearSelection();
    m_selection->setCurrentIndex(cur_index, QItemSelectionModel::Select);
}


void MainWindow::on_act_remove_row_triggered()
{
    auto cur_row = ui->tableView->currentIndex();
    if(cur_row.row() == m_model->rowCount() - 1)
        m_model->removeRow(cur_row.row());
    else
    {
        m_model->removeRow(cur_row.row());
        m_selection->setCurrentIndex(cur_row, QItemSelectionModel::Select);
    }
}


void MainWindow::on_act_ali_left_triggered()
{
    if(!m_selection->hasSelection())
        return;
    auto index_list = m_selection->selectedIndexes();
    for(auto index: index_list)
    {
        auto *a_item = m_model->itemFromIndex(index);
        a_item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    }
}


void MainWindow::on_act_ali_right_triggered()
{
    if(!m_selection->hasSelection())
        return;
    auto index_list = m_selection->selectedIndexes();
    for(auto index: index_list)
    {
        auto *a_item = m_model->itemFromIndex(index);
        a_item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }
}


void MainWindow::on_act_ali_center_triggered()
{
    if(!m_selection->hasSelection())
        return;
    auto index_list = m_selection->selectedIndexes();
    for(auto index: index_list)
    {
        auto *a_item = m_model->itemFromIndex(index);
        a_item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
}




void MainWindow::on_act_font_bold_triggered(bool checked)
{
    if(!m_selection->hasSelection())
        return;
    auto index_list = m_selection->selectedIndexes();
    for(auto index: index_list)
    {
        auto *a_item = m_model->itemFromIndex(index);
        auto font = a_item->font();
        font.setBold(checked);
        a_item->setFont(font);
    }
}


void MainWindow::on_act_preview_data_triggered()
{
    ui->plainTextEdit->clear();
    QStandardItem *a_item;
    QString str;
    for(int i = 0; i < m_model->columnCount(); i++)
    {
        a_item = m_model->horizontalHeaderItem(i);
        str = str + a_item->text() + "\t";
    }
    ui->plainTextEdit->appendPlainText(str);
    for(int i = 0;i < m_model->rowCount(); i++)
    {
        str = "";
        for(int j = 0; j < m_model->columnCount() -1; j++)
        {
            a_item = m_model->item(i,j);
            str += a_item->text() + "\t";
        }
        a_item = m_model->item(i, FixedColumnCount - 1);
        if(a_item->checkState() == Qt::Checked)
            str += "1";
        else
            str += "0";
        ui->plainTextEdit->appendPlainText(str);
    }
}


void MainWindow::on_act_save_file_triggered()
{
    QString str;
    QStandardItem *a_item;
    auto file_name = a_file_name + "_copy.txt";
    QString msg("保存失败");
    if(m_model->rowCount()){
        for(int i = 0; i < m_model->columnCount(); i++)
        {
            a_item = m_model->horizontalHeaderItem(i);
            str = str + a_item->text() + "\t";
        }
        for(int i = 0;i < m_model->rowCount(); i++)
        {
            str += "\n";
            for(int j = 0; j < m_model->columnCount() -1; j++)
            {
                a_item = m_model->item(i,j);
                str += a_item->text() + "\t";
            }
            a_item = m_model->item(i, FixedColumnCount - 1);
            if(a_item->checkState() == Qt::Checked)
                str += "1";
            else
                str += "0";
        }
        QFile a_file(file_name);
        if(a_file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            qDebug() << "保存的数据" << str.toStdString().c_str();
            a_file.write(str.toStdString().c_str());
            a_file.close();
            msg ="保存成功";
        }
    }
    QMessageBox::information(this,file_name,msg);
}

