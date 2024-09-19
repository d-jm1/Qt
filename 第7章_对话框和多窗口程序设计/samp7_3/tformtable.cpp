#include "tformtable.h"
#include "./ui_tformtable.h"

FormTable::FormTable(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FormTable)
{
    ui->setupUi(this);
    m_model = new QStandardItemModel(6, 4, this);
    QStringList headers;
    headers << "姓名" <<"性别" << "学位" << "部门";
    m_model->setHorizontalHeaderLabels(headers);
    m_selection = new QItemSelectionModel(m_model, this);
    connect(m_selection, &QItemSelectionModel::currentChanged, this, &FormTable::do_model_currentChanged);
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

FormTable::~FormTable()
{
    delete ui;
}

void FormTable::closeEvent(QCloseEvent *event)
{
    auto result = QMessageBox::question(this,"确认", "确定要退出本程序吗?");
    if (result == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

void FormTable::do_setCellText(int col, int row, QString &text)
{
    auto index = m_model->index(row, col);
    m_selection->clearSelection();
    m_selection->setCurrentIndex(index, QItemSelectionModel::Select);
    m_model->setData(index, text, Qt::DisplayRole);
}

void FormTable::do_model_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if(current.isValid())
    {
        lab_cell_pos->setText(QString::asprintf("当前单元格: %d行, %d 列", current.row(), current.column()));
        auto item = m_model->itemFromIndex(current);
        this->lab_cell_text->setText("单元格内容: " + item->text());
    }
}

void FormTable::on_act_set_list_rows_cols_triggered()
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


void FormTable::on_actionact_set_list_header_triggered()
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


void FormTable::on_tableView_doubleClicked(const QModelIndex &index)
{
    emit cellIndexChanged(index.row(), index.column());
}

