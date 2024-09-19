#include "tformdoc.h"
#include "ui_tformdoc.h"

TFormDoc::TFormDoc(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TFormDoc)
{
    ui->setupUi(this);
    auto *tool_bar = new QToolBar("文档", this);
    tool_bar->addAction(ui->act_open);
    tool_bar->addAction(ui->act_font);
    tool_bar->addSeparator();
    tool_bar->addAction(ui->act_cut);
    tool_bar->addAction(ui->act_copy);
    tool_bar->addAction(ui->act_paste);
    tool_bar->addAction(ui->act_undo);
    tool_bar->addAction(ui->act_redo);
    tool_bar->addSeparator();
    tool_bar->addAction(ui->act_exit);
    tool_bar->setToolButtonStyle(Qt::ToolButtonTextOnly);
    auto layout = new QVBoxLayout();
    layout->addWidget(tool_bar);
    layout->addWidget(ui->plainTextEdit);
    layout->setContentsMargins(2,2,2,2);
    layout->setSpacing(2);
    this->setLayout(layout);
}

void TFormDoc::loadFromFile(QString &file_name)
{
    QFile file(file_name);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        ui->plainTextEdit->clear();
        while(!stream.atEnd())
        {
            auto str = stream.readLine();
            ui->plainTextEdit->appendPlainText(str);
        }
        file.close();
        QFileInfo file_info(file_name);
        auto short_name = file_info.fileName();
        this->setWindowTitle(short_name);
    }
    file.close();
    ui->plainTextEdit->document()->clearUndoRedoStacks();
}

TFormDoc::~TFormDoc()
{
    delete ui;
}

void TFormDoc::on_act_open_triggered()
{
    auto cur_path = QDir::currentPath();
    auto file_name = QFileDialog::getOpenFileName(this, "打开一个文件", cur_path, /*"C程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)"*/ "*.py");
    if(file_name.isEmpty())
        return;
    loadFromFile(file_name);
}


void TFormDoc::on_act_font_triggered()
{
    auto font = ui->plainTextEdit->font();
    bool ok;
    font = QFontDialog::getFont(&ok, font, this);
    ui->plainTextEdit->setFont(font);
}

