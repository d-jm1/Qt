#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();
    ui->tabWidget->setTabsClosable(true);
    this->setCentralWidget(ui->tabWidget);
    this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, ui->toolBar->height(), this->width(), this->height(),QPixmap(":/images/C:/Users/djm/Pictures/独显全高开光追.png"));
    event->accept();
}

void MainWindow::do_changeTabTitle(QString title)
{
    auto index = ui->tabWidget->currentIndex();
    ui->tabWidget->setTabText(index, title);
}

void MainWindow::on_act_embedded_w_triggered()
{
    auto formdoc = new TFormDoc(this);
    formdoc->setAttribute(Qt::WA_DeleteOnClose);
    auto cur = ui->tabWidget->addTab(formdoc, QString::asprintf("Doc %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
    connect(formdoc, &TFormDoc::titleChanged, this, &MainWindow::do_changeTabTitle);
}


void MainWindow::on_act_indepent_w_triggered()
{
    auto formdoc = new TFormDoc();
    formdoc->setAttribute(Qt::WA_DeleteOnClose);
    formdoc->setWindowTitle("基于 QWidget 的窗口, 无父窗口, 关闭时删除");
    formdoc->setWindowFlag(Qt::Window, true);
    formdoc->setWindowOpacity(0.9);
    formdoc->show();
}


void MainWindow::on_act_embedded_mw_triggered()
{
    auto formdoc = new FormTable(this);
    formdoc->setAttribute(Qt::WA_DeleteOnClose);
    auto cur = ui->tabWidget->addTab(formdoc, QString::asprintf("Table %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void MainWindow::on_act_indepent_mw_triggered()
{
    auto form_table = new FormTable();
    form_table->setAttribute(Qt::WA_DeleteOnClose);
    form_table->setWindowTitle("基于 QMainWindow 的窗口, 无父窗口, 关闭时删除");
    form_table->statusBar();
    form_table->show();
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if(index < 0)
        return;
    auto form = ui->tabWidget->widget(index);
    form->close();
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    Q_UNUSED(index);
    bool en = ui->tabWidget->count() > 0;
    ui->tabWidget->setVisible(en);
}

