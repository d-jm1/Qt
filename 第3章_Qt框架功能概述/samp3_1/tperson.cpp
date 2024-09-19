#include "tperson.h"

TPerson::TPerson(QString aName, QObject *parent)
    : QObject{parent}
{
    m_name = aName;
}

TPerson::~TPerson()
{
    qDebug("TPerson 对象被删除了");
}

int TPerson::age()
{
    return m_age;
}

void TPerson::setAge(int value)
{
    if(value == m_age) return;
    m_age = value;
    emit ageChanged(m_age);
}

void TPerson::incAge()
{
    m_age ++;
    emit ageChanged(m_age);
}

