#include "dialoglogin.h"
#include "ui_dialoglogin.h"

DialogLogin::DialogLogin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogLogin)
{
    ui->setupUi(this);
    ui->lt_pwd->setEchoMode(QLineEdit::Password);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::SplashScreen);
    QApplication::setOrganizationName("DJM-Qt");
    QApplication::setApplicationName("samp7_7");
    auto bg = QPixmap(":/images/C:/Users/djm/Pictures/全高无光追.png");
    ui->lab_imag->setPixmap(bg);
ui->lab_imag->adjustSize();
    readSettings();
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        moving = true;
        last_pos = event->globalPosition().toPoint() - this->pos();
    }
    return QDialog::mousePressEvent(event);
}

void DialogLogin::mouseReleaseEvent(QMouseEvent *event)
{
    moving = false;
    event->accept();
}

void DialogLogin::mouseMoveEvent(QMouseEvent *event)
{
    auto pos = event->globalPosition().toPoint();
    if (moving && (event->buttons() & Qt::LeftButton) && (pos - last_pos).manhattanLength() > QApplication::startDragDistance())
    {
        move(pos - last_pos);
        last_pos = pos - this->pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void DialogLogin::readSettings()
{
    QSettings settings;
    bool saved = settings.value("saved", false).toBool();
    user = settings.value("Username", "user").toString();
    auto default_pwd = encrypt("12345");
    pwd = settings.value("pwd", default_pwd).toString();
    if (saved)
        ui->lt_user->setText(user);
    ui->chk_save_user->setChecked(saved);
}

void DialogLogin::writeSettings()
{
    QSettings settings;
    settings.setValue("Username", user);
    settings.setValue("pwd", pwd);
    settings.setValue("saved", ui->chk_save_user->isChecked());
}

QString DialogLogin::encrypt(const QString &str)
{
    auto bt_array = str.toLocal8Bit();
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(bt_array);
    auto result_array = hash.result();
    QString md5 = result_array.toHex();
    return md5;
}

void DialogLogin::on_btn_ok_clicked()
{
    auto user = ui->lt_user->text().trimmed();
    auto pwd = ui->lt_pwd->text().trimmed();
    auto encrypt_pwd = encrypt(pwd);
    // qDebug() << "用户名: " << user << "\t密码: " << pwd << "\t加密密码: " << encrypt_pwd;
    if((this->user == user) && (this->pwd == encrypt_pwd))
    {
        writeSettings();
        this->accept();
    }
    else
    {
        try_count++;
        if(try_count > 3)
        {
            QMessageBox::critical(this, "错误", "输入错误的次数太多", "强行退出");
            this->reject();
        }
        else
        {
            QMessageBox::warning(this, "错误提示", "用户名或密码错误");
            ui->lt_pwd->clear();
        }
    }
}


void DialogLogin::on_btn_cancel_clicked()
{
    this->reject();
}

