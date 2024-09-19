#include "mainwindow.h"
#include "./ui_mainwindow.h"

void MainWindow::buildUI()
{
    // 状态栏初始化
    status_label_file = new QLabel("文件名:");
    status_label_font_family = new QLabel("字体名称: ");
    status_bar = new QProgressBar();

    status_label_file->setMinimumWidth(150);

    status_bar->setMaximumWidth(200);
    status_bar->setRange(5,50);
    status_bar->setValue(ui->plainTextEdit->font().pointSize());

    ui->statusbar->addPermanentWidget(status_label_file);
    ui->statusbar->addPermanentWidget(status_bar);
    ui->statusbar->addPermanentWidget(status_label_font_family);

    // 工具栏 语言按钮互斥
    tool_language_group = new QActionGroup(this);
    tool_language_group->addAction(ui->action_21);
    tool_language_group->addAction(ui->actionEnglish);
    tool_language_group->setExclusive(true);
    ui->action_21->setChecked(true);

    // 工具栏 添加无法可视化添加的组件
    tool_font_size = new QSpinBox(this);
    tool_font_family = new QFontComboBox(this);

    tool_font_size->setMinimum(5);
    tool_font_size->setMaximum(50);
    tool_font_size->setValue(ui->plainTextEdit->font().pointSize());
    tool_font_size->setMaximumWidth(50);

    tool_font_family->setMinimumWidth(150);

    ui->toolBar->addWidget(tool_font_size);
    ui->toolBar->addWidget(tool_font_family);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->action_13);
}

void MainWindow::buildSignalSlots()
{
    connect(tool_font_size,&QSpinBox::valueChanged,this,&MainWindow::do_font_size_changed);
    connect(tool_font_family,&QFontComboBox::currentFontChanged, this, &MainWindow::do_font_family_changed);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buildUI();                                                  // 界面初始化, 为需要的组件申明内存空间, 并将对应的组件放置到相应的 工具栏中和状态栏
    buildSignalSlots();                                         // 所有需要被连接的信号和槽初始化
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);    // 工具按钮只显示 文字
    this->setCentralWidget(ui->plainTextEdit);                  // 界面主空间为 plainTextEdit
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_font_size_changed(int font_size)
{
    qInfo() << "字体大小修改为" << font_size;
    auto fmt = ui->plainTextEdit->currentCharFormat();
    fmt.setFontPointSize(font_size);
    ui->plainTextEdit->setCurrentCharFormat(fmt);
    status_bar->setValue(font_size);
}

void MainWindow::do_font_family_changed(const QFont &font)
{
    qInfo() << "字体修改为" << font.toString();
    status_label_font_family->setText("字体名称: " + font.family());
    auto fmt = ui->plainTextEdit->currentCharFormat();
    fmt.setFont(font);
    ui->plainTextEdit->setCurrentCharFormat(fmt);
}
