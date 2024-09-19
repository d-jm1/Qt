#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // setCentralWidget(ui->line_2);
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    setActionsForButton();
    createSelectionMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setActionsForButton()
{
    ui->tbtn_init_list->setDefaultAction(ui->act_init_list);
    ui->tbtn_clear_list->setDefaultAction(ui->act_clear_list);
    ui->tbtn_insert_item->setDefaultAction(ui->act_insert_item);
    ui->tbtn_add_item->setDefaultAction(ui->act_add_item);
    ui->tbtn_delete_item->setDefaultAction(ui->act_delete_item);
    ui->tbtn_select_all->setDefaultAction(ui->act_select_all);
    ui->tbtn_select_none->setDefaultAction(ui->act_select_none);
    ui->tbtn_select_inv->setDefaultAction(ui->act_select_inverse);
}

void MainWindow::createSelectionMenu()
{
    auto menuSelection = new QMenu(this);
    menuSelection->addAction(ui->act_select_all);
    menuSelection->addAction(ui->act_select_none);
    menuSelection->addAction(ui->act_select_inverse);

    ui->tbtn_select_item->setPopupMode(QToolButton::MenuButtonPopup);
    ui->tbtn_select_item->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->tbtn_select_item->setDefaultAction(ui->act_select_menu);
    ui->tbtn_select_item->setMenu(menuSelection);

    auto a_btn = new QToolButton(this);
    a_btn->setPopupMode(QToolButton::InstantPopup);
    a_btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    a_btn->setDefaultAction(ui->act_select_menu);
    a_btn->setMenu(menuSelection);

    ui->toolBar->addWidget(a_btn);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->act_exit);
}

void MainWindow::on_act_init_list_triggered()
{
    QListWidgetItem *a_item;
    QIcon a_icon;
    a_icon.addFile(":/images/icons/check2.ico");
    auto chk = ui->chk_item_editable->isChecked();

    ui->listWidget->clear();
    for(auto i = 0; i < 10; i++)
    {
        auto str = QString("Item %1").arg(i);
        a_item = new QListWidgetItem();
        a_item->setText(str);
        a_item->setIcon(a_icon);
        a_item->setCheckState(Qt::Checked);
        if(chk)
            a_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable
                             | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        else
            a_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        ui->listWidget->addItem(a_item);
    }
}


void MainWindow::on_act_clear_list_triggered()
{
    ui->listWidget->clear();
}


void MainWindow::on_act_insert_item_triggered()
{
    QIcon a_icon(":/images/icons/check2.ico");
    auto chk = ui->chk_item_editable->isChecked();
    auto *a_item = new QListWidgetItem("Inserted Item");
    a_item->setIcon(a_icon);
    a_item->setCheckState(Qt::Checked);
    if(chk)
        a_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable
                         | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    else
        a_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    ui->listWidget->insertItem(ui->listWidget->currentRow(),a_item);
}


void MainWindow::on_act_add_item_triggered()
{
    QIcon a_icon(":/images/icons/check2.ico");
    auto chk = ui->chk_item_editable->isChecked();
    auto *a_item = new QListWidgetItem("Added Item");
    a_item->setIcon(a_icon);
    a_item->setCheckState(Qt::Checked);
    if(chk)
        a_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable
                         | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    else
        a_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    ui->listWidget->addItem(a_item);
}


void MainWindow::on_act_delete_item_triggered()
{
    auto row = ui->listWidget->currentRow();
    auto a_item = ui->listWidget->takeItem(row);
    delete a_item;
}


void MainWindow::on_act_select_all_triggered()
{
    QListWidgetItem *a_item;
    auto cnt = ui->listWidget->count();
    for(int i = 0; i < cnt; i++)
    {
        a_item = ui->listWidget->item(i);
        a_item->setCheckState(Qt::Checked);
    }
}


void MainWindow::on_act_select_none_triggered()
{
    QListWidgetItem *a_item;
    auto cnt = ui->listWidget->count();
    for(int i = 0; i < cnt; i++)
    {
        a_item = ui->listWidget->item(i);
        a_item->setCheckState(Qt::Unchecked);
    }
}


void MainWindow::on_act_select_inverse_triggered()
{
    QListWidgetItem *a_item;
    auto cnt = ui->listWidget->count();
    for(int i = 0; i < cnt; i++)
    {
        a_item = ui->listWidget->item(i);
        if(a_item->checkState() == Qt::Unchecked)
            a_item->setCheckState(Qt::Checked);
        else
            a_item->setCheckState(Qt::Unchecked);
    }
}


void MainWindow::on_toolButton_5_clicked()
{
    ui->listWidget->sortItems(Qt::AscendingOrder);
}


void MainWindow::on_toolButton_6_clicked()
{
    ui->listWidget->sortItems(Qt::DescendingOrder);
}


void MainWindow::on_checkBox_clicked(bool checked)
{
    ui->listWidget->setSortingEnabled(checked);
}


void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString str;
    if(current)
    {
        if(!previous)
            str = "当前: " + current->text();
        else
            str = "前一项: " + previous->text() + "; 当前项: " + current->text();
        ui->lineEdit->setText(str);
    }
    ui->plainTextEdit->appendPlainText("currentItemChanged() 信号被发射");
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->plainTextEdit->appendPlainText("");
}


void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    ui->plainTextEdit->appendPlainText(
        QString("currentRowChanged() 信号被发射, currentRow = %1").arg(currentRow)
        );
}


void MainWindow::on_listWidget_currentTextChanged(const QString &currentText)
{
    ui->plainTextEdit->appendPlainText(
        QString("currentTextChanged() 信号被发射, currentText = ") + currentText
        );
}


void MainWindow::on_listWidget_itemChanged(QListWidgetItem *item)
{
    ui->plainTextEdit->appendPlainText(
        QString("ItemChanged() 信号被发射, ") + item->text()
        );
}


void MainWindow::on_listWidget_itemSelectionChanged()
{
    ui->plainTextEdit->appendPlainText(
        QString("itemSelectionChanged() 信号被发射.")
        );
}


void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    auto menuList = new QMenu(this);
    menuList->addAction(ui->act_init_list);
    menuList->addAction(ui->act_clear_list);
    menuList->addAction(ui->act_insert_item);
    menuList->addAction(ui->act_add_item);
    menuList->addAction(ui->act_delete_item);
    menuList->addSeparator();
    menuList->addAction(ui->act_select_all);
    menuList->addAction(ui->act_select_none);
    menuList->addAction(ui->act_select_inverse);
    menuList->exec(QCursor::pos());                 // 在鼠标光标处显示快捷菜单
    delete menuList;                                // 显示结束后清理对象
}

