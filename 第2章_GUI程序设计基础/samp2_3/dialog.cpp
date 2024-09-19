#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    init_ui();
    init_signal_slots();
    setWindowTitle("manul factory");
}

Dialog::~Dialog() {}

void Dialog::init_ui()
{
    chk_bold = new QCheckBox("Bold");
    chk_ita = new QCheckBox("Italic");
    chk_under = new QCheckBox("Underline");
    radio_black = new QRadioButton("Black");
    radio_black->setChecked(true);
    radio_blue = new QRadioButton("Blue");
    radio_red = new QRadioButton("red");
    btn_clear = new QPushButton("Clear");
    btn_OK = new QPushButton("OK");
    btn_quit = new QPushButton("Quit");
    plt = new QPlainTextEdit();

    auto *Hlay1 = new QHBoxLayout();
    Hlay1->addWidget(chk_under);
    Hlay1->addWidget(chk_ita);
    Hlay1->addWidget(chk_bold);

    auto *Hlay2 = new QHBoxLayout();
    Hlay2->addWidget(radio_black);
    Hlay2->addWidget(radio_red);
    Hlay2->addWidget(radio_blue);

    auto *Hlay3 = new QHBoxLayout();
    Hlay3->addStretch();
    Hlay3->addWidget(btn_clear);
    Hlay3->addStretch();
    Hlay3->addWidget(btn_OK);
    Hlay3->addWidget(btn_quit);


    plt->setPlainText("Hello word\n 手工创建");
    auto font = plt->font();
    font.setPointSize(20);
    plt->setFont(font);

    auto *Vlay = new QVBoxLayout(this);
    Vlay->addLayout(Hlay1);
    Vlay->addLayout(Hlay2);
    Vlay->addWidget(plt);
    Vlay->addLayout(Hlay3);
    setLayout(Vlay);
}

void Dialog::init_signal_slots()
{
    connect(chk_bold, &QCheckBox::clicked, this, &Dialog::do_chk_bold);
    connect(chk_under, &QCheckBox::clicked, this, &Dialog::do_chk_under);
    connect(chk_ita, &QCheckBox::clicked, this, &Dialog::do_chk_ita);

    connect(radio_black, &QRadioButton::clicked, this, &Dialog::do_radio_color);
    connect(radio_blue, &QRadioButton::clicked, this, &Dialog::do_radio_color);
    connect(radio_red, &QRadioButton::clicked, this, &Dialog::do_radio_color);

    connect(btn_clear, &QPushButton::clicked, plt,&QPlainTextEdit::clear);
    connect(btn_quit, &QPushButton::clicked, this, &Dialog::close);
}

void Dialog::do_chk_under(bool flag)
{
    auto font = plt->font();
    font.setUnderline(flag);
    plt->setFont(font);
}

void Dialog::do_chk_ita(bool flag)
{
    auto font = plt->font();
    font.setItalic(flag);
    plt->setFont(font);
}

void Dialog::do_chk_bold(bool flag)
{
    auto font = plt->font();
    font.setBold(flag);
    plt->setFont(font);
}

void Dialog::do_radio_color()
{
    auto palette = plt->palette();
    if (radio_black->isChecked())
        palette.setColor(QPalette::Text, Qt::black);
    else if(radio_blue->isChecked())
        palette.setColor(QPalette::Text, Qt::blue);
    else
        palette.setColor(QPalette::Text, Qt::red);
    plt->setPalette(palette);
}
