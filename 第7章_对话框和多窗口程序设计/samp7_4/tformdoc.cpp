#include "tformdoc.h"
#include "ui_tformdoc.h"

TFormDoc::TFormDoc(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TFormDoc)
{
    ui->setupUi(this);
    this->setWindowTitle("New Doc[*]");
    this->setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->plainTextEdit, &QPlainTextEdit::modificationChanged, this, &QWidget::setWindowModified);
}

void TFormDoc::loadFromFile(QString &file_name)
{
    QFile file(file_name);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        ui->plainTextEdit->clear();
        auto str = stream.readAll();
        ui->plainTextEdit->appendPlainText(str);
        file.close();
        this->file_name = file_name;
        QFileInfo file_info(file_name);
        auto short_name = file_info.fileName();
        this->setWindowTitle(short_name + "[*]");
        file_opened = true;
    }
    file.close();
    ui->plainTextEdit->document()->clearUndoRedoStacks();
}

void TFormDoc::saveToFile()
{
    this->setWindowModified(false);
}

TFormDoc::~TFormDoc()
{
    delete ui;
}

void TFormDoc::on_act_open_triggered()
{
    auto cur_path = QDir::currentPath();
    auto file_name = QFileDialog::getOpenFileName(this, "打开一个文件", cur_path, "C程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)");
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

bool TFormDoc::getFile_opened() const
{
    return file_opened;
}

void TFormDoc::setEditFont()
{
    auto font = ui->plainTextEdit->font();
    bool ok;
    font = QFontDialog::getFont(&ok, font, this);
    ui->plainTextEdit->setFont(font);
}

void TFormDoc::textCut()
{
    ui->plainTextEdit->cut();
}

void TFormDoc::textCopy()
{
    ui->plainTextEdit->copy();
}

void TFormDoc::textPaste()
{
    ui->plainTextEdit->paste();
}

QString TFormDoc::getFile_name() const
{
    return file_name;
}
