#include "quote.h"

Quote::Quote()
{

}
Quote::Quote(QString content, int tag1Id, int tag2Id, int tag3Id)
{
    this->Content = content;
    this->Tag1Id = tag1Id;
    this->Tag2Id = tag2Id;
    this->Tag3Id = tag3Id;
}

void Quote::setContent(QString content)
{
    this->Content = content;
}

void Quote::setTag1Id(int tag1Id)
{
    this->Tag1Id = tag1Id;
}

void Quote::setTag2Id(int tag2Id)
{
    this->Tag2Id = tag2Id;
}

void Quote::setTag3Id(int tag3Id)
{
    this->Tag3Id = tag3Id;
}

void Quote::setTag1Name(QString name1)
{
    this->Tag1Name = name1;
}

void Quote::setTag2Name(QString name2)
{
    this->Tag2Name = name2;
}

void Quote::setTag3Name(QString name3)
{
    this->Tag3Name = name3;
}

QString Quote::getContent()
{
    return this->Content;
}

int Quote::getTag1Id()
{
    return this->Tag1Id;
}

int Quote::getTag2Id()
{
    return this->Tag2Id;
}

int Quote::getTag3Id()
{
    return this->Tag3Id;
}


QString Quote::getTag1Name()
{
    return this->Tag1Name;
}

QString Quote::getTag2Name()
{
    return this->Tag2Name;
}

QString Quote::getTag3Name()
{
    return this->Tag3Name;
}
