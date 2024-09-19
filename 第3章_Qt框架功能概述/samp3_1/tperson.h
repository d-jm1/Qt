#ifndef TPERSON_H
#define TPERSON_H

#include <QObject>
#include <QDebug>
class TPerson : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("AUTHOR","WANG")
    Q_CLASSINFO("COMPANY", "UPC")
    Q_CLASSINFO("VERSION","2.0.0")
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(QString name MEMBER m_name)
    Q_PROPERTY(int score MEMBER m_score)
public:
    explicit TPerson(QString aName, QObject *parent = nullptr);
    ~TPerson();
    int age();
    void setAge(int value);
    void incAge();
private:
    int m_age = 10;
    int m_score = 79;
    QString m_name;

signals:
    void ageChanged(int value);
public slots:
};

#endif // TPERSON_H
