#include "mainwindow.h"
#include "./ui_mainwindow.h"

void MainWindow::buildTreeHeader()
{
    ui->treeWidget->clear();
    auto header = new QTreeWidgetItem();

    header->setText(MainWindow::colItem, "目录和文件");

    header->setText(MainWindow::colItemType, "节点类型");

    header->setText(MainWindow::colDate, "最后修改日期");


    header->setTextAlignment(colItem, Qt::AlignHCenter | Qt::AlignVCenter);

    header->setTextAlignment(colItemType, Qt::AlignHCenter | Qt::AlignVCenter);
    ui->treeWidget->setHeaderItem(header);
}

void MainWindow::iniTree()
{
    QIcon icon(":/images/icons/15.ico");
    auto item = new QTreeWidgetItem(itTopItem);
    item->setIcon(MainWindow::colItem, icon);
    item->setText(MainWindow::colItem, "图片");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable
                   | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(MainWindow::colItem, Qt::Checked);
    ui->treeWidget->addTopLevelItem(item);
}

void MainWindow::addFolderItem(QTreeWidgetItem *par_item, QString dir_name)
{
    QIcon icon(":/images/icons/open3.bmp");
    auto node_text = getFinalFolderName(dir_name);
    auto item = new QTreeWidgetItem(itGroupItem);
    item->setIcon(colItem, icon);
    item->setText(colItem, node_text);
    item->setText(colItemType, "Group Item");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable
                   | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);
    item->setData(colItem, Qt::UserRole, QVariant(dir_name));
    par_item->addChild(item);
}

QString MainWindow::getFinalFolderName(const QString &full_path_name)
{
    int cnt = full_path_name.length();
    auto i = full_path_name.lastIndexOf("/");
    auto str = full_path_name.right(cnt-i -1);
    return str;
}

void MainWindow::addImageItem(QTreeWidgetItem *par_item, QString a_file_name)
{
    QIcon icon(":/images/icons/31.ico");
    QFileInfo file_info(a_file_name);
    auto node_text = file_info.fileName();
    auto birth_date = file_info.lastModified();

    QTreeWidgetItem *item;
    item = new QTreeWidgetItem(itImageItem);
    item->setIcon(colItem, icon);
    item->setText(colItem, node_text);
    item->setText(colItemType, "Image Item");
    item->setText(colDate, birth_date.toString("yyyy-MM-dd"));
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable
                   | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);
    item->setData(colItem, Qt::UserRole, QVariant(a_file_name));
    par_item->addChild(item);
}



void MainWindow::displayImage(QTreeWidgetItem *item)
{
    auto file_name = item->data(colItem, Qt::UserRole).toString();
    lab_status_file_name->setText(file_name);
    lab_status_node_text->setText(item->text(colItem));
    m_pixmap.load(file_name);
    ui->act_zoom_fit_height->trigger();
    ui->act_zoom_fit_height->setEnabled(true);
    ui->act_zoom_fit_width->setEnabled(true);
    ui->act_zoom_in->setEnabled(true);
    ui->act_zoom_out->setEnabled(true);
    ui->act_zoom_real->setEnabled(true);
}

void MainWindow::changeItemCaption(QTreeWidgetItem *item)
{
    QString str = "*" + item->text(colItem);
    item->setText(colItem, str);
    if(item->childCount() > 0)
        for(int i = 0; i < item->childCount(); i++)
            changeItemCaption(item->child(i));      // 递归调用, 修改所有的标题
}

void MainWindow::deleteItem(QTreeWidgetItem *par_item, QTreeWidgetItem *item)
{
    if(item->childCount() > 0)
    {
        int count = item->childCount();
        auto temp_par_item = item;
        for(int i = count - 1; i >= 0; i--)
            deleteItem(temp_par_item, temp_par_item->child(i)); // 递归删除, 不使用递归会导致内存泄露
    }
    par_item->removeChild(item);
    delete item;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lab_status_node_text = new QLabel("节点标题", this);
    lab_status_file_name = new QLabel("文件名", this);
    spin_status_ratio = new QSpinBox(this);

    lab_status_node_text->setMinimumWidth(200);
    spin_status_ratio->setRange(0,2000);
    spin_status_ratio->setValue(100);
    spin_status_ratio->setSuffix(" %");
    spin_status_ratio->setReadOnly(true);
    spin_status_ratio->setButtonSymbols(QAbstractSpinBox::NoButtons);   // 隐藏按钮

    ui->statusbar->addWidget(lab_status_node_text);
    ui->statusbar->addWidget(spin_status_ratio);
    ui->statusbar->addWidget(lab_status_file_name);

    buildTreeHeader();
    iniTree();

    ui->act_window_float->setChecked(ui->dockWidget->isFloating());
    ui->act_window_visiable->setChecked(!ui->dockWidget->isHidden());
    setCentralWidget(ui->scrollArea);
}

MainWindow::~MainWindow()
{
        // qDebug(ui->dockWidget->isVisible()? "窗口可见" : "窗口不可见");
        // qDebug(ui->dockWidget->isHidden()? "窗口隐藏了" : "窗口没隐藏");
    delete ui;
}

void MainWindow::on_act_add_fold_triggered()
{
    auto dir = QFileDialog::getExistingDirectory();
    if (dir.isEmpty())
        return;
    auto par_item = ui->treeWidget->currentItem();
    if(!par_item)
        return;
    if (par_item->type() != itImageItem) // 问题
        addFolderItem(par_item, dir);
}


void MainWindow::on_act_add_file_triggered()
{
    auto files = QFileDialog::getOpenFileNames(this,"选择文件", "", "Images(*.jpg, *.png)");
    if(files.isEmpty())
        return;
    QTreeWidgetItem *par_item, *item;
    item= ui->treeWidget->currentItem();
    if(!item)
        item = ui->treeWidget->topLevelItem(0);
    if(item->type() == itImageItem)
        par_item = item->parent();
    else
        par_item = item;
    for(int i = 0; i < files.size(); i++)
    {
        auto a_file_name = files.at(i);
        addImageItem(par_item, a_file_name);
    }
    par_item->setExpanded(true);
}


void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);
    qDebug("currentItemChanged() is emitted");
    if(!current)
        return;
    if(current == previous)
        return;
    auto var = current->type();
    switch(var)
    {
    case itTopItem:
        ui->act_add_fold->setEnabled(true);
        ui->act_add_file->setEnabled(true);
        ui->act_delete_node->setEnabled(false);
        break;
    case itGroupItem:
        ui->act_add_fold->setEnabled(true);
        ui->act_add_file->setEnabled(true);
        ui->act_delete_node->setEnabled(true);
        break;
    case itImageItem:
        ui->act_add_fold->setEnabled(false);
        ui->act_add_file->setEnabled(true);
        ui->act_delete_node->setEnabled(true);
        displayImage(current);
    }
}


void MainWindow::on_act_delete_node_triggered()
{
    auto *item = ui->treeWidget->currentItem();
    if(!item)
        return;
    auto par_item = item->parent();
    deleteItem(par_item, item);
}


void MainWindow::on_act_traversal_node_triggered()
{
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        auto item = ui->treeWidget->topLevelItem(i);
        changeItemCaption(item);
    }
}


void MainWindow::on_act_zoom_in_triggered()
{
    m_ratio *= 1.2;
    spin_status_ratio->setValue(100 * m_ratio);
    auto w = m_ratio * m_pixmap.width();
    auto h = m_ratio * m_pixmap.height();
    auto pix = m_pixmap.scaled(w,h);
    ui->lab_pic->setPixmap(pix);
}


void MainWindow::on_act_zoom_fit_height_triggered()
{
    auto height = ui->scrollArea->height();
    int real_height = m_pixmap.height();
    m_ratio = float(height) / real_height;
    spin_status_ratio->setValue(100 * m_ratio);
    auto pix = m_pixmap.scaledToHeight(height - 30);
    ui->lab_pic->setPixmap(pix);
}


void MainWindow::on_act_zoom_real_triggered()
{
    m_ratio = 1;
    spin_status_ratio->setValue(100);
    ui->lab_pic->setPixmap(m_pixmap);
}


void MainWindow::on_act_zoom_out_triggered()
{
    m_ratio *= 0.8;
    spin_status_ratio->setValue(100 * m_ratio);
    auto w = m_ratio * m_pixmap.width();
    auto h = m_ratio * m_pixmap.height();
    auto pix = m_pixmap.scaled(w,h);
    ui->lab_pic->setPixmap(pix);
}


void MainWindow::on_act_window_float_triggered(bool checked)
{
    ui->dockWidget->setFloating(checked);
}


void MainWindow::on_act_window_visiable_triggered(bool checked)
{
    ui->dockWidget->setVisible(checked);
}


void MainWindow::on_dockWidget_topLevelChanged(bool topLevel)
{
    ui->act_window_float->setChecked(topLevel);
}

