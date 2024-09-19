#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    boy = new TPerson("王小明", this);
    boy->setProperty("score", 95);
    boy->setProperty("age", 10);
    boy->setProperty("sex", "Boy");

    connect(boy, &TPerson::ageChanged, this, &Widget::do_ageChanged);

    girl = new TPerson("张小丽", this);
    girl->setProperty("score", 81);
    girl->setProperty("age", 20);
    girl->setProperty("sex", "Girl");

    connect(girl, &TPerson::ageChanged, this, &Widget::do_ageChanged);

    ui->spinBox->setProperty("isBoy", true);
    ui->spinBox_2->setProperty("isBoy", false);
    connect(ui->spinBox_2, &QSpinBox::valueChanged, this, &Widget::do_spinChanged);
    connect(ui->spinBox, &QSpinBox::valueChanged, this, &Widget::do_spinChanged);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::do_ageChanged(int value)
{
    Q_UNUSED(value);
    auto person = qobject_cast<TPerson *> (sender());
    auto name = person->property("name").toString();
    auto sex = person->property("sex").toString();
    auto age = person->age();
    auto str = QString("%1, %2, 年龄 = %3").arg(name).arg(sex).arg(age);
    ui->plt->appendPlainText(str);
}

void Widget::do_spinChanged(int arg1)
{
    auto spinBox = qobject_cast<QSpinBox *>(sender());
    if(spinBox->property("isBoy").toBool())
        boy->setAge(arg1);
    else
        girl->setAge(arg1);
}

void Widget::on_btn_mate_info_clicked()
{
    QObject *obj = boy;
    const auto *meta = obj->metaObject();
    ui->plt->clear();
    ui->plt->appendPlainText(QString("类名称: %1\n").arg(meta->className()));
    ui->plt->appendPlainText("property");
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); i++)
    {
        const char * prop_name = meta->property(i).name();
        auto prop_value = obj->property(prop_name).toString();
        auto str = QString("属性名称 = %1, 属性值 = %2").arg(prop_name).arg(prop_value);
        ui->plt->appendPlainText(str);
    }

    ui->plt->appendPlainText("");
    ui->plt->appendPlainText("classInfo");

    for (int i = meta->propertyOffset() - 1; i < meta->propertyCount() - 1; ++i)
    {
        QMetaClassInfo classinfo = meta->classInfo(i);
        qDebug()<< &classinfo;
        ui->plt->appendPlainText(
            QString("Name = %1, Value = %2").arg(classinfo.name()).arg(classinfo.value())
        );
    }
}

